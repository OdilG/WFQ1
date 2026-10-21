//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2025 Pearson Education, Hoboken, New Jersey.


/** @file Node.h */

#ifndef NODE_
#define NODE_
#include <memory>

template<class ItemType>
class Node {
private:
   ItemType item;
   /* 2026-02-21 OG: Changed prev to weak_ptr to prevent cyclic ownership */
      std::weak_ptr<Node<ItemType>> prev;
   std::shared_ptr<Node<ItemType>> next;
   /* 2026-02-21 OG: Numerical priority value for scheduling/ordering */
   int priority = 0;
   /* 2026-02-21 OG: Weight value used for weighted scheduling algorithms */
   int weight = 1;
   /* 2026-02-21 OG: Timestamp recording when the item entered the system */
   long arrivalTime = 0;
   /* 2026-02-21 OG: Calculated or actual time when processing was completed */
   double finishTime = 0.0;

public:
   Node();
   Node(const ItemType& anItem);
   /* 2026-02-21 OG: Added prev accessors */
   void setPrev(std::shared_ptr<Node<ItemType>> prevNodePtr) noexcept;
   std::shared_ptr<Node<ItemType>> getPrev() const noexcept;

   Node(const ItemType& anItem, std::shared_ptr<Node<ItemType>> nextNodePtr);
   Node(const ItemType& anItem, int prio, int w, long time);

   /* 2026-02-21 OG: Updates the data content stored within this node */
   void setItem(const ItemType& anItem) noexcept;
   void setNext(std::shared_ptr<Node<ItemType>> nextNodePtr) noexcept;

   ItemType getItem() const noexcept;
   auto getNext() const noexcept;
   /* 2026-02-21 OG: Getters and setters for scheduling metadata */
   int getPriority() const { return priority; }
   void setPriority(int p) { priority = p; }

   long getArrivalTime() const { return arrivalTime; }
   void setArrivalTime(long t) { arrivalTime = t; }

   int getWeight() const { return weight; }
   void setWeight(int w) { weight = w; }

   double getFinishTime() const { return finishTime; }
   void setFinishTime(double f) { finishTime = f; }






};

#include "Node.cpp"
#endif
