/*
LeetCode 201: Bitwise AND of Numbers Range

Task:
    Compute: left & (left+1) & (left+2) & ... & right.

Key Insight:
    Any bit position that changes (flips from 0->1 or 1->0) inside the range
    will become 0 in the final AND because at least one number in the range has
    a 0 in that bit position. Therefore the answer is simply the common leftmost
    (most significant) prefix of left and right. We find this common prefix by
    right-shifting both numbers until they are equal; the removed (shifted out)
    bits are the differing suffix and must be zeroed in the final result.

Algorithm:
    1. Count how many times we can shift both left and right to the right until they match.
    2. That count = number of differing low-order bits.
    3. Left (now == right) holds the shared prefix; shift it back left by count.

Complexity:
    Time: O(B) where B = number of bits (<= 31 or 32 for int)
    Space: O(1)

Alternative Implementation:
    while (right > left) right &= (right - 1); // clears lowest set bit of right
    return right; // converges to common prefix too
*/

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int shift = 0;                  // number of right shifts applied
        while (left < right) {          // while differing bits remain
            left >>= 1;                 // discard one low-order bit
            right >>= 1;                // keep prefixes aligned
            ++shift;                    // track how many bits removed
        }
        return left << shift;           // restore common prefix in place
    }
};
