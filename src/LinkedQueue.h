//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2025 Pearson Education, Hoboken, New Jersey.

/** ADT queue: Link-based implementation.
 @file LinkedQueue.h */
/** @file LinkedQueue.h */
#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include "QueueInterface.h"
#include "Node.h"

template<class ItemType>
class LinkedQueue : public QueueInterface<ItemType> {
private:
   std::shared_ptr<Node<ItemType>> backPtr;
   std::shared_ptr<Node<ItemType>> frontPtr;

   /* 2026-02-20 OG: Added global limit tracking */
   static long totalStringsInSystem;
   static const long MAX_LIMIT = 1000000;

public:
   LinkedQueue();
   LinkedQueue(const LinkedQueue& otherQueue);
   ~LinkedQueue();

   bool isEmpty() const noexcept;
   bool enqueue(const ItemType& someItem) override;

   /* 2026-02-20 OG: Added node-level management for Aging/WFQ */
   bool enqueueNode(std::shared_ptr<Node<ItemType>> newNode);
   std::shared_ptr<Node<ItemType>> dequeueNode();
   /* 2026-02-20 OG: Added peek for the node itself to check finishTime */
   std::shared_ptr<Node<ItemType>> peekFrontNode() const;

   bool dequeue() noexcept override;
   /* 2026-02-20 OG: Synchronized exception name to PrecondViolatedExcept */
   ItemType peekFront() const;
   
   /* 2026-02-20 OG: Static getter for system count */
   static long getGlobalCount() { return totalStringsInSystem; }
};
#include "LinkedQueue.cpp"
#endif
