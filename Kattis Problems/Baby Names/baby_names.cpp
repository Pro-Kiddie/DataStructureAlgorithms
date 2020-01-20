//Matric number:  
//Full name:  
//Lab group number:  
//Lab group TA:  

#include <bits/stdc++.h>

using namespace std;

int COUNT;

struct TrieNode {
    struct TrieNode *children[26];
    bool isWordEnd;
    int gender;
    bool deleted;
};

struct TrieNode *getNode(void) {
    struct TrieNode *pNode = new TrieNode;
    pNode->isWordEnd = false;
    for (int i = 0; i < 26; i++)
        pNode->children[i] = NULL;
    return pNode;
}

int CHAR_TO_INDEX(char UPPERCASE) {
    return (int)(UPPERCASE - 'A');
}

void insert(struct TrieNode *root, const string key, const int gender) {
    struct TrieNode *pCrawl = root;
    for (int level = 0; level < key.length(); level++) {
        int index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }
    pCrawl->isWordEnd = true;
    pCrawl->gender = gender;
    pCrawl->deleted = false;
}

bool isLastNode(struct TrieNode *root) {
    for (int i = 0; i < 26; i++)
        if (root->children[i])
            return 0;
    return 1;
}

bool RemoveSuggestion(struct TrieNode *root, const string key) {
    int length = key.length();
    struct TrieNode *pCrawl = root;
    for (int level = 0; level < length; level++) {
        int index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }
    if(pCrawl == NULL) return false;
    if(pCrawl->isWordEnd) pCrawl->deleted = true;
    return true;
}

void suggestions(struct TrieNode *root, int gender) {
    // found a string in Trie with the given prefix
    if (root->isWordEnd && !root->deleted && (gender == 0 || root->gender == gender)) {
        COUNT++;
    }
    // All children struct node pointers are NULL
    if (isLastNode(root))
        return;
    for (int i = 0; i < 26; i++) {
        if (root->children[i]) {
            // recur over the rest
            suggestions(root->children[i], gender);
        }
    }
}

void FindSuggestions(TrieNode *root, const string prefix, int gender) {
    struct TrieNode *pCrawl = root;
    int level;
    int n = prefix.length();
    for (level = 0; level < n; level++) {
        int index = CHAR_TO_INDEX(prefix[level]);
        // no string in the Trie has this prefix
        if (!pCrawl->children[index])
            return;
        pCrawl = pCrawl->children[index];
    }
    // If prefix is present as a word.
    bool isWord = (pCrawl->isWordEnd == true);
    // If prefix is last node of tree (has no children)
    bool isLast = isLastNode(pCrawl);
    // If prefix is present as a word, but there is no subtree below the last matching node.
    if (isWord && isLast && !pCrawl->deleted && (gender == 0 || pCrawl->gender == gender)) {
        COUNT++;
        return;
    }
    // If there are are nodes below last matching character.
    if (!isLast) {
        suggestions(pCrawl, gender);
        return;
    }
}

void generatePrefix(string& start, const string& end, vector<string>& prefixes){
    while(start != end){
        prefixes.push_back(start);
        int sLastIndex = start.length() - 1;
        // int c = CHAR_TO_INDEX(start[sLastIndex]);
        if(start[sLastIndex] == 'Z') start.push_back('A');
        else start[sLastIndex] = (char)(start[sLastIndex] + 1);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    // freopen("in.txt", "r", stdin);
    struct TrieNode* root = getNode();
    int cmd;
    string ostart, start, oend, end;
    vector<string> prefixes;
    while(cin >> cmd, cmd != 0){
        switch(cmd){
            case 1:{
                string name; cin >> name;
                int gender; cin >> gender;
                insert(root, name, gender);
                break;
            }
            case 2:{
                string name; cin >> name;
                RemoveSuggestion(root, name);
                break;
            }
            case 3:{
                cin >> start >> end;
                int gender; cin >> gender;
                COUNT = 0;
                if(start != ostart && end != oend){
                    prefixes.clear();
                    generatePrefix(start, end, prefixes);
                    start = ostart, end = oend;
                }
                for(string& pre : prefixes) FindSuggestions(root, pre, gender);
                cout << COUNT << "\n";
            }
        }
    }
    return 0;
}