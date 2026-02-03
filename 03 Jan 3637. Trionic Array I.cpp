class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int n = nums.size();
      
        // Phase 1: Find the end of the first increasing segment
        // Start from index 0 and move right while values are increasing
        int firstPeakIndex = 0;
        while (firstPeakIndex < n - 2 && nums[firstPeakIndex] < nums[firstPeakIndex + 1]) {
            firstPeakIndex++;
        }
      
        // If no increasing segment found at the beginning, pattern is invalid
        if (firstPeakIndex == 0) {
            return false;
        }
      
        // Phase 2: Find the end of the decreasing segment (valley)
        // Start from the peak and move right while values are decreasing
        int valleyIndex = firstPeakIndex;
        while (valleyIndex < n - 1 && nums[valleyIndex] > nums[valleyIndex + 1]) {
            valleyIndex++;
        }
      
        // If no decreasing segment found or it reaches the end, pattern is invalid
        if (valleyIndex == firstPeakIndex || valleyIndex == n - 1) {
            return false;
        }
      
        // Phase 3: Verify the final increasing segment
        // Start from the valley and check if values increase until the end
        int currentIndex = valleyIndex;
        while (currentIndex < n - 1 && nums[currentIndex] < nums[currentIndex + 1]) {
            currentIndex++;
        }
      
        // Valid trionic pattern if the final increasing segment reaches the last element
        return currentIndex == n - 1;
    }
};
