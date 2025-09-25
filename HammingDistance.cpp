/*
LeetCode 461: Hamming Distance

The Hamming distance between two integers is the number of positions
at which the corresponding bits are different.
*/

class Solution {
public:
    int hammingDistance(int x, int y) {
        int diff = x ^ y;  // XOR highlights differing bits
        int count = 0;
        while (diff) {
            count += diff & 1;  // count lowest bit if it's 1
            diff >>= 1;         // shift right
        }
        return count;
    }
};
