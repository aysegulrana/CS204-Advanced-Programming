#ifndef _SORTEDARRAY
#define _SORTEDARRAY

#include <iostream>

using namespace std;

class ArrayNode {
public:
	int val;
	ArrayNode *right;
	ArrayNode() {};
	ArrayNode(int val) :val(val), right(nullptr) {};
};


class SortedArray {
public:
	SortedArray();

	//we need deep copy implementation for copy constructor
	//createClone and cloneHelper will do the real work
	SortedArray(const SortedArray &);

	//we need to destruct all the nodes in the linkedlist
	//complete the implementation of this
	~SortedArray();

	bool search(int Value);
	void insert(int Value);
	void deleteSortedArray();
	void print();
	ArrayNode * getFront()const;
	void SetFront(ArrayNode * newFront);

	//implement this function in the cpp file
	ArrayNode* createClone() const;

	//Define and implement = operator for assignments and cascading assignment
	SortedArray  & SortedArray::operator= (SortedArray &x);

private:

	//complete the implementation of this function in cpp file
	void cloneHelper(ArrayNode* source, ArrayNode*& destination) const;

	ArrayNode *front;

};

SortedArray &operator+ (SortedArray &x, SortedArray& y);
SortedArray &operator+(SortedArray &lhs, const int &rhs);
SortedArray &operator+(const int &lhs, SortedArray &rhs);
//Define and implement + operators

#endif