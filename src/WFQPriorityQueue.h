/*
 * WFQPriorityQueue.h
 *
 *  Created on: Feb 24, 2026
 *      Author: odilg
 */

#ifndef WFQ_PRIORITY_QUEUE_
#define WFQ_PRIORITY_QUEUE_

/* 2026-02-23 OG: Created WFQ doubly-linked priority queue with aging */

#include <memory>
#include <array>
#include <string>
#include <stdexcept>
#include "Node.h"

template<class ItemType>
class WFQPriorityQueue
{
private:

    /* 2026-02-23 OG: 10 priority levels (0 lowest, 9 highest) */
    std::array<std::shared_ptr<Node<ItemType>>, 10> frontPtrs;
    std::array<std::shared_ptr<Node<ItemType>>, 10> backPtrs;

    long globalTime = 0;          // Virtual time
    long arrivalCounter = 0;      // For ordering
    size_t itemCount = 0;

    /* 2026-02-24 OG: Internal helpers */
    void ageQueues();
    int calculateWeight(int priority) const;
    double calculateFinishTime(int weight, size_t serviceTime);
    void removeNode(std::shared_ptr<Node<ItemType>> node, int priority);
    void insertNodeAtBack(std::shared_ptr<Node<ItemType>> node, int priority);

public:
    void setDebug(bool enabled) { debugMode = enabled; }
    WFQPriorityQueue();
    WFQPriorityQueue(const WFQPriorityQueue& other);
    ~WFQPriorityQueue() = default;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    /* 2026-02-24 OG: Debug flag for scheduling visibility */
        bool debugMode = false;
    void enqueue(const ItemType& item, int priority);
    ItemType dequeue();

    void clear();
};

#include "WFQPriorityQueue.cpp"
#endif
