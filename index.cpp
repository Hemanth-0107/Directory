#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    bool isEnd;
    string phoneNumber;
    char data;
    vector<Node *> child;
    Node()
    {
        isEnd = false;
        child.assign(26, NULL);
    }
};
class Trie
{
    Node *root;
public:
    Trie()
    {
        root = new Node();
    }
    void insert(string name)
    {
        int len = name.length();
        Node *curr = root;
        for (int i = 0; i < len; i++)
        {
            int k = name[i] - 'a';
            if (curr->child[k] == NULL)
                curr->child[k] = new Node();
            curr = curr->child[k];
        }
        curr->isEnd = true;
    }
    bool search(string word)
    {
        int len = word.length();
        Node *curr = root;
        for (int i = 0; i < len; i++)
        {
            int k = word[i] - 'a';
            curr = curr->child[k];
            if (!curr)
            {
                cout << "No such name in Existing Directory" << endl;
                return false;
            }
        }
        if (!curr->isEnd)
            cout << "No such name in Existing Directory" << endl;
        else
            cout << "Found " << word << "successfully" << endl;
        return curr->isEnd;
    }
    void remove(string word)
    {
        int len = word.length();
        int idx=-1;
        Node *curr = root,*temp=NULL;
        for (int i = 0; i < len; i++)
        {
            int k = word[i] - 'a';
            curr = curr->child[k];
            if(curr->isEnd) {
                idx=i;
                temp=curr;
            }
            if (!curr)
            {
                cout << "No such name in Existing Directory" << endl;
                return;
            }
        }  
        curr->isEnd = false;
        cout << "Removed successfully" << endl;
    }
    void wordsSearch(string word, unordered_set<string>  &results, Node *curr, int n)
    {
        if (results.size()==n)
            return;
        if (curr->isEnd)
        {
            results.insert(word);
            n--;
        }
        for (int i = 0; i < 26; i++)
        {
            if(curr->child[i]){
                 word += ('a' + i);
                wordsSearch(word, results, curr->child[i], n);
                word.pop_back();
            }           
        }
    }
    unordered_set<string>  wordsWithPrefix(string prefix, int n)
    {
        unordered_set<string>  results;
        Node *curr = root;
        for (auto i : prefix)
        {
            if (!curr){
                cout<<"No results found"<<endl;
                return results;
            }  
            curr = curr->child[i - 'a'];
        }
        wordsSearch(prefix, results, curr, n);
        return results;
    }
    unordered_set<string> suggestions(string name, int n = 100)
    {
        cout<<"Suggestions for "<<name<<":\n"<<endl;
        unordered_set<string>  suggestions;
        string prefix;
        for (auto w : name)
        {
            prefix += w;
            unordered_set<string> temp=wordsWithPrefix(prefix, n);
            suggestions.insert(temp.begin(), temp.end());
        }
        cout<<"Suggestions loaded\n";
        return suggestions;
    }
};
int main()
{
    Trie trie = Trie();
    string command;
     while (true) {
    cout << "> ";
    cin >> command; 

    if (command == "insert") {
      string word;
      cin >> word;
      trie.insert(word);
    } else if (command == "search") {
      string word;
      cin >> word;
      cout << trie.search(word) << endl;
    } else if (command == "remove") {
      string word;
      cin >> word;
      trie.remove(word);
    } else if (command == "suggestions") {
      string prefix;
      cin >> prefix;
      unordered_set<string> suggestions = trie.suggestions(prefix);
      cout << "Size: " << suggestions.size() << endl;
      for (auto& suggestion : suggestions) {
        cout << suggestion << endl;
      }
    } else if (command == "exit") {
      break;
    } else {
      cout << "Invalid command." << endl;
    }
  }
    return 0;
}