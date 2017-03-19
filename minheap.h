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

//creates the new heap
void newheap();

//insert a new node into the heap
void heapinsert(int value, int key);

//removes the root node and return its value.
int heapgethead();

//returns the value at the root node of the heap without removing the node.
int heapminkey();

//find and remove the node with the given value from the heap.
int heapgetitem(int);

//resizes the array if needed
void reSizeArray();

//gets the parent node
int getParent(int location);

//gets the left child node
int getLeftChild(int location);

//gets the right child node
int getRightChild(int location);
