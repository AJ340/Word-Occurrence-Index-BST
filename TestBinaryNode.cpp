// A simple file to test a binary node.
// Ioannis Stamos

#include <iostream>
#include <string>
#include "BinaryNode.h"
using namespace std;

namespace {

// Simple function to test Node<> using static allocation.
void  TestBinaryNodes() {
  
  BinaryNode<int, string> a_node;
  cout << "The left child should be nullptr: " << (a_node.GetLeftPtr() == nullptr) << endl;
  cout << "The right child should be nullptr: " << (a_node.GetRightPtr() == nullptr) << endl;
  a_node.SetItem(10);
  cout << "The item should be 10: " << a_node.GetItem() << endl;
  cout << "The other item should be empty: " << a_node.GetOther() << endl;
  cout << "Setting the other item to TEST_OTHER: " << endl;
  a_node.GetOtherReference() = "TEST_OTHER";
  cout << "Other of node is " << a_node.GetOther() << endl;
}



} // end unnamed namespace

int
main() {
  TestBinaryNodes();
} 
