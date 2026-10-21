//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2025 Pearson Education, Hoboken, New Jersey.

/** @file Node.cpp   */
#include "Node.h"

template<class ItemType>
Node<ItemType>::Node()
: next(nullptr), priority(0), weight(1), arrivalTime(0), finishTime(0.0)
{ }

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem): item(anItem),
/* 2026-02-22 OG: Init metadata in single-param constructor */
next(nullptr), priority(0), weight(1), arrivalTime(0), finishTime(0.0)
{ }

/* 2026-02-22 OG: Full constructor for WFQ packet creation */
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, int prio, int w, long time)
                : item(anItem), next(nullptr), priority(prio), weight(w), arrivalTime(time), finishTime(0.0)
{ }

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem,
                     std::shared_ptr<Node<ItemType>> nextNodePtr)
                : item(anItem), next(nextNodePtr)
{ }

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem) noexcept
{
   item = anItem;
}

template<class ItemType>
void Node<ItemType>::setNext(std::shared_ptr<Node<ItemType>> nextNodePtr) noexcept
{
   next = nextNodePtr;
}

template<class ItemType>
ItemType Node<ItemType>::getItem() const noexcept
{
   return item;
}

template<class ItemType>
auto Node<ItemType>::getNext() const noexcept
{
   return next;
}

/* 2026-02-23 OG: Updated prev setter for weak_ptr */
template<class ItemType>
void Node<ItemType>::setPrev(std::shared_ptr<Node<ItemType>> prevNodePtr) noexcept
{
    prev = prevNodePtr;
}

/* 2026-02-23 OG: Updated prev getter for weak_ptr */
template<class ItemType>
std::shared_ptr<Node<ItemType>> Node<ItemType>::getPrev() const noexcept
{
    return prev.lock();   // Converts weak_ptr to shared_ptr safely
}


