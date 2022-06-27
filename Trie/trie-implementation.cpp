#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
using std::cout;
using std::string;
using std::unordered_map;
using std::vector;

class Trie
{
    struct TrieNode
    {
        bool is_end_of_word;

        unordered_map<char, TrieNode *> children;

        TrieNode() : is_end_of_word(false)
        {
        }
    };

    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }

    void insert(const string &word)
    {
        TrieNode *current_node = root;

        for (char letter : word)
        {
            if (find_child(letter, current_node->children) == false)
            {
                current_node->children[letter] = new TrieNode();
            }

            current_node = current_node->children[letter];
        }

        current_node->is_end_of_word = true;
    }

    bool search(const string &word)
    {
        TrieNode *current_node = root;

        for (char letter : word)
        {
            if (find_child(letter, current_node->children) == false)
            {
                return false;
            }

            current_node = current_node->children[letter];
        }

        return current_node->is_end_of_word;
    }

    bool startsWith(const string &prefix)
    {
        TrieNode *current_node = root;

        for (char letter : prefix)
        {
            if (find_child(letter, current_node->children) == false)
            {
                return false;
            }

            current_node = current_node->children[letter];
        }

        return true;
    }

    void delete_word(const string &word)
    {
        if (search(word) == true)
        {
            cout << word << "\n";
            root = delete_word_helper(root, 0, word);
        }
    }

private:
    bool find_child(char letter, unordered_map<char, TrieNode *> &children)
    {
        return children.find(letter) != children.end() && children[letter] != nullptr;
    }

    bool hasChildren(TrieNode *node)
    {
        return node->children.size();
    }

    TrieNode *delete_word_helper(TrieNode *current_node, int depth, const string &word)
    {
        if (current_node == nullptr)
            return current_node;

        if (depth == word.size())
        {
            current_node->is_end_of_word = false;

            if (hasChildren(current_node) == false)
            {
                delete current_node;
                current_node = nullptr;
            }

            return current_node;
        }

        char key = word[depth];

        current_node->children[key] = delete_word_helper(current_node->children[key], depth + 1, word);

        if (current_node->is_end_of_word == false && hasChildren(current_node) == false)
        {
            delete current_node;
            current_node = nullptr;
        }

        return current_node;
    }
};

int main(int argc, char const *argv[])
{
    using std::cin;

    int n = 5;
    // cin >> n;

    vector<string> strs{"a", "ab", "apple", "cat", "green"};

    // for (int i = 0; i < n; ++i)
    // 	cin >> strs[i];

    Trie test_trie;

    for (string &s : strs)
        test_trie.insert(s);

    for (string &s : strs)
        cout << s << " : " << test_trie.search(s) << "\n";
    cout << "\n";

    test_trie.delete_word("ap");

    for (string &s : strs)
        cout << s << " : " << test_trie.search(s) << "\n";

    return 0;
}
