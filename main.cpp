
#include "BinarySearchTree.h"  // ADT binary tree operations
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include "LinkedQueue.h"  



using namespace std;

//changes upercase characters to lowercase and changes anything thats not lowercase letters into spaces (delimiter)
void process(string& a)
{
  for(int i=0;i<a.size();i++)
  {
    a[i] = tolower(a[i]);
    if( (int)a[i] < 97 || (int)a[i] > 122)
      a[i] = ' ';
  }
}

//read line by line. process everyword on the line. add to tree. store 1 copy of each word into all_words
BinarySearchTree<string, LinkedQueue<int>>* createTreeFromDocument(string file, vector<string>& all_words)
{
  BinarySearchTree<string, LinkedQueue<int>>* tree1Ptr = new BinarySearchTree<string, LinkedQueue<int>>();
  cout << "1. Creating index(tree) for the document.\n";
  int lineNumber=1;

  string currentLine;
  ifstream textFile;
  textFile.open(file);
  while (getline(textFile,currentLine))
  {
    process(currentLine);
    istringstream iSS(currentLine);
    string word;
    while (iSS >> word)
    {
      bool inTree = tree1Ptr->Contains(word);
      if(inTree)
        tree1Ptr->GetOtherReference(word).Enqueue(lineNumber);
      else 
      {
        LinkedQueue<int> loc;
        loc.Enqueue(lineNumber);
        tree1Ptr->Add(word,loc);
        all_words.push_back(word);
      }
    }
    lineNumber++;
  }
  textFile.close();
  return tree1Ptr;
}
void display(string& anItem, LinkedQueue<int>& otherItem)
{
  cout <<"  "<< anItem << " :: " << "Count: " << otherItem.GetCount() << " ::" << " Lines: " << otherItem << endl;
}  // end display



int main(int argc, const char * argv[])
{

  if (argc!=2)
  {
    cout << "Invalid amount of arguments" << endl;
    return 1;
  }

  vector<string> words;
  vector<LinkedQueue<int> > locations;

  BinarySearchTree<string, LinkedQueue<int>>* tree1Ptr = createTreeFromDocument(argv[1],words);


  cout << "2. Printing out index in lexicographic order (inorderTraversal). \n";
  tree1Ptr->InorderTraverse(display);
  cout << "3. Printing out the total number of nodes in the tree. \n";
  cout << "  Total number of nodes: " << tree1Ptr->GetNumberOfNodes() << endl;
  cout << "4. Printing out the height of the tree. \n";
  cout << " Height: " << tree1Ptr->GetHeight() << endl;
  cout << "5. Finding word with maximum occurences.\n";
  // For each word, get the other of that word(reference) in the tree and store it in vector locations
  // words and location vecotors are associated with each other. (ex. word at words[1] is the word in the tree
  // with the locations data at locations[1])
  for (int i=0;i<words.size();i++)
    locations.push_back(tree1Ptr->GetOtherReference(words[i]));
  int maxPos=0; int globalMax=0;
  for (int i=0; i< locations.size();i++)
  {
    //Get the position of queue of locations with the most items. store it in maxpos and store the max sofar in global max
    int thisCount = locations[i].GetCount();
    if(locations[i].GetCount() > globalMax)
    {
      maxPos=i; globalMax=thisCount;
    }
  }

  cout << " Word with max occurences:\n";

  display(words[maxPos],locations[maxPos]); // demonstrates 1-1 in the two vectors
  cout << "6. Interactively search and display a word entered by user.\n";
  string userInput;
  cout << " Enter a word to search(will only search first word entered):\n";
  cin >> userInput;
  process(userInput);
  istringstream iSS(userInput);
  string in;
  iSS >> in;
  LinkedQueue<int> locInfo;
  if(tree1Ptr->Contains(in))
  {
    locInfo = tree1Ptr->GetOtherReference(in);
    cout << " Word Found:\n";
    display(in,locInfo);
  }
  else
  {
    cout << " Word Not Found.\n";
  }
  cout << endl << endl << endl;


  cout << "--------------------EXTRA CREDIT BELOW--------------------\n";
  cout << "1. Delete node from tree.\n";
  string userInput2;
  cout << "Enter a word to delete(will only use first word entered):\n";
  cin >> userInput2;
  process(userInput2);
  cout << " Delete returned ";

  if(tree1Ptr->Remove(userInput2))
    cout << "true\n";
  else
    cout << "false\n";
  cout << " Searching for word now.\n";
  bool found = tree1Ptr->Contains(userInput2);
  if(found == true)
    cout << "Word still in tree.\n";
  else 
    cout << "Word not in tree.\n";
  cout << "2. Display the tree in a level-order traversal.\n";
  tree1Ptr->LevelorderTraverse(display);
  return 0;
}  // end main
