//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2025 Pearson Education, Hoboken, New Jersey.

/** @file LinkedQueue.cpp */
#include "LinkedQueue.h"   /* 2026-02-20 OG: Include header here since it's no longer at the bottom of .h */
#include "Node.h"          /* 2026-02-20 OG: Added to fix 'Node not declared' error */
#include "PrecondViolatedExcept.h"
#include <memory>

/* 2026-02-21 OG: Initialize static system counter */
template<class ItemType>
long LinkedQueue<ItemType>::totalStringsInSystem = 0;

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue() : backPtr(nullptr), frontPtr(nullptr)
{ }

template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue()
{
   while (!isEmpty()) {
      dequeue();
   }
}

template<class ItemType>
bool LinkedQueue<ItemType>::isEmpty() const noexcept
{
   return frontPtr == nullptr;
}

template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& someItem) {
   if (totalStringsInSystem >= MAX_LIMIT) return false;

   auto itemNodePtr = std::make_shared<Node<ItemType>>(someItem);
   return enqueueNode(itemNodePtr);
}

/* 2026-02-24 OG: Updated for doubly-linked enqueue with proper termination */
template<class ItemType>
bool LinkedQueue<ItemType>::enqueueNode(std::shared_ptr<Node<ItemType>> newNode)
{
    if (!newNode)
        return false;

    newNode->setNext(nullptr);   // Always terminate new node

    if (isEmpty())
    {
        frontPtr = newNode;
        newNode->setPrev(nullptr);  // First node has no previous
    }
    else
    {
        backPtr->setNext(newNode);
        newNode->setPrev(backPtr);
    }

    backPtr = newNode;

    totalStringsInSystem++;   // If you're keeping global tracking

    return true;
}
template<class ItemType>
bool LinkedQueue<ItemType>::dequeue() noexcept {
   return dequeueNode() != nullptr;
}

template<class ItemType>
std::shared_ptr<Node<ItemType>> LinkedQueue<ItemType>::dequeueNode() {
   if (isEmpty()) return nullptr;
   
   auto nodeToReturn = frontPtr;
   if (frontPtr == backPtr) {
      frontPtr = nullptr;
      backPtr = nullptr;
   } else {
      frontPtr = frontPtr->getNext();
   }
   
   nodeToReturn->setNext(nullptr);
   totalStringsInSystem--;
   return nodeToReturn;
}

template<class ItemType>
ItemType LinkedQueue<ItemType>::peekFront() const {
   if (isEmpty()) {
      throw PrecondViolatedExcept("peekFront() called with empty queue.");
   }
   return frontPtr->getItem();
}

template<class ItemType>
std::shared_ptr<Node<ItemType>> LinkedQueue<ItemType>::peekFrontNode() const {
    return frontPtr;
}
template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue& otherQueue)
    : backPtr(nullptr), frontPtr(nullptr)
{
    auto origChainPtr = otherQueue.frontPtr;

    while (origChainPtr != nullptr)
    {
        enqueue(origChainPtr->getItem());
        origChainPtr = origChainPtr->getNext();
    }
}
