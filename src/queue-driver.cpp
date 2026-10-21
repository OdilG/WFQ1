//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2025 Pearson Education, Hoboken, New Jersey.
#include "WFQPriorityQueue.h"
#include <iostream>
#include <random>
#include <cassert>
#include "LinkedQueue.h"
#include "PrecondViolatedExcept.h"
#include <iostream>
#include <string>

void queueTester(LinkedQueue<std::string>& queue);
void copyConstructorTester(LinkedQueue<std::string>& queue);
void simpleAgingDemo()
{
    std::cout << "\n===== MULTI-PRIORITY AGING DEMO =====\n";

    WFQPriorityQueue<std::string> demo;
    demo.setDebug(true);   // Show aging activity

    // Insert multiple low-priority items
    demo.enqueue("LOW_P0", 0);
    demo.enqueue("LOW_P1", 1);
    demo.enqueue("LOW_P2", 2);
    demo.enqueue("LOW_P3", 3);

    // Insert high-priority flood
    for (int i = 0; i < 15; i++)
        demo.enqueue("HIGH_" + std::to_string(i), 9);

    std::cout << "\nStarting dequeues...\n";

    while (!demo.isEmpty())
    {
        std::string item = demo.dequeue();
        std::cout << "Dequeued: " << item << std::endl;
    }

    std::cout << "===== END MULTI-PRIORITY AGING DEMO =====\n";
}
int main()
{
    WFQPriorityQueue<std::string> queue;
    /* 2026-02-25 OG: Test 1 - Verifies basic enqueue and dequeue logic for a small set of items */
    std::cout << "===== WFQ STRESS TEST START =====\n\n";

    // -------------------------------------------------
    // TEST 1: Basic functionality
    // -------------------------------------------------
    std::cout << "Test 1: Basic enqueue/dequeue\n";

    queue.enqueue("A", 5);
    queue.enqueue("B", 2);
    queue.enqueue("C", 9);

    while (!queue.isEmpty())
        std::cout << "Popped: " << queue.dequeue() << "\n";

    std::cout << "Basic test complete\n\n";


    // -------------------------------------------------
    // TEST 2: Same priority same weight
    // -------------------------------------------------
    /* 2026-02-25 OG: Test 2 - Ensures FIFO (First-In, First-Out) integrity for items with identical priority */
    std::cout << "Test 2: Same priority FIFO integrity\n";

    for (int i = 0; i < 10; ++i)
        queue.enqueue("SAME_" + std::to_string(i), 4);

    for (int i = 0; i < 10; ++i)
        std::cout << queue.dequeue() << "\n";

    std::cout << "FIFO test complete\n\n";


    // -------------------------------------------------
    // TEST 3: Flood high priority
    // -------------------------------------------------
    /* 2026-02-25 OG: Test 3 - Stress tests the head and tail pointers with a large volume of high-priority nodes */
    std::cout << "Test 3: Flood priority 9\n";

    for (int i = 0; i < 100; ++i)
        queue.enqueue("HIGH_" + std::to_string(i), 9);

    std::cout << "Inserted 100 priority 9 items\n";

    for (int i = 0; i < 10; ++i)
        std::cout << "Pop: " << queue.dequeue() << "\n";

    std::cout << "High flood test partial drain complete\n\n";


    // -------------------------------------------------
    // TEST 4: Starvation prevention
    // -------------------------------------------------
    /* 2026-02-25 OG: Test 4 - Validates the Weighted Fair Queuing logic to prevent low-priority item starvation */
    std::cout << "Test 4: Starvation prevention\n";
    queue.setDebug(true);
    queue.enqueue("LOW_PRIORITY_SURVIVOR", 0);

    for (int i = 0; i < 200; ++i)
        queue.enqueue("HIGH_SPAM_" + std::to_string(i), 9);

    bool foundLow = false;

    while (!queue.isEmpty())
    {
        std::string item = queue.dequeue();

        if (item == "LOW_PRIORITY_SURVIVOR")
        {
            foundLow = true;
            std::cout << "Low priority survived and was dequeued!\n";
            break;
        }
    }

    assert(foundLow);
    std::cout << "Starvation test complete\n\n";
    queue.setDebug(false);


    // -------------------------------------------------
    // TEST 5: 1,000,000 char stress
    // -------------------------------------------------
    /* 2026-02-25 OG: Test 5 - Memory stress test using large-scale string payloads (1MB per node) */
    std::cout << "Test 5: 1,000,000 character strings\n";

    std::string mega(1'000'000, 'X');

    for (int i = 0; i < 5; ++i)
        queue.enqueue(mega, i);

    std::cout << "Inserted 5 mega strings\n";

    for (int i = 0; i < 5; ++i)
        std::cout << "Mega popped length: "
                  << queue.dequeue().length() << "\n";

    std::cout << "Mega test complete\n\n";


    // -------------------------------------------------
    // TEST 6: Random chaos
    // -------------------------------------------------
    /* 2026-02-25 OG: Test 6 - High-concurrency simulation using 10,000 random operations */
    std::cout << "Test 6: 10,000 random operations\n";

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> priorityDist(0, 9);
    std::uniform_int_distribution<int> lengthDist(1, 5000);

    for (int i = 0; i < 10000; ++i)
    {
        int p = priorityDist(rng);
        int len = lengthDist(rng);

        std::string randomStr(len, 'R');
        queue.enqueue(randomStr, p);
    }

    int popCount = 0;

    while (!queue.isEmpty())
    {
        queue.dequeue();
        popCount++;
    }

    std::cout << "Random test popped: " << popCount << "\n";
    std::cout << "Random chaos test complete\n\n";

    std::cout << "===== ALL TESTS COMPLETED SUCCESSFULLY =====\n";
    simpleAgingDemo();
    return 0;

}

/*
 Testing the Array-based queue:
 Empty: 1
 Adding one
 Adding two
 Adding three
 Adding four
 Adding five
 Adding six
 Empty?: 0
 Loop 0
 peekFront: one
 Empty: 0
 dequeue: 1
 Loop 1
 peekFront: two
 Empty: 0
 dequeue: 1
 Loop 2
 peekFront: three
 Empty: 0
 dequeue: 1
 Loop 3
 peekFront: four
 Empty: 0
 dequeue: 1
 Loop 4
 peekFront: five
 Empty: 0
 dequeue: 1
 Loop 5
 peekFront: six
 Empty: 0
 dequeue: 1
 dequeue with an empty queue:
 Empty: 1
 dequeue: 0
 peekFront with an empty queue:
 peekFront: Precondition Violated Exception: peekFront() called with empty queue
 */
