# 删除排序数组中的重复项

## 题目

给定一个排序数组，你需要在 原地 删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。

不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

```
给定数组 nums = [1,1,2], 

函数应该返回新的长度 2, 并且原数组 nums 的前两个元素被修改为 1, 2。 

你不需要考虑数组中超出新长度后面的元素。
```

##  分析

### 1.数组已经排序

既然数组已经排好序，我们可以设置两个指针，一个快指针一个慢指针，当快指针和慢指针不相等的时候，就将快指针的值赋值给慢指针的下一位，当快指针的值和慢指针的值相等的时候，快指针自增。

C语言代码如下：

```c
int removeDuplicates(int* nums, int numsSize){
    int f;
    int s=0;
    if(numsSize > 1){
        while(f<numsSize){
            if(nums[f] != nums[s]){
                s++;
                nums[s]=nums[f];
            }
            f++;
        }
    }else{
        return numsSize;
    }
    return s+1;
}
```

> 执行用时：20 ms, 在所有 C 提交中击败了97.52%的用户
>
> 内存消耗：8.1 MB, 在所有 C 提交中击败了95.97%的用户

Go语言代码如下：

```go
func removeDuplicates(nums []int) int {
    n := len(nums)
    if n < 2{
        return n
    }
    left := 1
    right:= 1
    for right < n {
        if (nums[right] != nums[right-1]){
            nums[left] = nums[right]
            left++
        }
        right++
    }
    return left
}
```

> 执行用时：0 ms, 在所有 Go 提交中击败了100.00%的用户
>
> 内存消耗：4.5 MB, 在所有 Go 提交中击败了100.00%的用户