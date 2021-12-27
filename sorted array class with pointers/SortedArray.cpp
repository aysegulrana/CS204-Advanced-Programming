#include "SortedArray.h"

SortedArray::SortedArray() {
	front = nullptr;
}

//impelent copy constructor
SortedArray::SortedArray(const SortedArray & copy) {
	front = copy.createClone();

}

//implement destructor
SortedArray::~SortedArray() {
	ArrayNode * ptr = front;
	while (ptr != NULL) 
	{
		ArrayNode* temp = ptr->right;
		delete ptr;
		ptr = temp;
	}
}

ArrayNode * SortedArray::getFront() const{
	return front;
}

void SortedArray::SetFront(ArrayNode * newFront){
	front = newFront;
}

// implement this function
void SortedArray::cloneHelper(ArrayNode * source, ArrayNode *& destination) const {

}

// implement this function
ArrayNode * SortedArray::createClone() const{
	if (front == nullptr) {
		return nullptr;  } //if the one we're trying to copy is empty then we'll assign the lhs to empty too

	ArrayNode *front_clone = new ArrayNode (front->val); //we made a clone of the first node of the one will be copied.
	ArrayNode *sec=front->right; //this is pointing to the second node, we will go around with this
	ArrayNode *ptr=front_clone; //this is going around the new array 

	while(sec){ //while there's node to point
		ptr->right = new ArrayNode (sec->val); //we make new nodes copied from source
		sec=sec->right; 
		ptr=ptr->right;
	}
	return front_clone;
}

bool SortedArray::search(int Value)
{
	ArrayNode * tmp = front;
	while (tmp) {
		if (tmp->val == Value) {
			return true;
		}
		tmp = tmp->right;
	}
	return false;
}

void SortedArray::insert(int Value) {
	if (!search(Value)) {
		ArrayNode * tmp = front;

		ArrayNode * newNode = new ArrayNode(Value);
		if (!front) {
			front = newNode;
		}
		else if (front && Value < front->val) {
			newNode->right = front;
			front = newNode;
		}
		else {
			while (tmp->right && tmp->right->val < Value) {
				tmp = tmp->right;
			}
			newNode->right = tmp->right;
			tmp->right = newNode;
		}
	}
}

void SortedArray::deleteSortedArray() {
	ArrayNode * current = front, *next = front;
	while (current) {
		next = current->right;
		delete current;
		current = next;
	}
	front = nullptr;
}

void SortedArray::print() {
	if (!front) {
		cout << "Array is empty" << endl;
	}
	ArrayNode * tmp = front;
	while (tmp) {
		cout << tmp->val << " ";
		tmp = tmp->right;
	}
	cout << endl;
}

SortedArray & SortedArray::operator = (SortedArray &rhs){
	if (this != &rhs)
	{
		deleteSortedArray(); //we need to delete the lhs in order to make it equal to the rhs 
		front = rhs.createClone(); //we called create clone function and now we have a deep copied new array as lhs
	}
	return *this;
}

SortedArray &operator+(SortedArray &lhs, SortedArray& rhs){

	ArrayNode*ptr_rhs=rhs.getFront(); //we point to the first el. of the array with this.
	ArrayNode*right_follower=rhs.getFront()->right; //we are pointing to the sec el.

	ArrayNode*x;
	x=lhs.createClone(); //we created a clone of lhs, we will add things to that clone and get a  new array which is the sum of two arrays

	SortedArray* z=new SortedArray();
	z->SetFront(x); //we assigned front of our new array as front of x which was a copy of lhs. now z is pointing to a sorted array which is the copy of lhs

	z->insert(ptr_rhs->val); //we inserted the first value of rhs
	while (right_follower){ //we will continue till the array ends, the pointer stops pointing to an element
		z->insert(right_follower->val); //we're inserting the elements of the array in each iteration of the loop
		right_follower=right_follower->right;
	}
	return *z;
}

SortedArray &operator+(SortedArray &lhs, const int &rhs){

	ArrayNode*x;
	x=lhs.createClone(); //we created a clone of the lhs array and x pointer is pointing to that 

	SortedArray* z = new SortedArray(); //our array should be sorted so we made a sorted array type pointer
	z->SetFront(x); //we set the front of array as x, which is looking to the copy of lhs now we have a sorted array which is the same as lhs
	z->insert(rhs); //we inserted the number in the addition 
	return *z; //we returned the array which is pointed by z
}

SortedArray &operator+(const int &lhs, SortedArray &rhs){ //we did the same as the upper part but the locations of int and sorted array are switched

	ArrayNode*x;
	x=rhs.createClone();

	SortedArray* z = new SortedArray();
	z->SetFront(x);
	z->insert(lhs);
	return *z;
}