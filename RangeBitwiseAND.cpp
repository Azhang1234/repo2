/*
LeetCode 201: Bitwise AND of Numbers Range

Given two integers left and right that represent a range [left, right],
return the bitwise AND of all numbers in this range.
*/

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int shift = 0;
        // keep shifting until left == right
        while (left < right) {
            left >>= 1;
            right >>= 1;
            shift++;
        }
        return left << shift; // shift back to original position
    }
};
