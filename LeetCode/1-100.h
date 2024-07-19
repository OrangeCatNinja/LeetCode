#pragma once

using namespace std;

//2.两数相加
struct ListNode
{
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	const ListNode* pLine1 = l1;
	const ListNode* pLine2 = l2;
	ListNode* pRes = new ListNode();
	ListNode* pLine3 = pRes;

	int nSumNext = 0;
	while (pLine1 || pLine2 || nSumNext)
	{
		int nSum = nSumNext;
		if (pLine1)
			nSum += pLine1->val;
		if (pLine2)
			nSum += pLine2->val;

		int nData = nSum % 10;
		nSumNext = nSum / 10;

		ListNode* pTemp = new ListNode(nData);
		pLine3->next = pTemp;
		pLine3 = pLine3->next;

		if (pLine1)
			pLine1 = pLine1->next;
		if (pLine2)
			pLine2 = pLine2->next;
	}

	pRes = pRes->next;
	return pRes;
}

//1.两数之和
std::vector<int> twoSum(std::vector<int>& nums, int target) {
	std::vector<int> vec{ 0, 0 };
	std::unordered_multimap<int, int> hashNums;

	for (int i = 0; i < nums.size(); ++i)
	{
		hashNums.insert(std::pair<int, int>(nums[i], i));
	}

	for (int i = 0; i < nums.size(); ++i)
	{
		int nEle = nums[i];

		int nSecondNum = target - nEle;
		std::unordered_map<int, int>::const_iterator itr = hashNums.find(nSecondNum);
		if (itr != hashNums.end() && itr->second != i)
		{
			vec[0] = i;
			vec[1] = itr->second;
			break;
		}
	}

	return vec;
}

//2367.算数三元组的数目
int arithmeticTriplets(std::vector<int>& nums, int diff) {
	int nNum = 0;

	std::unordered_map<int, int> mapValueIndex;
	for (int i = 0; i < nums.size(); ++i)
	{
		mapValueIndex[nums[i]] = i;
	}

	for (int i = 0; i < nums.size(); ++i)
	{
		std::unordered_map<int, int>::const_iterator itrSecond = mapValueIndex.find(nums[i] + diff);
		std::unordered_map<int, int>::const_iterator itrThird = mapValueIndex.find(nums[i] + diff + diff);

		if (itrSecond != mapValueIndex.end()
			&& itrThird != mapValueIndex.end()
			&& itrSecond->second > i
			&& itrThird->second > itrSecond->second)
		{
			++nNum;
		}
	}

	return nNum;
}

//3.无重复字符的最长子串
int lengthOfLongestSubstring(std::string s) {
	if (s.length() <= 0)
		return 0;

	int nCount = 0;
	int nIndex = 0;
	int nLastIndex = 0;

	std::unordered_set<char> setChar;
	setChar.insert(s.at(nLastIndex++));

	while (nLastIndex < s.length())
	{
		if (setChar.count(s.at(nLastIndex)) != 0)
		{
			nCount = setChar.size() > nCount ? setChar.size() : nCount;
			do
			{
				setChar.erase(s.at(nIndex++));
			} while (setChar.count(s.at(nLastIndex)));
		}
		setChar.insert(s.at(nLastIndex++));
	}

	nCount = setChar.size() > nCount ? setChar.size() : nCount;
	return nCount;
}

//4.寻找两个正序数组的中位数
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
	return 0;
}

//5. 最长回文子串
std::string longestPalindrome(std::string s) {
	int nIndex = 0;
	int nLast = s.length() - 1;
	std::pair<int, int> maxLength(0, 0);

	if (s.length() <= 1)
		return s;

	while (nIndex <= nLast
		&& nLast < s.length())
	{
		nLast = s.find_last_of(s[nIndex], nLast);
		if (nLast <= nIndex)
		{
			nIndex++;
			nLast = s.length() - 1;
			continue;
		}

		int nTempIndex = nIndex;
		int nTempLast = nLast;
		bool bSucess = true;
		while (nTempIndex <= nTempLast)
		{
			if (s[++nTempIndex] != s[--nTempLast])
			{
				bSucess = false;
				break;
			}
		}

		if (bSucess)
		{
			if (maxLength.second - maxLength.first < nLast - nIndex)
			{
				maxLength.first = nIndex;
				maxLength.second = nLast;
				++nIndex;
				nLast = s.length() - 1;
			}
			else
			{
				++nIndex;
				nLast = s.length() - 1;
			}
		}
		else
		{
			--nLast;
		}
	}

	return s.substr(maxLength.first, maxLength.second - maxLength.first + 1);
}

//6. N 字形变换
std::string convert(std::string s, int numRows) {
	if (s.length() <= 2 || s.length() <= numRows || numRows <= 1)
		return s;

	std::vector<std::string> vecStr(numRows);
	int nIndex = 0;
	int nOffset = 2 * numRows - 2;
	for (int nCount = 1; nCount <= s.length() / nOffset + 1; ++nCount)
	{
		std::string strSub = s.substr(nIndex, nOffset);
		for (int i = 0; i < numRows; ++i)
		{
			if (i < strSub.length())
			{
				vecStr[i] += strSub[i];
				int nSubOffset = i + 2 * (numRows - 1 - i);
				if (nSubOffset < strSub.length() && i != numRows - 1)
					vecStr[i] += strSub[nSubOffset];
			}
		}

		if (s.length() - (nCount + 1) * nOffset >= 0)
			nIndex += nOffset;
		else
			nOffset = s.length() - nCount * nOffset;
	}

	std::string strRes;
	for (int i = 0; i < numRows; ++i)
	{
		strRes += vecStr[i];
	}
	return strRes;
}

//11. 盛最多水的容器
int maxArea(std::vector<int>& height) {
	if (height.size() < 2)
		return 0;

	int nIndex = 0;
	int nLast = height.size() - 1;

	int nMaxArea = 0;

	while (nIndex < nLast)
	{
		int nHeight = height[nIndex] > height[nLast] ? height[nLast] : height[nIndex];
		int nArea = (nLast - nIndex) * nHeight;
		if (nMaxArea < nArea)
			nMaxArea = nArea;

		if (height[nIndex] < height[nLast])
			++nIndex;
		else
			--nLast;
	}

	return nMaxArea;
}

//15. 三数之和
std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
	std::vector<std::vector<int>> res;

	std::sort(nums.begin(), nums.end());

	for (int i = 0; i < nums.size(); ++i)
	{
		if (nums[i] > 0)
			break;

		if (i > 0 && nums[i] == nums[i - 1])
			continue;

		int nFirst = i + 1;
		int nLast = nums.size() - 1;

		while (nFirst < nLast)
		{
			if (nFirst > i + 1 && nums[nFirst] == nums[nFirst - 1])
			{
				++nFirst;
				continue;
			}
			if (nLast < nums.size() - 1 && nums[nLast] == nums[nLast + 1])
			{
				--nLast;
				continue;
			}

			int nSum = nums[i] + nums[nFirst] + nums[nLast];
			if (nSum == 0)
			{
				res.push_back({ nums[i], nums[nFirst++], nums[nLast--] });
			}
			else if (nSum > 0)
			{
				--nLast;
			}
			else if (nSum < 0)
			{
				++nFirst;
			}
		}
	}


	return res;
}

//17. 电话号码的字母组合
std::vector<std::string> letterCombinations(std::string digits) {
	std::vector<std::string> ret;
	if (digits.empty()) {
		return ret;
	}

	std::string combination;
	backtrack(ret, digits, combination, 0);
	return ret;
}

void backtrack(std::vector<std::string>& ret, std::string& digits, std::string& combination, int nStart)
{
	static std::unordered_map<char, std::string> phoneMap
	{
		{'2', "abc"},{'3', "def"},{'4', "ghi"},{'5', "jkl"},{'6', "mno"},{'7', "pqrs"},{'8', "tuv"},{'9', "wxyz"}
	};

	if (nStart == digits.length())
	{
		ret.push_back(combination);
		return;
	}

	char curNum = digits[nStart];
	const std::string& str = phoneMap[curNum];

	if (str.empty())
		backtrack(ret, digits, combination, nStart + 1);

	for (int i = 0; i < str.length(); ++i)
	{
		combination.push_back(str[i]);
		backtrack(ret, digits, combination, nStart + 1);
		combination.pop_back();
	}
}

//19. 删除链表的倒数第 N 个结点
ListNode* removeNthFromEnd(ListNode* head, int n)
{
	ListNode* pHead = head;
	ListNode* pLast = head;
	for (int i = 0; i < n; ++i)
	{
		if (pLast->next != NULL)
			pLast = pLast->next;
		else
			return pHead->next;
	}

	while (pLast != NULL && pLast->next != NULL)
	{
		pHead = pHead->next;
		pLast = pLast->next;
	}

	if (pHead == head && !pHead->next)
		return pHead = pHead->next;
	ListNode* delNode = pHead->next;
	pHead->next = delNode ? delNode->next : delNode;
	delNode = NULL;

	return head;
}

//20. 有效的括号
bool isValid(std::string s)
{
	std::stack<char> bracketStack;
	for (int i = 0; i < s.length(); ++i)
	{
		char barcket = s[i];
		if (barcket == '(' || barcket == '{' || barcket == '[')
			bracketStack.push(barcket);
		else if (barcket == ')' || barcket == '}' || barcket == ']')
		{
			if (bracketStack.empty())
				return false;

			char left = bracketStack.top();
			if (left == '(' && barcket == ')'
				|| left == '{' && barcket == '}'
				|| left == '[' && barcket == ']')
				bracketStack.pop();
			else
				return false;
		}
	}

	if (bracketStack.empty())
		return true;
	else
		return false;
}

//21. 合并两个有序链表
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
{
	if (!list1 && !list2)
		return NULL;

	ListNode* pNew = new ListNode();
	ListNode* pHead = pNew;

	while (list1 && list2)
	{
		ListNode* pHead1 = list1;
		ListNode* pHead2 = list2;
		ListNode* pTemp = NULL;
		if (list1->val <= list2->val)
		{
			pTemp = pHead1;
			list1 = list1->next;
		}
		else
		{
			pTemp = pHead2;
			list2 = list2->next;
		}

		pTemp->next = NULL;
		pHead->next = pTemp;
		pHead = pHead->next;
	}

	pHead->next = list1 ? list1 : list2;

	return pNew->next;
}

//22. 括号生成
std::vector<std::string> generateParenthesis(int n)
{
	std::vector<std::string> ret;
	std::unordered_set<std::string> retSet;

	if (n == 1) return { "()" };

	for (auto& ele : generateParenthesis(n - 1))
	{
		for (int i = 0; i < ele.length(); ++i)
		{
			std::string str = ele.substr(0, i + 1) + "()" + ele.substr(i + 1, ele.length());
			if (retSet.insert(str).second)
				ret.push_back(str);
		}
	}

	return ret;
}

//31. 下一个排列
void nextPermutation(std::vector<int>& nums)
{
	int i = 0;
	for (i = nums.size() - 2; i >= 0; --i) { // 从后往前找到第一个相邻升序对
		if (nums[i] < nums[i + 1]) break;
	}
	if (i == -1) reverse(nums.begin(), nums.end()); // 无相邻升序对，必定为非递减序列
	else {
		for (int j = nums.size() - 1; j >= i + 1; --j) { // 从后往前[i+1,end)找第一个大于a[i+1]的值
			if (nums[i] < nums[j]) {
				swap(nums[i], nums[j]); // 交换二者
				reverse(nums.begin() + i + 1, nums.end()); // 反转[i+1,end)，变成升序
				break;
			}
		}
	}
}

//33. 搜索旋转排序数组
int search(vector<int>& nums, int target) {
	if (nums.empty()) return -1;

	int nBegin = 0, nEnd = nums.size() - 1;
	int nRet = 0;

	while (nBegin <= nEnd)
	{
		if (nBegin == nEnd)
		{
			nRet = nBegin;
			break;
		}
		else
		{
			int nMid = (nBegin + nEnd) / 2;
			if (nums[nMid] < nums[nBegin])
				nEnd = nMid;
			if (nums[nMid] > nums[nEnd])
				nBegin = nMid + 1;
		}
	}

	if (nums[nRet] > target && target > nums[0])
	{
		nBegin = 0;
		nEnd = nRet;
	}
	else if (nums[nRet + 1] < target && target < nums[nums.size() - 1])
	{
		nBegin = nRet + 1;
		nEnd = nums.size() - 1;
	}
	else
		return -1;

	while (nBegin <= nEnd)
	{
		int nMid = (nBegin + nEnd) / 2;
		if (nums[nMid] == target)
			return nMid;
		else if (nums[nMid] < target)
			nBegin = nMid + 1;
		else if (nums[nMid] > target)
			nEnd = nMid;
		else return -1;
	}
}

//34. 在排序数组中查找元素的第一个和最后一个位置
std::vector<int> searchRange(std::vector<int>& nums, int target) {
	std::vector<int> ret;

	if (nums.size() == 0)
	{
		ret.push_back(-1);
		ret.push_back(-1);
		return ret;
	}

	if (nums.size() == 1)
	{
		if (nums[0] == target)
		{
			ret.push_back(0);
			ret.push_back(0);
		}
		else
		{
			ret.push_back(-1);
			ret.push_back(-1);
		}
		return ret;
	}

	int nLow = 0;
	int nHigh = nums.size() - 1;

	while (nLow <= nHigh)
	{
		int nMid = (nLow + nHigh) / 2;

		if (nums[nMid] > target)
		{
			nHigh = nMid - 1;
		}
		else if (nums[nMid] < target)
		{
			nLow = nMid + 1;
		}
		else
		{
			int nFindLow = nMid;
			int nFindHigh = nMid;
			while (nFindLow - 1 >= nLow && nums[nFindLow - 1] == target)
			{
				--nFindLow;
			}
			while (nFindHigh + 1 <= nHigh && nums[nFindHigh + 1] == target)
			{
				++nFindHigh;
			}

			ret.push_back(nFindLow);
			ret.push_back(nFindHigh);
			break;
		}
	}

	if (ret.empty())
	{
		ret.push_back(-1);
		ret.push_back(-1);
	}

	return ret;
}

//39. 组合总和
std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
	std::vector<std::vector<int>> ret;

	//std::sort(candidates.begin(), candidates.end());

	vector<int> combination;
	GetSum(candidates, ret, combination, target, 0);

	return ret;
}

void  GetSum(std::vector<int>& candidates, std::vector<std::vector<int>>& ret, vector<int>& combination, int target, int nStart)
{
	if (target == 0)
	{
		//std::sort(candidates.begin(), candidates.end());
		ret.emplace_back(combination);
		return;
	}
	else if (target < 0 || nStart == candidates.size())
		return;
	else
	{
		int nNum = candidates[nStart];
		GetSum(candidates, ret, combination, target, nStart + 1);

		if (target - nNum >= 0)
		{
			combination.push_back(nNum);
			GetSum(candidates, ret, combination, target - nNum, nStart);
			combination.pop_back();
		}
	}
}

//70. 爬楼梯
int climbStairs(int n) {
	if (1 == n)	return 1;
	if (2 == n)	return 2;

	int count = 0;
	count += climbStairs(n - 1);
	count += climbStairs(n - 2);

	return count;
}