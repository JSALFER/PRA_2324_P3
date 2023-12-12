all: testTableEntry testHashTable

testTableEntry: testTableEntry.cpp TableEntry.h
	g++ -o testTableEntry testTableEntry.cpp

testHashTable: testHashTable.cpp Dict.h HashTable.h TableEntry.h
	g++ -o testHashTable testHashTable.cpp
	
clean: 
	rm -rf *.o *.gch 
