#include <string>
#include <deque>
#include <vector>
using namespace std;
/*
2390. 从字符串中移除星号
包含若干星号 * 的字符串 s 。
在一步操作中，你可以：
选中 s 中的一个星号。
移除星号 左侧 最近的那个 非星号 字符，并移除该星号自身。
返回移除 所有 星号之后的字符串。

注意：
生成的输入保证总是可以执行题面中描述的操作。
可以证明结果字符串是唯一的。
输入：s = "leet**cod*e"
输出："lecoe"
解释：从左到右执行移除操作：
- 距离第 1 个星号最近的字符是 "leet**cod*e" 中的 't' ，s 变为 "lee*cod*e" 。
- 距离第 2 个星号最近的字符是 "lee*cod*e" 中的 'e' ，s 变为 "lecod*e" 。
- 距离第 3 个星号最近的字符是 "lecod*e" 中的 'd' ，s 变为 "lecoe" 。
不存在其他星号，返回 "lecoe" 。
*/
//解法1：
class Solution {
public:
    string removeStars(string s) {
        int len = s.length();
        std::deque<char> dq;
        std::string result;
        int i = 0;
        while(i<len){
            if (s[i] != '*') {
                dq.push_back(s[i]);
                i++;

            }
            else if (s[i] == '*') {
                if (!dq.empty()) {
                    dq.pop_back();
                    i++;
                }
                else i++;

            }

        }
        while (!dq.empty())
        {
            result.push_back(dq.front());
            dq.pop_front();
            
        }
        return result;
    }
};
//解法2
class Solution {
public:
    string removeStars(string s) {
        string st;
        for (char c : s) {
            if (c == '*') {
                st.pop_back();
            }
            else {
                st += c;
            }
        }
        return st;
    }
};




/*
2848. 与车相交的点
给你一个下标从 0 开始的二维整数数组 nums 表示汽车停放在数轴上的坐标。对于任意下标 i，nums[i] = [starti, endi] ，其中 starti 是第 i 辆车的起点，endi 是第 i 辆车的终点。
返回数轴上被车任意部分覆盖的整数点的数目。

示例 1：

输入：nums = [[3,6],[1,5],[4,7]]
输出：7
解释：从 1 到 7 的所有点都至少与一辆车相交，因此答案为 7 。
示例 2：

输入：nums = [[1,3],[5,8]]
输出：7
解释：1、2、3、5、6、7、8 共计 7 个点满足至少与一辆车相交，因此答案为 7 。


提示：

1 <= nums.length <= 100
nums[i].length == 2
1 <= starti <= endi <= 100


*/
class Solution {
public:
    int numberOfPoints(vector<vector<int>>& nums) {
        int C = 0;
        for (const auto& interval : nums) {
            C = max(C, interval[1]);  //得到J的最大值
        }

        vector<int> v(C + 1); //初始化j+1个空间的v  8
        for (const auto& interval : nums) {


            v[interval[0]] = max(v[interval[0]], interval[1]);    //v[3] =6  v[1] =5  v[4]=7
        }
        //v[1] =5 ,max=5 
        int max = 0, cnt = 0;
        for (int i = 1; i < C + 1; i++) {    //v[3] =6  v[1] =5  v[4]=7   v[2]=0 v[6]=0 v[7]=0 v[5]=0
            if (v[i] > max) {
                max = v[i];
                cnt++;
            }
            else if (i <= max) {
                cnt++;
            }
        }
        return cnt;
    }
};
