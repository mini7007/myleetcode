class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
      
        // Multiset to maintain elements in current window (sorted)
        multiset<int> currentWindow;
      
        int n = nums.size();
      
        // dp[i] = number of ways to partition nums[0...i-1]
        vector<int> dp(n + 1, 0);
      
        // prefixSum[i] = cumulative sum of dp[0] + dp[1] + ... + dp[i]
        vector<int> prefixSum(n + 1, 0);
      
        // Base case: empty array has one way to partition
        dp[0] = 1;
        prefixSum[0] = 1;
      
        // Left pointer for sliding window
        int leftPtr = 1;
      
        // Process each position as potential end of a partition
        for (int rightPtr = 1; rightPtr <= n; ++rightPtr) {
            // Add current element to the window
            int currentElement = nums[rightPtr - 1];
            currentWindow.insert(currentElement);
          
            // Shrink window from left while range exceeds k
            // Range = max element - min element in current window
            while (*currentWindow.rbegin() - *currentWindow.begin() > k) {
                // Remove the leftmost element from window
                currentWindow.erase(currentWindow.find(nums[leftPtr - 1]));
                ++leftPtr;
            }
          
            // Calculate number of valid partitions ending at position rightPtr
            // This equals sum of dp values for all valid starting positions
            // Valid starting positions are from leftPtr-1 to rightPtr-1
            int waysFromValidStarts = prefixSum[rightPtr - 1] - 
                                      (leftPtr >= 2 ? prefixSum[leftPtr - 2] : 0);
            dp[rightPtr] = (waysFromValidStarts + MOD) % MOD;
          
            // Update prefix sum for next iteration
            prefixSum[rightPtr] = (prefixSum[rightPtr - 1] + dp[rightPtr]) % MOD;
        }
      
        // Return number of ways to partition the entire array
        return dp[n];
    }
};
