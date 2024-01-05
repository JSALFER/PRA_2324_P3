all: testTableEntry testHashTable testBSTree testBSTreeDict

testTableEntry: testTableEntry.cpp TableEntry.h
	g++ -o testTableEntry testTableEntry.cpp

testHashTable: testHashTable.cpp Dict.h HashTable.h TableEntry.h
	g++ -o testHashTable testHashTable.cpp
	
testBSTree: BSTree.h BSNode.h testBSTree.cpp
	g++ -o testBSTree testBSTree.cpp

testBSTreeDict: testBSTreeDict.cpp Dict.h BSTreeDict.h BSNode.h TableEntry.h 
	g++ -o testBSTreeDict testBSTreeDict.cpp
	
clean: 
	rm -rf *.o *.gch 
