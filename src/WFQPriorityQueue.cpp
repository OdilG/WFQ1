/* 2026-02-24 OG: WFQ + Aging implementation */

#include "WFQPriorityQueue.h"
#include <iostream>

template<class ItemType>
WFQPriorityQueue<ItemType>::WFQPriorityQueue()
{
    frontPtrs.fill(nullptr);
    backPtrs.fill(nullptr);
}

template<class ItemType>
bool WFQPriorityQueue<ItemType>::isEmpty() const noexcept
{
    return itemCount == 0;
}

template<class ItemType>
size_t WFQPriorityQueue<ItemType>::getSize() const noexcept
{
    return itemCount;
}

template<class ItemType>
int WFQPriorityQueue<ItemType>::calculateWeight(int priority) const
{
    /* 2026-02-24 OG: Weight proportional to priority */
    return priority + 1;  // 0→1 ... 9→10
}


//FinishTime = max(globalTime, arrivalTime) + (serviceTime / weight)
template<class ItemType>
double WFQPriorityQueue<ItemType>::calculateFinishTime(int weight, size_t serviceTime)
{
    return globalTime + (static_cast<double>(serviceTime) / weight);
}

template<class ItemType>
void WFQPriorityQueue<ItemType>::enqueue(const ItemType& item, int priority)
{
    /* 2026-02-24 OG: Enqueue with WFQ + Aging metadata */

    if (priority < 0 || priority > 9)
        throw std::out_of_range("Priority must be 0-9");

    auto newNode = std::make_shared<Node<ItemType>>(item);

    size_t serviceTime = item.length();  // 1 million safe

    int weight = calculateWeight(priority);
    double finish = calculateFinishTime(weight, serviceTime);
    if (debugMode)
        {
            std::cout << "[ENQUEUE] "
                      << "Len=" << serviceTime
                      << " P=" << priority
                      << " W=" << weight
                      << " Arrival=" << arrivalCounter
                      << " Finish=" << finish
                      << "\n";
        }
    newNode->setPriority(priority);
    newNode->setWeight(weight);
    newNode->setArrivalTime(arrivalCounter++);
    newNode->setFinishTime(finish);

    // Doubly linked insert at back of priority queue
    if (!frontPtrs[priority])
    {
        frontPtrs[priority] = newNode;
    }
    else
    {
        backPtrs[priority]->setNext(newNode);
        newNode->setPrev(backPtrs[priority]);
    }

    backPtrs[priority] = newNode;

    itemCount++;
}




template<class ItemType>
void WFQPriorityQueue<ItemType>::ageQueues()
{
    const long AGING_THRESHOLD = 50;

    for (int p = 0; p < 9; ++p)   // no need to age priority 9
    {
        auto current = frontPtrs[p];

        while (current)
        {
            auto nextNode = current->getNext();  // save next first

            long waited = globalTime - current->getArrivalTime();

            if (waited > AGING_THRESHOLD)
            {
                if (debugMode)
                {
                    std::cout << "[AGING] Moving node from "
                              << p << " → " << p + 1 << "\n";
                }

                removeNode(current, p);

                current->setPriority(p + 1);
                current->setWeight(calculateWeight(p + 1));

                insertNodeAtBack(current, p + 1);
            }

            current = nextNode;   // move forward safely
        }
    }
}

template<class ItemType>
ItemType WFQPriorityQueue<ItemType>::dequeue()
{
    if (isEmpty())
        throw std::runtime_error("Queue empty");

    ageQueues();

    std::shared_ptr<Node<ItemType>> bestNode = nullptr;
    int bestPriority = -1;

    for (int p = 0; p < 10; ++p)
    {
        if (frontPtrs[p])
        {
            if (!bestNode ||
                frontPtrs[p]->getFinishTime() < bestNode->getFinishTime())
            {
                bestNode = frontPtrs[p];
                bestPriority = p;
            }
        }
    }

    auto result = bestNode->getItem();
    if (debugMode)
        {
            std::cout << "[DEQUEUE] "
                      << "Len=" << result.length()
                      << " P=" << bestNode->getPriority()
                      << " Finish=" << bestNode->getFinishTime()
                      << " GlobalBefore=" << globalTime
                      << "\n";
        }
    frontPtrs[bestPriority] = bestNode->getNext();

    if (frontPtrs[bestPriority])
        frontPtrs[bestPriority]->setPrev(nullptr);
    else
        backPtrs[bestPriority] = nullptr;

    globalTime += result.length();  // advance virtual time
    if (debugMode)
        {
            std::cout << "GlobalAfter=" << globalTime << "\n\n";
        }
    itemCount--;

    return result;
}

template<class ItemType>
void WFQPriorityQueue<ItemType>::clear()
{
    frontPtrs.fill(nullptr);
    backPtrs.fill(nullptr);
    itemCount = 0;
    globalTime = 0;
}
template<class ItemType>
void WFQPriorityQueue<ItemType>::removeNode(
    std::shared_ptr<Node<ItemType>> node,
    int priority)
{
    auto prev = node->getPrev();
    auto next = node->getNext();

    if (prev)
        prev->setNext(next);
    else
        frontPtrs[priority] = next;   // node was front

    if (next)
        next->setPrev(prev);
    else
        backPtrs[priority] = prev;    // node was back

    node->setNext(nullptr);
    node->setPrev(nullptr);
}
template<class ItemType>
void WFQPriorityQueue<ItemType>::insertNodeAtBack(
    std::shared_ptr<Node<ItemType>> node,
    int priority)
{
    if (!frontPtrs[priority])
    {
        frontPtrs[priority] = node;
    }
    else
    {
        backPtrs[priority]->setNext(node);
        node->setPrev(backPtrs[priority]);
    }

    backPtrs[priority] = node;
}
