#include "Trie.h"
#include "TrieIterator.h"
#include <iostream>
#include <sstream>

Trie::Trie(){
	this->root = new TrieNode();
	this->size = 0;
}

// TODO: Implement this function
Trie::Trie(const Trie & copy){

	cout << "Copy constructor called" << endl;

	root = copy.createClone();
}

// TODO: Implement this function
Trie::Trie(Trie && move):root(nullptr), size(0){

	cout << "Move constructor called" << endl;
	std::swap(this->root, move.root); //we do shallow copy with move
	std::swap(this->size, move.size); 
}

// TODO: Implement this function
Trie::~Trie(){

	cout << "Destructor called" << endl;

	this->deleteTrie();

}


// TODO: Implement this function
TrieNode * Trie::createClone() const {

	TrieNode* ptr;
	ptr=this->root;
	Trie* ourtr=new Trie();
	TrieNode *newptr=ourtr->root; 

	cloneHelper(ptr, newptr);

	ourtr->size=this->size;

	return newptr;
}


// TODO: Implement this function
void Trie::cloneHelper(TrieNode* source, TrieNode*& destination) const {

	if (source!=nullptr){
		if (source->isWord){
			destination->isWord=true;
		}
		else {
			destination->isWord=false;
		}
		for (int i=0; i < ALPHABET_SIZE; i++){
			if (source->children[i]!=nullptr){
				destination->children[i] = new TrieNode(); //we make a copy of each node for the node that we created 
				cloneHelper(source->children[i], destination->children[i]);
			}
		}
	}
}
/*******************************************************************/
/*                      DEFINE YOUR OPERATORS HERE                 */
/*******************************************************************/

bool Trie::BooleanHelper (TrieNode* rhs, TrieNode* lhs){ //this helper functin checks if two tries are equal

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (rhs->children[i]) {
			if (lhs->children[i]) {
				BooleanHelper (rhs->children[i], lhs->children[i]); //we recursiveley look at every node if they are equal
			}
			else {
				return false; //if one node doesn't exist in the other trie we now they are not equal so we return false
			}
		}
	}
	return true;
}

bool Trie::operator == (const Trie &tr){
	TrieNode* rhs=tr.root;
	TrieNode* lhs=this->root;
	bool equal=BooleanHelper(rhs, lhs);
	return equal;
}

bool Trie::operator != (const Trie &tr){

	TrieNode* rhs=tr.root;
	TrieNode* lhs=this->root;
	bool equal=!(BooleanHelper(rhs, lhs)); //this gives just the opposite of ==
	return equal;

}

Trie &Trie::operator = (const Trie &rhs){

	if (this!=&rhs){
		deleteTrie();
		root=rhs.createClone(); 
	}
	return *this;

}

Trie & Trie::operator += (const string & str){
	(*this).insertWord(str); //we just insert the word to add
	this->size+=1;
	return *this;
}

void Trie::AdditionHelper (TrieNode* source, TrieNode* dest){ //this function adds to tries source has the nodes that will be added

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (source->children[i]) { //if source has children at ith node we add that children node to destination.
			if (!(dest->children[i])){ //if dest has already have a children there we won't add it
				dest->children[i]=new TrieNode(); 
				dest->children[i]->isWord=source->children[i]->isWord;
				AdditionHelper (source->children[i], dest->children[i]);
			}
			else {
				AdditionHelper (source->children[i], dest->children[i]);
			}
		}
	}

}

Trie & Trie::operator += (const Trie & tr){

	TrieNode* source=tr.root;
	TrieNode* dest=this->root;
	AdditionHelper (source, dest); //we use the same helper function with + operator
	this->size+=tr.size;

	return *this;
}

Trie Trie::operator + (Trie &rhs){

	TrieNode* newtrie;
	newtrie=this->createClone(); 
	TrieNode* rhsx=rhs.root;

	AdditionHelper (rhsx, newtrie);

	Trie x;
	x.root=newtrie; //we assign the destination node that we added up to a new trie

	return x;
}

Trie operator + (const string &lhs, Trie &rhs){

	TrieNode* newtrie;
	newtrie=rhs.createClone();
	Trie ourtr;
	ourtr.root=newtrie;

	ourtr.insertWord(lhs);
	ourtr.size+=1;
	return ourtr;

}

Trie Trie ::operator + (const string &rhs){

	TrieNode* newtrie;
	newtrie=this->createClone();
	Trie ourtr;
	ourtr.root=newtrie;

	ourtr.insertWord(rhs);
	ourtr.size+=1;
	return ourtr;

}

ostream &operator << (ostream& os, Trie &rhs){

	string word="";
	TrieNode* y = rhs.root;
	Trie obj;
	if (y){ //if it is not nullptr
		obj.printHelper(os, y, word); //print helper helps to print each word
	}
	else {
		cout<<"Trie is empty."<<endl;
	}
	return os;
}

bool Trie::searchWord(string word) {
	lower(word);
	TrieNode * ptr = root;
	int len = word.length();
	for (int i = 0; i < len; i++) {
		int targetIndex = word.at(i) - 'a';
		if (!ptr->children[targetIndex]) {
			return false;
		}
		ptr = ptr->children[targetIndex];
	}
	if (ptr->isWord) {
		return true;
	}
	return false;
}

void Trie::lower(string & word) {
	string res;
	for (char c : word) {
		if (c >= 'A' && c < 'a') {
			res += (c - 'A' + 'a');
		}
		else {
			res += c;
		}
	}
	word = res;
}


void Trie::insertWord(string word) {
	lower(word);
	if (!searchWord(word)) {
		TrieNode * ptr = root;
		int len = word.length();
		for (int i = 0; i < len; i++) {
			int targetIndex = word.at(i) - 'a';
			if (!ptr->children[targetIndex]) {
				ptr->children[targetIndex] = new TrieNode();
			}
			//			ptr->isLeaf = false;
			ptr = ptr->children[targetIndex];
		}
		ptr->isWord = true;
		size += 1;
	}
}

bool Trie::hasChildren(TrieNode * node, int i = 0) const {
	if (node) {
		for (i; i < ALPHABET_SIZE; i++) {
			if (node->children[i]) {
				return true;
			}
		}
	}
	return false;
}

void Trie::deleteWord(string word) {
	lower(word);
	if (searchWord(word)) {
		if (deleteWordHelper(root, word)) {
			size--;
		}
	}
}

bool Trie::isEmpty() const {
	return !(this->hasChildren(root));
}

bool Trie::deleteWordHelper(TrieNode *& node, string word) {
	if (word.length()) {
		if (node != nullptr &&
			node->children[word[0] - 'a'] != nullptr &&
			deleteWordHelper(node->children[word[0] - 'a'], word.substr(1)) &&
			!node->isWord
			) {
				if (!hasChildren(node)) {
					delete node;
					node = nullptr;
					return true;
				}
				else {
					node->isWord = false;
					return true;
				}
		}
	}
	if (word.length() == 0 && node->isWord) {
		if (!hasChildren(node)) {
			delete node;
			node = nullptr;
			return true;
		}
		else {
			node->isWord = false;
			return false;
		}
	}
}

void Trie::printHelper(ostream & os, TrieNode * node, string & word) const {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (node->children[i]) {
			word += char(i + 'a');
			if (node->children[i]->isWord) {
				os << word << endl;
				printHelper(os, node->children[i], word);
			}
			else {
				printHelper(os, node->children[i], word);
			}
		}
		else if (i == 26) {
			word = word.substr(0, word.length() - 1);
		}
	}
	word = word.substr(0, word.length() - 1);
}

void Trie::deleteTrie() {
	if (root) {
		deleteTrieHelper(root);
		root = nullptr;
		size = 0;
	}
}

void Trie::deleteTrieHelper(TrieNode * node) {
	if (hasChildren(node)) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			if (node->children[i]) {
				deleteTrieHelper(node->children[i]);
			}
		}
	}
	delete node;
}

int Trie::length() {
	return size;
}