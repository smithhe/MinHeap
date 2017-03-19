#include <stdio.h>
#include <stdlib.h>

#define MAXKEY 2147483647

typedef struct node {
	int value;
	int key;
} node;

int arraySize;
int numElements;

node *readyList;

//creates the new heap, return OK or SYSERR.
void newheap();

//insert a process of PID with the given key into the heap
void heapinsert(int pid, int key);

//removes the root node and return its process id.
int heapgethead();

//returns the key value at the root node of the heap without removing the node.
int heapminkey();

//find and remove the process with the given pid from the heap. Status returns the process id or SYSERR 
int heapgetitem(int);

//resizes the array if needed
void reSizeArray();

//gets the parent node
int getParent(int location);

//gets the left child node
int getLeftChild(int location);

//gets the right child node
int getRightChild(int location);
