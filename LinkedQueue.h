//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
// Modified by Ioannis Stamos.

/** ADT queue: Link-based implementation.
 Listing 14-3.
 @file LinkedQueue.h */
#ifndef TEACH235_QUEUE_LINKEDQUEUE_H
#define TEACH235_QUEUE_LINKEDQUEUE_H

#include "QueueInterface.h"
#include "Node.h"
#include "PreconditionViolatedException.h"

template<class ItemType>
class LinkedQueue : public QueueInterface<ItemType>
{
public:
   LinkedQueue();
   LinkedQueue(const LinkedQueue& a_queue);
   LinkedQueue<ItemType>& operator=(const LinkedQueue<ItemType>& right_hand_side); 
   ~LinkedQueue();
   
   int GetCount() const;
   bool IsEmpty() const;
   bool Enqueue(const ItemType& new_entry);
   bool Dequeue();
   
   /** @throw PrecondViolatedExcep if the queue is empty */
   ItemType PeekFront() const throw(PreconditionViolatedException);
   
   // Overloads the + operator for queues.
   // @returns the concatenation of this queue with the queue right_hand_side.
   LinkedQueue<ItemType> operator+(const LinkedQueue<ItemType> &right_hand_side) const;
 
   // Friend function to overload the << operator.
   template<class friendItemType>
     friend ostream& operator<<(ostream& out_stream, const LinkedQueue<friendItemType>& output_queue);
 private:
   // Clears a given queue by removing all elements.
   void Clear();
   
   // @param a_list a given queue.
   // Allocates space and copies all the nodes from a_list.
   // The function does not check whether this list contains
   // any items, but it assumes that it is empty.
   void CopyNodesFrom(const LinkedQueue<ItemType> &a_queue);

   int count;
   // The queue is implemented as a chain of linked nodes that has 
   // two external pointers, a head pointer for front of the queue and
   // a tail pointer for the back of the queue.
   Node<ItemType>* back_ptr_;
   Node<ItemType>* front_ptr_;
}; // end LinkedQueue

#include "LinkedQueue.cpp"
#endif  // TEACH235_QUEUE_LINKEDQUEUE_H
