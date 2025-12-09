class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        // Map to count occurrences of elements to the left of current position
        unordered_map<int, int> leftCount;
        // Map to count occurrences of elements to the right of current position
        unordered_map<int, int> rightCount;
      
        // Initialize rightCount with all elements
        for (int num : nums) {
            rightCount[num]++;
        }
      
        long long result = 0;
        const int MOD = 1e9 + 7;
      
        // Iterate through each element as the middle element of triplet
        for (int middleValue : nums) {
            // Remove current element from right side
            rightCount[middleValue]--;
          
            // Count triplets where current element is in the middle
            // and left element equals right element equals 2 * middle element
            // This forms a triplet (2x, x, 2x) where x is the middle value
            int targetValue = middleValue * 2;
            result = (result + 1LL * leftCount[targetValue] * rightCount[targetValue] % MOD) % MOD;
          
            // Add current element to left side for next iterations
            leftCount[middleValue]++;
        }
      
        return static_cast<int>(result);
    }
};
