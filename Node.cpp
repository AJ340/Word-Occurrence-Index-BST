//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file Node.cpp 
    Listing 4-2 */


#include "Node.h"
#include <cstddef>

template<class ItemType>
Node<ItemType>::Node() : next_node_(nullptr)
{
} // end default constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& an_item) : item_(an_item), next_node_(nullptr)
{
} // end constructor
  
template<class ItemType>
Node<ItemType>::Node(const ItemType& an_item, Node<ItemType>* next_node) :
    item_(an_item), next_node_(next_node)
{
} // end constructor

template<class ItemType>
void Node<ItemType>::SetItem(const ItemType& an_item)
{
   item_ = an_item;
} // end setItem

template<class ItemType>
void Node<ItemType>::SetNext(Node<ItemType>* next_node)
{
   next_node_ = next_node;
} // end setNext_Node_Ptr

template<class ItemType>
ItemType Node<ItemType>::GetItem() const
{
   return item_;
} // end getItem

template<class ItemType>
Node<ItemType>* Node<ItemType>::GetNext() const
{
   return next_node_;
} // end getNext_Node_Ptr
