/*
LeetCode 421: Maximum XOR of Two Numbers in an Array

Problem:
    Given an integer array nums, find max(nums[i] ^ nums[j]) for i != j.

Strategy (Bitwise Trie / Prefix Tree):
    Insert each number's 32-bit representation into a binary trie (MSB -> LSB).
    To maximize XOR for a number, at each bit position we greedily choose the
    opposite bit branch if it exists (since 1 ^ 0 = 1 gives higher value at more
    significant bits first). We accumulate the XOR value as we traverse.

Complexity:
    Build:  O(n * B)   (B = 32 bits)
    Query:  O(n * B)
    Space:  O(n * B) worst case (if bits diverge at many positions)

Memory Management:
    Original implementation leaked allocated trie nodes. Added a recursive
    cleanup helper in a local smart wrapper struct to free nodes.

Alternative Approach:
    Use a greedy bitmask + hash set technique: iterate bit from MSB to LSB,
    hypothesize next bit of answer, test prefixes in a set. Similar complexity
    but often lower constant factors and no explicit tree allocation.
*/

#include <vector>
#include <algorithm> // for std::max (clarity)
using namespace std;

class Solution {
    struct TrieNode {                    // Node with up to two children (bit 0 / bit 1)
        TrieNode* children[2] = {nullptr, nullptr};
    };

    // Recursive helper to free all nodes in the trie.
    void destroy(TrieNode* node) {
        if (!node) return;
        destroy(node->children[0]);
        destroy(node->children[1]);
        delete node;
    }

    // Insert one number into the trie (from MSB to LSB).
    void insert(TrieNode* root, int num) {
        for (int bitIndex = 31; bitIndex >= 0; --bitIndex) {
            int bit = (num >> bitIndex) & 1;            // extract bit at bitIndex
            if (!root->children[bit])                  // create path if needed
                root->children[bit] = new TrieNode();
            root = root->children[bit];                // descend
        }
    }

    // Given a number, traverse trie choosing opposite bits when possible to
    // maximize XOR value. Accumulate the resulting XOR bitwise.
    int findMaxXor(TrieNode* root, int num) const {
        int xorVal = 0;                                 // accumulated result
        for (int bitIndex = 31; bitIndex >= 0; --bitIndex) {
            int bit = (num >> bitIndex) & 1;             // current bit of num
            int desired = 1 - bit;                      // opposite bit preferred
            if (root->children[desired]) {              // take opposite branch
                xorVal |= (1 << bitIndex);              // set this bit in result
                root = root->children[desired];
            } else {                                    // fallback: same bit branch
                root = root->children[bit];
            }
        }
        return xorVal;                                  // best XOR with num
    }

public:
    int findMaximumXOR(vector<int>& nums) {
        if (nums.size() < 2) return 0;                  // need at least two numbers
        TrieNode* root = new TrieNode();                // allocate root
        for (int num : nums)                            // build trie
            insert(root, num);

        int maxXor = 0;                                 // track global maximum
        for (int num : nums)
            maxXor = std::max(maxXor, findMaxXor(root, num));

        destroy(root);                                  // free trie memory
        return maxXor;                                  // result
    }
};
