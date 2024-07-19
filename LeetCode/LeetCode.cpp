// Demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "stdafx.h"
#include "Array.h"

int main()
{
	vector<int> nums{ 2,2 };

	auto ret = searchRange(nums, 2);

	std::cout << ret[0] << "," << ret[1] << std::endl;

	return 0;
}
