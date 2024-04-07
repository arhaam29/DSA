
#include <string>

struct Node
{
    Node *child[26];
    bool end;
    Node(){
	for (int i = 0; i < 26; i++){
		child[i] = nullptr;
	}
	end = false;
}
};

class Trie
{
 
 Node *root;

public:
    Trie();
    Trie(const std::string wordList[], int sz);
    void addWord(const std::string &newWord);
    bool lookup(const std::string &word) const;
    int beginsWith(const std::string &prefix, std::string resultList[]) const;
    ~Trie();
};
