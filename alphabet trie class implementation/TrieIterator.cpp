#include "Stack.h"
#include "Trie.h"
#include "TrieIterator.h"


TrieIterator::TrieIterator(const Trie & myTrie)
	: myTrie(myTrie), currentNode(nullptr), currentWord("") {
}

// TODO: Implement this function
void TrieIterator::Init() {
	currentNode=myTrie.root;
	/*string word=""; bool found=false; int i=0; 
	currentNode=myTrie.root;

	while (!(currentNode->isWord)) {
		if (currentNode->children[i]) {
			word+=char('a'+i);
			stack.push(currentNode, i);
			currentNode=currentNode->children[i];
			i=-1;
		}
		i++;
	}*/
}

// TODO: Implement this function
void TrieIterator::Next() {
	int i=0;
	//bool found=false; int i=0, a; string word=""; TrieNode *x, *curr;
	currentNode=currentNode->children[i];
	/*stack.pop(curr, a); 

	while (!found) {

		if (!(myTrie.hasChildren(curr, a))){
			stack.pop(curr, a); 
		}
		else {
			stack.push(curr, a);
		}

		while (i<ALPHABET_SIZE && !found){

			if (curr->children[i] && !(curr->children[i]->isWord) && !(curr->children[i]->visited)){
				curr->children[i]->visited=true;
				stack.push(curr, a);
				stack.push(curr->children[i], i);
				curr=curr->children[i]; i=0;
			}
			else if (curr->children[i]->children[i] && curr->children[i]->children[i]->isWord) {

				stack.push(currentNode->children[i]->children[i], i);

				TrieNode *lettereverse, *letter;
				Stack y;
				while (!stack.isEmpty()){
					stack.pop(lettereverse, i);
					y.push(lettereverse, i);
				}

				while (!y.isEmpty()){
					y.pop(letter, i);
					word+=char('a'+i);
				}
				found=true;
			}
			i++;
		}
	}*/
	//currentWord=word;
}

// TODO: Implement this function
bool TrieIterator::HasMore() const {
	return (currentNode!=nullptr);
}

// TODO: Implement this function
string TrieIterator::Current() const {
	return currentWord;
}