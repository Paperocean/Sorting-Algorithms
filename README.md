# Sorting Algorithms

## Bucket Sort
- **Time Complexity:**
  - Average Case: O(n)
  - Worst Case: O(n^2)
- **Description:** 
  The algorithm divides the data based on a range determined by the minimum and maximum values in the dataset. It splits the data into subranges (buckets), where each value is used as the index for the bucket. When a value appears in the array, the corresponding bucket's counter is incremented. Finally, the array is filled with the indices based on the count in each bucket.

## Merge Sort
- **Time Complexity:**
  - Average Case: O(n log n)
  - Worst Case: O(n log n)
- **Description:** 
  The algorithm divides the data into smaller subarrays. It does this for the left and right sides based on the middle element (m). Then, the data is merged back into a single array. Merging involves comparing the left and right values in sequence. The algorithm uses recursion to perform these operations.

## Quick Sort
- **Time Complexity:**
  - Best Case: O(n log n)
  - Average Case: O(n log n)
  - Worst Case: O(n^2)
- **Description:** 
  The algorithm selects a pivot element and then searches for a larger element than the pivot on the left side, and a smaller element on the right side, swapping them accordingly. This process continues until the left side crosses the right side, which ensures that the data is sorted from smallest to largest. The process is recursive.
