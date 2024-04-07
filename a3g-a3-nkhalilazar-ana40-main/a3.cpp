#include "a3.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int getIdx(char ch) {
	return ch - 'a';
}
char getLetter(int num) {
	return 'a' + num;
}


Trie::Trie(const std::string wordList[], int sz){
	root = nullptr;
	for (int i = 0; i < sz; i++){
		addWord(wordList[i]);
	}
}

void Trie::addWord(const std::string& newWord){
		if (!root){
			root = new Node;
		}

		Node* curr = root;
		
		for (int i = 0; i < newWord.length(); i++){
			int idx=getIdx(newWord[i]);
			if (curr->child[idx]){
				curr = curr->child[idx];
			}
			else{
				curr->child[idx] = new Node;
				curr = curr->child[idx];
			}
		}
		curr->end = true;
}

bool Trie::lookup(const std::string& word) const{

	if(root){

		Node* curr = root;

	for (int i = 0; i < word.length(); i++){
		int idx=getIdx(word[i]);
		if (curr->child[idx] == nullptr)
			return false;
		else
			curr = curr->child[idx];
	}
	
	return curr->end;
	}
	
	return false;
	
	
}

int Trie::beginsWith(const std::string& prefix, std::string resultList[]) const{
	if (root) {
	Node* curr = root;
	for (int i = 0; i < prefix.length(); i++) {
		int idx = getIdx(prefix[i]);
		if (curr->child[idx] == nullptr) {
			return 0;
		}
		curr = curr->child[idx];
	}
	
	// At this point, curr points to the last node corresponding to the prefix
	int count = 0;
	if (curr->end) {
		resultList[count++] = prefix;
	}
	
	// Traverse the subtree rooted at curr to find all words that begin with the prefix
	for (int i = 0; i < 26; i++) {
		if (curr->child[i] != nullptr) {
			std::string newPrefix = prefix + getLetter(i);
			count += beginsWith(newPrefix, &resultList[count]);
		}
	}
	
	return count;
	}
	return 0;
}

Trie::~Trie(){
	delete root;
	root=nullptr;
}
