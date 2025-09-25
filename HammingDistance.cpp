/*
LeetCode 461: Hamming Distance

Definition:
    The Hamming distance between two non‑negative integers is the number of bit
    positions at which they differ. Example: x=1 (001), y=4 (100) -> distance = 2.

Approach:
    XOR (^) of the two numbers sets a bit to 1 exactly where they differ.
    We then count set bits (population count) in that XOR result.

Implementation Detail:
    Uses Brian Kernighan's algorithm: repeatedly clear the lowest set bit with
        diff &= (diff - 1);
    Each loop iteration removes one set bit, so complexity proportional to the
    number of differing bits instead of total bit width.

Complexity:
    Worst-case (all bits differ): O(B) where B is number of bits (<= 32/64)
    Best-case (few differing bits): O(k) where k is number of set bits in diff
    Space: O(1)

Note:
    Could also use builtin: __builtin_popcount(x ^ y) (GCC/Clang) for brevity.
*/

class Solution {
public:
    int hammingDistance(int x, int y) {
        int diff = x ^ y;           // Bits set to 1 where x and y differ
        int count = 0;              // Accumulates number of differing bits
        while (diff) {              // Loop while there remain set bits
            diff &= (diff - 1);     // Clear lowest set bit
            ++count;                // Increment count for that bit
        }
        return count;               // Return total differing positions
    }
};
