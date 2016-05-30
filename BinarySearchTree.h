 //  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 16-4.
// Modified by Ioannis Stamos


/** Link-based implementation of the ADT binary search tree.
 @file BinarySearchTree.h */
 
#ifndef TEACH_CSCI235_BST_BINARY_SEARCH_TREE_H
#define TEACH_CSCI235_BST_BINARY_SEARCH_TREE_H

#include "BinaryTreeInterface.h"
#include "NotFoundException.h"
#include "BinaryNode.h"

template<class ItemType, class OtherType>
  class BinarySearchTree : public BinaryTreeInterface<ItemType, OtherType>
{
 public:
 BinarySearchTree(): root_(nullptr) { };

  BinarySearchTree(const BinarySearchTree<ItemType, OtherType>& tree);
  BinarySearchTree& operator=(const BinarySearchTree<ItemType, OtherType>& right_hand_side);
  virtual ~BinarySearchTree();
  

  bool IsEmpty() const;
  int GetHeight() const;
  int GetNumberOfNodes() const;
  bool Add(const ItemType& item, const OtherType& other); 
  bool Remove(const ItemType& data); // Removes a node
  void Clear();
  
  OtherType GetOther(const ItemType& an_item) const throw(NotFoundException);
  OtherType &GetOtherReference(const ItemType& an_item) throw(NotFoundException);
  bool Contains(const ItemType& an_item) const;
   
  //------------------------------------------------------------
  // Public Traversals Section.
  //------------------------------------------------------------
  void PreorderTraverse(void visit(ItemType&)) const;
  void InorderTraverse(void visit(ItemType&)) const;
  //Overloaded InOrder so that a void function can perform actions on both ItemType and OtherType
  void InorderTraverse(void visit(ItemType&, OtherType&)) const;
  //EC: Levelorder. traverses tree each level at a time
  void LevelorderTraverse(void visit(ItemType&, OtherType&)) const;
  void PostorderTraverse(void visit(ItemType&)) const;
  //------------------------------------------------------------

 private:
  BinaryNode<ItemType, OtherType>* root_;
  
  int GetHeightHelper(BinaryNode<ItemType, OtherType>* node_ptr) const;
  int GetNumberOfNodesHelper(BinaryNode<ItemType, OtherType>* node_ptr) const;
  
  // Recursively deletes all nodes from the tree.
  void DestroyTree(BinaryNode<ItemType, OtherType>* node_ptr);
  
  
  // Recursively finds where the given node should be placed and
  // inserts it in a leaf at that point.
  BinaryNode<ItemType, OtherType>* InsertInorder(BinaryNode<ItemType, OtherType>* subTreePtr,
						 BinaryNode<ItemType, OtherType>* newNode);
  
  // Removes the given target value from the tree while maintaining a
  // binary search tree.
  BinaryNode<ItemType, OtherType>* RemoveValue(BinaryNode<ItemType, OtherType>* subTreePtr,
					       const ItemType target,
					       bool& success);
  
  // Removes a given node from a tree while maintaining a
  // binary search tree.
  BinaryNode<ItemType, OtherType>* RemoveNode(BinaryNode<ItemType, OtherType>* nodePtr);
  
  // Removes the leftmost node in the left subtree of the node
  // pointed to by nodePtr.
  // Sets inorderSuccessor to the value in this node.
  // Returns a pointer to the revised subtree.
  BinaryNode<ItemType, OtherType>* RemoveLeftmostNode(BinaryNode<ItemType, OtherType>* subTreePtr,
						      ItemType& IinorderSuccessor,OtherType& OinorderSuccessor);
  
  // Returns a pointer to the node containing the given value,
  // or nullptr if not found.
  BinaryNode<ItemType, OtherType>* FindNode(BinaryNode<ItemType, OtherType>* treePtr,
					    const ItemType& target) const;
  
  // Copies the tree rooted at treePtr and returns a pointer to
  // the copy.
  BinaryNode<ItemType, OtherType>* CopyTree(const BinaryNode<ItemType, OtherType>* node_ptr) const;
  
  // Recursive traversal helper methods:
  void Preorder(void visit(ItemType&), BinaryNode<ItemType, OtherType>* node_ptr) const;
  void Inorder(void visit(ItemType&), BinaryNode<ItemType, OtherType>* node_ptr) const;
  //Overloaded InOrder so that a void function can perform actions on both ItemType and OtherType
  void Inorder(void visit(ItemType&, OtherType&), BinaryNode<ItemType, OtherType>* node_ptr) const;
  //EC: Levelorder. traverses tree each level at a time
  void Levelorder(void visit(ItemType&, OtherType&), BinaryNode<ItemType, OtherType>* node_ptr) const;
  void Postorder(void visit(ItemType&), BinaryNode<ItemType, OtherType>* node_ptr) const;
  
}; // end BinarySearchTree

#include "BinarySearchTree.cpp"

#endif  // TEACH_CSCI235_BST_BINARY_SEARCH_TREE_H
