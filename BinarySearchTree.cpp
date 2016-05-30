//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file BinarySearchTree.cpp */
#include <iostream>

#include "BinarySearchTree.h" 
#include "BinaryNode.h" 
#include <queue>

// template<class ItemType>
// BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& treePtr)
// {
//    root_ = this->copyTree(treePtr.root_); // Call inherited method
// }  // end copy constructor

template<class ItemType, class OtherType>
BinarySearchTree<ItemType, OtherType>::BinarySearchTree(const BinarySearchTree<ItemType, OtherType>& tree)
{
  root_ = CopyTree(tree.root_);
}  // end copy constructor

template<class ItemType, class OtherType>
BinarySearchTree<ItemType, OtherType>& BinarySearchTree<ItemType, OtherType>::operator=(const BinarySearchTree<ItemType, OtherType>& right_hand_side)
{
    root_ = CopyTree(right_hand_side.root_);
}  // end operator=


template<class ItemType, class OtherType>
BinarySearchTree<ItemType, OtherType>::~BinarySearchTree()
{
   DestroyTree(root_);
}  // end destructor


template<class ItemType, class OtherType>
bool BinarySearchTree<ItemType, OtherType>::IsEmpty() const
{
   return root_ == nullptr;
}  // end isEmpty

template<class ItemType, class OtherType>
int BinarySearchTree<ItemType, OtherType>::GetHeight() const
{
   return GetHeightHelper(root_);
}  // end getHeight

template<class ItemType, class OtherType>
int BinarySearchTree<ItemType, OtherType>::GetNumberOfNodes() const
{
   return GetNumberOfNodesHelper(root_);
}  // end getNumberOfNodes

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Clear()
{
   DestroyTree(root_);
   root_ = nullptr;
}  // end clear

template<class ItemType, class OtherType>
bool BinarySearchTree<ItemType, OtherType>::Remove(const ItemType& target)
{
  //EC: okay signals if deletion was successful. will be changed by remove value
  bool okay=false;
  RemoveValue(root_,target,okay);
  return okay;
}  // end remove

template<class ItemType, class OtherType>
OtherType BinarySearchTree<ItemType, OtherType>::GetOther(const ItemType& an_entry) const throw(NotFoundException)
{
  //Use internal FindNode to get a pointer to a node. then return the otherItem of that node
  BinaryNode<ItemType, OtherType>* nodeFound = nullptr;
  nodeFound = FindNode(root_,an_entry);
  if(nodeFound == nullptr)
    throw NotFoundException("Item not in tree");

  return nodeFound->GetOther();
}  // end getEntry

template<class ItemType, class OtherType>
OtherType& BinarySearchTree<ItemType, OtherType>::GetOtherReference(const ItemType& an_entry) throw(NotFoundException)
{
  //Same as GetOther except is return by reference
  BinaryNode<ItemType, OtherType>* nodeFound = nullptr;
  nodeFound = FindNode(root_,an_entry);
  if(nodeFound == nullptr)
    throw NotFoundException("Item not in tree");

  return nodeFound->GetOtherReference();
}  // end getEntry

template<class ItemType, class OtherType>
bool BinarySearchTree<ItemType, OtherType>:: Contains(const ItemType& an_entry) const
{
  //If a node is found return true
  if (FindNode(root_,an_entry) != nullptr)
    return true;
  return false;
}  // end contains


template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::PreorderTraverse(void visit(ItemType&)) const
{
   Preorder(visit, root_);
}  // end preorderTraverse

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::InorderTraverse(void visit(ItemType&)) const
{
   Inorder(visit, root_);
}  // end inorderTraverse

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::InorderTraverse(void visit(ItemType&, OtherType&)) const
{
   Inorder(visit, root_);
}  // end inorderTraverse

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::LevelorderTraverse(void visit(ItemType&, OtherType&)) const
{
   Levelorder(visit, root_);
}  // end levelorderTraverse

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::PostorderTraverse(void visit(ItemType&)) const
{
   Postorder(visit, root_);
}  // end postorderTraverse



//////////////////////////////////////////////////////////////
//      Protected Utility Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType, class OtherType>
int BinarySearchTree<ItemType, OtherType>::GetHeightHelper(BinaryNode<ItemType, OtherType>* node_ptr) const
{
  //Gets the bigger height between 2 subtrees and adds 1 for the parent of the two sub trees
   if (node_ptr == nullptr)
      return 0;
   else
      return 1 + max(GetHeightHelper(node_ptr->GetLeftPtr()), 
                     GetHeightHelper(node_ptr->GetRightPtr()));
}  // end GetHeightHelper

template<class ItemType, class OtherType>
int BinarySearchTree<ItemType, OtherType>::GetNumberOfNodesHelper(BinaryNode<ItemType, OtherType>* node_ptr) const
{
  //1 + 2* Number of nodes in 2 subtrees. Base case 0 because leaf nodes left and rights dont count as nodes
   if (node_ptr == nullptr)
      return 0;
   else
      return 1 + GetNumberOfNodesHelper(node_ptr->GetLeftPtr()) + GetNumberOfNodesHelper(node_ptr->GetRightPtr());
}  // end GetNumberOfNodesHelper


template<class ItemType, class OtherType>
bool BinarySearchTree<ItemType, OtherType>::Add(const ItemType& new_item, const OtherType& new_other)
{
   BinaryNode<ItemType, OtherType>* new_node = new BinaryNode<ItemType, OtherType>(new_item);
   new_node->SetOther(new_other);
   root_ = InsertInorder(root_, new_node);
   return true;
}  // end add


//////////////////////////////////////////////////////////////
//
//      Protected Utility Methods Section
//
//////////////////////////////////////////////////////////////

template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::InsertInorder(BinaryNode<ItemType, OtherType>* subTreePtr,
										      BinaryNode<ItemType, OtherType>* newNodePtr)
{
  //Base case: Returns pointer of newnode so that parent can adopt
  if(subTreePtr == nullptr)
    return newNodePtr;
  else
  {
    //Traverse left if key is less
    if(newNodePtr->GetItem() < subTreePtr->GetItem())
      subTreePtr->SetLeftPtr(InsertInorder(subTreePtr->GetLeftPtr(),newNodePtr));
    //Traverse right if key is more
    if(newNodePtr->GetItem() > subTreePtr->GetItem())
      subTreePtr->SetRightPtr(InsertInorder(subTreePtr->GetRightPtr(),newNodePtr));
    return subTreePtr;
  }
}  // end insertInorder

template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::RemoveValue(BinaryNode<ItemType, OtherType>* subTreePtr,
										    const ItemType target, 
										    bool& success)
{
  //Recursively find the node that is requested for deletion. If a leaf node is reached set success to false
  if(subTreePtr == nullptr)
  {
    success = false;
    return nullptr;  
  }  
  //If target found. Remove the node. Deletion successful. Success=true
  else if (target == subTreePtr->GetItem())
  {
    subTreePtr = RemoveNode(subTreePtr);
    success = true;
  }
  //If target is less than this nodes item then go left
  else if (target < subTreePtr->GetItem())
    subTreePtr->SetLeftPtr(RemoveValue(subTreePtr->GetLeftPtr(),target,success));
  //If target is more than this nodes item then go right
  else if (target > subTreePtr->GetItem())
    subTreePtr->SetRightPtr(RemoveValue(subTreePtr->GetRightPtr(),target,success));
  return subTreePtr;
}  // end RemoveValue

template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::RemoveNode(BinaryNode<ItemType, OtherType>* nodePtr)
{
    //Case 1 = No Children
    if(nodePtr->GetLeftPtr() == nullptr && nodePtr->GetRightPtr() == nullptr)
    {
      delete nodePtr;
      return nullptr;
    }
    //Case 2 = 1 Child
    else if(nodePtr->GetLeftPtr() == nullptr)
    {
      //Adopt only child
      BinaryNode<ItemType, OtherType>* temp_ptr= nodePtr;
      nodePtr = nodePtr->GetRightPtr();
      delete temp_ptr;
    }
    else if(nodePtr->GetRightPtr() == nullptr)
    {
      //Adopt only child
      BinaryNode<ItemType, OtherType>* temp_ptr= nodePtr;
      nodePtr = nodePtr->GetLeftPtr();
      delete temp_ptr;
    }

    //Case 3 = 2 Children (Reduce to deleting node with 1/0 children)
    else
    {
      //Get inorder successor (will have 0 or 1 child), set the node's value to inorder successor
      //Change IIOsuccessor and OIOsuccessor to the min's Item and Other values so that we can put them in the deleted node.
      ItemType IIOsuccessor;
      OtherType OIOsuccessor;
      nodePtr->SetRightPtr(RemoveLeftmostNode(nodePtr->GetRightPtr(),IIOsuccessor,OIOsuccessor));
      nodePtr->SetItem(IIOsuccessor);
      nodePtr->SetOther(OIOsuccessor);
    }  // end RemoveNode
    return nodePtr;
}

template<class ItemType, class OtherType> 
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::RemoveLeftmostNode(BinaryNode<ItemType, OtherType>* nodePtr,
                                                                     ItemType& IinorderSuccessor,OtherType& OinorderSuccessor)
{
  //Stores the inordersuccessor's Item and OtherItem in IinorderSuccessor and OinorderSuccessor and deletes it
  if(nodePtr->GetLeftPtr() == nullptr)
  {
    IinorderSuccessor= nodePtr->GetItem();
    OinorderSuccessor= nodePtr->GetOther();
    return RemoveNode(nodePtr);
  }
  //This statement traverses to the minimum 
  nodePtr->SetLeftPtr(RemoveLeftmostNode(nodePtr->GetLeftPtr(),IinorderSuccessor,OinorderSuccessor));
  return nodePtr;
}  // end RemoveLeftmostNode


template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::FindNode(BinaryNode<ItemType, OtherType>* subTreePtr,
                                                           const ItemType& target) const 
{
  //base case empty tree
  if(subTreePtr == nullptr)
    return nullptr;
  //base case target found, return a pointer to that node
  if(subTreePtr->GetItem() == target)
    return subTreePtr;
  else
  {
    //Check left and if the node isnt found (nullptr is returned)  check the right. then return the address of the node that was found 
    BinaryNode<ItemType, OtherType>* nodeFound = nullptr;
    if(target < subTreePtr->GetItem())
      nodeFound = FindNode(subTreePtr->GetLeftPtr(),target);
    if(nodeFound == nullptr && target > subTreePtr->GetItem())
      nodeFound = FindNode(subTreePtr->GetRightPtr(),target);
    return nodeFound;
  }
}  // end findNode

template<class ItemType, class OtherType>
BinaryNode<ItemType, OtherType>* BinarySearchTree<ItemType, OtherType>::CopyTree(const BinaryNode<ItemType, OtherType>* node_ptr) const
{
   BinaryNode<ItemType, OtherType>* new_tree_ptr = nullptr;
   // Copy tree nodes during a preorder traversal
   if (node_ptr != nullptr) { 
     // Copy node
     new_tree_ptr = new BinaryNode<ItemType, OtherType>(node_ptr->GetItem());
     new_tree_ptr->SetOther(node_ptr->GetOther());

     new_tree_ptr->SetLeftPtr(CopyTree(node_ptr->GetLeftPtr()));
     new_tree_ptr->SetRightPtr(CopyTree(node_ptr->GetRightPtr()));
   }  // end if
   return new_tree_ptr;
}  // end copyTree

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::DestroyTree(BinaryNode<ItemType, OtherType>* node_ptr)
{
   if (node_ptr != nullptr) {
      DestroyTree(node_ptr->GetLeftPtr());
      DestroyTree(node_ptr->GetRightPtr());
      delete node_ptr;
   }  // end if
}  // end destroyTree

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Preorder(void visit(ItemType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      ItemType theItem = node_ptr->GetItem();
      visit(theItem);
      Preorder(visit, node_ptr->GetLeftPtr());
      Preorder(visit, node_ptr->GetRightPtr());
   }  // end if
}  // end preorder

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Inorder(void visit(ItemType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      Inorder(visit, node_ptr->GetLeftPtr());
      ItemType theItem = node_ptr->GetItem();
      visit(theItem);
      Inorder(visit, node_ptr->GetRightPtr());
   }  // end if
}  // end inorder

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Inorder(void visit(ItemType&, OtherType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
  //Overloaded InOrder so that a void function can perform actions on both ItemType and OtherType
   if (node_ptr != nullptr)
   {

      Inorder(visit, node_ptr->GetLeftPtr());
      ItemType theItem = node_ptr->GetItem();
      OtherType theOther = node_ptr->GetOtherReference();
      visit(theItem,theOther);
      Inorder(visit, node_ptr->GetRightPtr());
   }  // end if
}  // end Overloaded inorder

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Levelorder(void visit(ItemType&, OtherType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
  //if function recieves a nullptr in node_pter
  if(node_ptr == nullptr) 
    return;
  //make a queue that stores ptrs to binary nodes
  queue<BinaryNode<ItemType, OtherType>* > Q;
  //Push node
  Q.push(node_ptr);
  while(!Q.empty())
  {
    BinaryNode<ItemType, OtherType>* current = Q.front();
      ItemType theItem = current->GetItem();
      OtherType theOther = current->GetOtherReference();
      //Perform action on current items item and other item
      visit(theItem,theOther);
    //Push current's children into queue
    if(current->GetLeftPtr() != nullptr)
      Q.push(current->GetLeftPtr());
    if(current->GetRightPtr() != nullptr)
      Q.push(current->GetRightPtr());
    //pop current
    Q.pop();
  }
}  // end Overloaded levelorder

template<class ItemType, class OtherType>
void BinarySearchTree<ItemType, OtherType>::Postorder(void visit(ItemType&), BinaryNode<ItemType, OtherType>* node_ptr) const
{
   if (node_ptr != nullptr)
   {
      Postorder(visit, node_ptr->GetLeftPtr());
      Postorder(visit, node_ptr->GetRightPtr());
      ItemType theItem = node_ptr->GetItem();
      visit(theItem);
   } // end if
}  // end postorder








