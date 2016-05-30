//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
//  Modified by Ioannis Stamos.

/** @file Node.h 
    Listing 4-1 */
#ifndef TEACH_CSCI235_LINKEDBAG_NODE_H_
#define TEACH_CSCI235_LINKEDBAG_NODE_H_

// Basic Node class to be used in linked-based implementations.
// Sample usage (creates a list of two nodes and displays it):
// Node<int> *a_node = new Node<int>;
// a_node->SetItem(10);
// Node<int> *b_node = new Node<int>(20);
// a_node->SetNext(b_node);
// Node<int> *current_node = a_node;
// while (current_node != nullptr) {
//    cout << current_node->GetItem() << " " << endl;
//    current_node = current_node->GetNext();
// }

template<class ItemType>
class Node {   
public:
   Node();
   // @param an_item a given item.
   // Constucts a node holding an_item and pointing to nullptr.
   Node(const ItemType& an_item);
   
   // @param an_item a given item.
   // @param next_node pointer to next_nodex
   // Constucts a node holding an_item and pointing to next_node.
   Node(const ItemType& an_item, Node<ItemType>* next_node);

   // @param an_item
   // Sets the item_ to an_item.
   void SetItem(const ItemType& an_item);

   // @param next_node pointer to next node.
   // Sets next point to next_node.
   void SetNext(Node<ItemType>* next_node);

   // @return current item.
   ItemType GetItem() const;

   // @return pointer to next node.
   Node<ItemType>* GetNext() const;

private:
   ItemType        item_; // A data item
   Node<ItemType>* next_node_; // Pointer to next node
}; // end Node

#include "Node.cpp"
#endif  // TEACH_CSCI235_LINKEDBAG_NODE_H_
