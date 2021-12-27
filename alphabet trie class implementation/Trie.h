#ifndef _TRIE
#define _TRIE

#include <string>
#include <iostream>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
	bool isWord;
	bool visited;
	TrieNode * children[ALPHABET_SIZE];
	TrieNode(){
		this->isWord = false;
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			this->children[i] = nullptr;
		}
	};
};


class Trie {
	friend class TrieIterator;

public:
	Trie(); // Constructor
	Trie(const Trie &); // Copy constructor
	Trie(Trie &&); // Move constructor
	~Trie(); // Destructor

	bool searchWord(string word);
	void insertWord(string word);
	void deleteWord(string word);
	bool isEmpty() const;
	void deleteTrie();
	int length();

	/*******************************************************************/
	/*                      DEFINE YOUR OPERATORS HERE                 */

	/*******************************************************************/
	bool operator == (const Trie &tr);
	bool operator != (const Trie &tr);
	Trie & operator = (const Trie &rhs);
	Trie & operator += (const Trie & tr);	
	Trie & operator += (const string & str);
	Trie operator + (Trie &rhs);
	Trie operator+(const string &rhs);


	//implement this function
	TrieNode * createClone() const;

	friend Trie operator+(const string &lhs, Trie &rhs);
	//friend Trie &operator+(Trie &lhs, const string &rhs);
	friend ostream &operator << (ostream & os, Trie &rhs);

private:
	TrieNode * root;
	int size; // update size at every insertion and deletion
	// so that, every time length function called 
	// don't iterate all list.

	// helper function
	void lower(string & word);
	bool deleteWordHelper(TrieNode *& , string);
	bool hasChildren(TrieNode * node, int) const;
	void printHelper(ostream & os, TrieNode * node, string & word) const;
	void deleteTrieHelper(TrieNode * node);
	bool BooleanHelper (TrieNode* rhs, TrieNode* lhs);
	void AdditionHelper (TrieNode* source, TrieNode* dest);


	//complete the implementation of this function
	void cloneHelper(TrieNode* source, TrieNode*& destination) const;

};

Trie operator+(const string &lhs, Trie &rhs);
ostream &operator << (ostream & os, Trie &rhs);
#endif
