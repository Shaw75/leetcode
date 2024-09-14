#include <string>
#include <deque>
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