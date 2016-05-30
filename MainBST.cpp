//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

#include "BinarySearchTree.h"  // ADT binary tree operations
#include <iostream>
#include <string>

using namespace std;

void display(string& anItem)
{
   cout << "Displaying item - " << anItem << endl;
}  // end display

void check(bool success)
{
   if (success)
      cout << "Done." << endl;
   else
      cout << " Entry not in tree." << endl;
}  // end check

int main()
{
  BinarySearchTree<string, int>* tree1Ptr = new BinarySearchTree<string, int>();
   
  tree1Ptr->Add("70", 100);
  tree1Ptr->Add("50", 2); 
  tree1Ptr->Add("40", 1);
  tree1Ptr->Add("10", 10);
  tree1Ptr->Add("20", 1);
  tree1Ptr->Add("30", 1);
  tree1Ptr->Add("60", 1);
  tree1Ptr->Add("80", 1);
   
   cout << "Tree 1 Preorder: \n";
   tree1Ptr->PreorderTraverse(display);
   
   cout << "Tree 1 Inorder: \n";
   tree1Ptr->InorderTraverse(display);
   
   cout << "Tree 1 Postorder: \n";
   tree1Ptr->PostorderTraverse(display);
   
   cout << "Tree 1 height: " << tree1Ptr->GetHeight() << endl;
   cout << "Tree 1 number of nodes: " << tree1Ptr->GetNumberOfNodes() << endl;   

   return 0;
}  // end main
