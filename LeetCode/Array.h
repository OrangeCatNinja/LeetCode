#pragma once

//35. 搜索插入位置
int searchInsert(vector<int>& nums, int target) 
{
	if (nums.size() == 0) return 0;
	if (target <= nums[0]) return 0;
	if (target > nums.back()) return nums.size();

	int left = 0, right = nums.size(), mid = 0;

	while (left < right)
	{
		mid = (left + right) / 2;

		if (target < nums[mid])
			right = mid;
		else if (target > nums[mid])
			left = mid + 1;
		else
			return mid;
	}

	return left;
}

//34. 在排序数组中查找元素的第一个和最后一个位置
int searchLeft(vector<int>& nums, int target)
{
	int left = 0, right = nums.size(), mid = 0;

	while (left < right)
	{

	}
}

vector<int> searchRange(vector<int>& nums, int target) 
{
	vector<int> ret;

	int left = 0, right = nums.size(), mid = 0;

	while (left < right)
	{
		mid = (left + right) / 2;

		if (target < nums[mid])
			right = mid;
		else
			left = mid + 1;
	}

	return { -1,-1 };
}