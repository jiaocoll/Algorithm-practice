package main

func removeDuplicates(nums []int) int {
	n := len(nums)
	if n < 2 {
		return n
	}
	left := 1
	right := 1
	for right < n {
		if nums[right] != nums[right-1] {
			nums[left] = nums[right]
			left++
		}
		right++
	}
	return left
}
