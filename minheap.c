#include "minheap.h"

/*int main() {
	int i = 0, j = 0;
	newheap();
	heapgethead();
	
	for(i = 16; i > 1; i--) {
		heapinsert(2, i);
	}
	for(i = 1; i < numElements + 1; i++) {
		printf("Node %d -> key: %d\tvalue: %d\n", i, readyList[i].key, readyList[i].value);
	}
	
	heapinsert(2, 2);
	heapinsert(1, 1);
	heapinsert(7, 7);
	heapinsert(5 ,5);
	heapinsert(6, 6);

	for(i = 1; i < numElements + 1; i++) {
		printf("Node %d -> key: %d\tvalue: %d\n", i, readyList[i].key, readyList[i].value);
	}
	heapgetitem(2);
	
	printf("\n");
	for(i = 1; i < numElements + 1; i++) {
		printf("Node %d -> key: %d\tvalue: %d\n", i, readyList[i].key, readyList[i].value);
	}
	
	heapgetitem(6);
	
	printf("\n");
	for(i = 1; i < numElements + 1; i++) {
		printf("Node %d -> key: %d\tvalue: %d\n", i, readyList[i].key, readyList[i].value);
	}
	
	heapgethead();
	printf("\n");
	for(i = 1; i < numElements + 1; i++) {
		printf("Node %d -> key: %d\tvalue: %d\n", i, readyList[i].key, readyList[i].value);
	}
}*/

//creates the new heap, return OK or SYSERR.
//status newheap() {
void newheap() {
	arraySize = 10;//20;
	numElements = 0;
	readyList = (node *) malloc(arraySize * sizeof(node));
	//return OK;
}

//insert a process of PID with the given key into the heap
//status heapinsert( pid32 pid, int32 key) {
void heapinsert(int pid, int key) {
	//verifies there is space in the heap
	if (numElements + 1 == arraySize) {
		reSizeArray();
	}
	
	node n;
	n.key = key;
	n.value = pid;
	numElements++;
	readyList[numElements] = n;
	int nLoc = numElements;
	
	int parentLoc = getParent(numElements);
	
	//if we are inserting the root node no need to continue
	if (parentLoc == -1) {
		return;
	}
	node parent;
	
	while (parentLoc > 0) {
		parent = readyList[parentLoc];
		
		if (n.key < parent.key) {
			//n key is smaller
			readyList[parentLoc] = n;
			readyList[nLoc] = parent;
			nLoc = parentLoc;
		} else {
			//parent has smaller key
			break;
		}
		parentLoc = getParent(nLoc);
	}
}

//removes the root node and return its process id.
int heapgethead() {
	node rightChild;
	int rightChildLoc;
	node leftChild;
	int leftChildLoc;
	int nLoc;
	
	//verifies that we have a root node
	if (numElements == 0) {
		return -1;
	}
	
	node root = readyList[1]; //node with the value we need to return
	node n = readyList[numElements]; //last entry in the heap
	numElements--;
	
	//switch the first entry out with the last entry
	readyList[1] = n;
	
	nLoc = 1;
	rightChildLoc = getRightChild(nLoc);
	leftChildLoc = getLeftChild(nLoc);

	while(rightChildLoc > 0 || leftChildLoc > 0) {
		if (rightChildLoc > 0) {
			rightChild = readyList[rightChildLoc];
		} else {
			rightChild = readyList[0];
			rightChild.key = MAXKEY;
		}
		
		if(leftChildLoc > 0) {
			leftChild = readyList[leftChildLoc];
		} else {
			leftChild = readyList[0];
			leftChild.key = MAXKEY;
		}
		
		//children are not less than n
		if (n.key < leftChild.key && n.key < rightChild.key) {
			break;
			
		} else if (n.key > leftChild.key && n.key > rightChild.key) {

			//both children are less than n so check which is smaller
			if (leftChild.key > rightChild.key) {
				//swap in the right child
				readyList[nLoc] = rightChild;
				readyList[rightChildLoc] = n;
				nLoc = rightChildLoc;
			} else {
				//swap in the left child
				readyList[nLoc] = leftChild;
				readyList[leftChildLoc] = n;
				nLoc = leftChildLoc;
			}
		} else if (n.key > leftChild.key) {
			//swap in the left child
			readyList[nLoc] = leftChild;
			readyList[leftChildLoc] = n;
			nLoc = leftChildLoc;
			
		} else if (n.key > rightChild.key) {
			//swap in the right child
			readyList[nLoc] = rightChild;
			readyList[rightChildLoc] = n;
			nLoc = rightChildLoc;
		}
		
		leftChildLoc = getLeftChild(nLoc);
		rightChildLoc = getRightChild(nLoc);
	}
	
	return root.value;
}

//returns the key value at the root node of the heap without removing the node.
int heapminkey() {
	if(numElements != 0) {
		//heap has a root node
		return readyList[1].key;
	} else {
		//heap is empty
		return -1;
	}
}

//find and remove the process with the given pid from the heap. Status returns the process id or SYSERR 
int heapgetitem(int item) {
	int i = 0;
	node returnNode;
	node rightChild;
	int rightChildLoc;
	node leftChild;
	int leftChildLoc;
	int nLoc;
	
	//find the node with the value in item
	while(readyList[i].value != item) {
		i++;
		
		//verifies that we don't go out of bounds of the array
		if (i > numElements) {
			return -1;
		}
	}
	
	returnNode = readyList[i];
	node n = readyList[numElements];
	readyList[i] = n;
	numElements--;
	
	//remove the node from the heap
	nLoc = i;
	rightChildLoc = getRightChild(nLoc);
	leftChildLoc = getLeftChild(nLoc);
	
	while(rightChildLoc > 0 || leftChildLoc > 0) {
		if (rightChildLoc > 0) {
			rightChild = readyList[rightChildLoc];
		} else {
			rightChild = readyList[0];
			rightChild.key = MAXKEY;
		}
		
		if(leftChildLoc > 0) {
			leftChild = readyList[leftChildLoc];
		} else {
			leftChild = readyList[0];
			leftChild.key = MAXKEY;
		}
		
		//children are not less than n
		if (n.key < leftChild.key && n.key < rightChild.key) {
			break;
			
		} else if (n.key > leftChild.key && n.key > rightChild.key) {
			//both children are less than n so check which is smaller
			if (leftChild.key > rightChild.key) {
				//swap in the right child
				readyList[nLoc] = rightChild;
				readyList[rightChildLoc] = n;
				nLoc = rightChildLoc;
			} else {
				//swap in the left child
				readyList[nLoc] = leftChild;
				readyList[leftChildLoc] = n;
				nLoc = leftChildLoc;
			}
		} else if (n.key > leftChild.key) {
			//swap in the left child
			readyList[nLoc] = leftChild;
			readyList[leftChildLoc] = n;
			nLoc = leftChildLoc;
			
		} else if (n.key > rightChild.key) {
			//swap in the right child
			readyList[nLoc] = rightChild;
			readyList[rightChildLoc] = n;
			nLoc = rightChildLoc;
		}
		
		leftChildLoc = getLeftChild(nLoc);
		rightChildLoc = getRightChild(nLoc);
	}
	
	return returnNode.value;
}

void reSizeArray() {
	//printf("ResizeCalled\n");
	arraySize = arraySize * 2;
	readyList = (node *)realloc(readyList, (arraySize * sizeof(node)));
}

int getParent(int location) {
	if (location == 1 || location == 0) {
		return -1;
	}
	
	if (location % 2 != 0) {
		return (location - 1) / 2;
	} else {
		return location / 2;
	}
	
	return -1;
}

int getLeftChild(int location) {
	if ((2 * location) > arraySize) {
		return -1;
	}

	if ((2 * location) > numElements) {
		return -1;
	}
	return 2 * location;
}

int getRightChild(int location) {
	if (((2 * location) + 1) > arraySize) {
		return -1;
	}
	
	if ((2 * location + 1) > numElements) {
		return -1;
	}
	
	return (2 * location) + 1;
}










