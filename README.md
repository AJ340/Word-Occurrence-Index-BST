# Word-Occurrence-Index-BST
CSCI 235

for more information see hw5.pdf
PDF property of Hunter College
also implimented Extra Credit described in aforementioned pdf

README 
Homework 5 by Andres Quinones for CSCI 235
Professor Ahmed

make all:
	generates the following commands 
	make TestBinaryNodeProgram
	g++ -g -std=c++0x -Wall -I.   -c TestBinaryNode.cpp -o TestBinaryNode.o
	g++ -g -std=c++0x -Wall -o ./TestBinaryNodeProgram TestBinaryNode.o -I.  -L/usr/lib -L/usr/local/lib -lm 
	ld: warning: directory not found for option '-L/usr/local/lib'
	make TextAnalysis
	g++ -g -std=c++0x -Wall -I.   -c NotFoundException.cpp -o NotFoundException.o
	g++ -g -std=c++0x -Wall -I.   -c PreconditionViolatedException.cpp -o PreconditionViolatedException.o
	g++ -g -std=c++0x -Wall -I.   -c main.cpp -o main.o
	g++ -g -std=c++0x -Wall -o ./TestTextAnalysisProgram NotFoundException.o PreconditionViolatedException.o main.o -I.  -L/usr/lib -L/usr/local/lib -lm 
	ld: warning: directory not found for option '-L/usr/local/lib'
	make TestBSTProgram
	g++ -g -std=c++0x -Wall -I.   -c MainBST.cpp -o MainBST.o
	g++ -g -std=c++0x -Wall -o ./TestBSTProgram NotFoundException.o MainBST.o -I.  -L/usr/lib -L/usr/local/lib -lm 
	ld: warning: directory not found for option '-L/usr/local/lib'

	Three programs are made:
		TestBinaryNodeProgram takes no additional arguments and just tests if BinaryNode is implimented properly
		TestBSTProgram also takes no additional arguments and just tests if the BST is implimented properly (the MainBST.cpp you provided)
		
		TextAnalysis is the main program
			it uses the BST implimentations in BinarySearchTree in order to perform the actions detailed in HW5.pdf
		ITS USAGE:
			./TextAnalysis <NAME_OF_TXT_FILE

		***** NOTE: I changed the signiture of RemoveLeftMostNode to this:
			BinaryNode<ItemType, OtherType>* RemoveLeftmostNode(BinaryNode<ItemType, OtherType>* subTreePtr,
						      ItemType& IinorderSuccessor,OtherType& OinorderSuccessor);
		-I added Oinordersuccessor for the case that the node deleted had 2 children. when we swap it with the in order successor we need both the ItemType variable and the OtherType variable to be where the deleted node was
			-Before, only the ItemType variable was swapped over. resulted in inaccurate data in the tree when some nodes were deleted.
