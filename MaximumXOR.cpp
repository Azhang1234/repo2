/*
LeetCode 421: Maximum XOR of Two Numbers in an Array

Given an integer array nums, return the maximum result of nums[i] ^ nums[j].
We use a Trie to store binary representations and greedily maximize XOR.
*/

#include <vector>
using namespace std;

class Solution {
    struct TrieNode {
        TrieNode* children[2] = {nullptr, nullptr};
    };
    
    void insert(TrieNode* root, int num) {
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!root->children[bit])
                root->children[bit] = new TrieNode();
            root = root->children[bit];
        }
    }
    
    int findMaxXor(TrieNode* root, int num) {
        int xorVal = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (root->children[1 - bit]) {
                xorVal |= (1 << i); // take opposite bit for max XOR
                root = root->children[1 - bit];
            } else {
                root = root->children[bit];
            }
        }
        return xorVal;
    }
    
public:
    int findMaximumXOR(vector<int>& nums) {
        TrieNode* root = new TrieNode();
        for (int num : nums) insert(root, num);
        
        int maxXor = 0;
        for (int num : nums) {
            maxXor = max(maxXor, findMaxXor(root, num));
        }
        return maxXor;
    }
};
