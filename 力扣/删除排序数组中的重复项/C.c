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