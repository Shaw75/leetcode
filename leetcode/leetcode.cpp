#include <string>
#include <deque>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>
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


/*
1184. 公交站间的距离
简单
相关标签
相关企业
提示
环形公交路线上有 n 个站，按次序从 0 到 n - 1 进行编号。我们已知每一对相邻公交站之间的距离，distance[i] 表示编号为 i 的车站和编号为 (i + 1) % n 的车站之间的距离。

环线上的公交车都可以按顺时针和逆时针的方向行驶。

返回乘客从出发点 start 到目的地 destination 之间的最短距离。

*/
class Solution {
public:
    int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
        
        
        if (start > destination) swap(start, destination);
        int len = distance.size();
        int num = std::accumulate(distance.begin(), distance.end(), 0);
        int left = 0;
        while (start != destination) {

            left = +distance[start];
            start++;
        }
        int rigth = num - left;
        return left > rigth ? rigth : left;
        
    }
};

/*815. 公交路线
给你一个数组 routes ，表示一系列公交线路，其中每个 routes[i] 表示一条公交线路，第 i 辆公交车将会在上面循环行驶。

例如，路线 routes[0] = [1, 5, 7] 表示第 0 辆公交车会一直按序列 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... 这样的车站路线行驶。
现在从 source 车站出发（初始时不在公交车上），要前往 target 车站。 期间仅可乘坐公交车。

求出 最少乘坐的公交车数量 。如果不可能到达终点车站，返回 - 1 。

*/

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;
        int n = routes.size();//记录公交线总数
        vector<vector<int>> edge(n, vector<int>(n));//建立临接矩阵，记录路线
        unordered_map<int, vector<int>> rec;//key是站点，value是能到站点的公交路线

        for (int i = 0; i < n; i++) {
            for (int site : routes[i]) {    //取出每条路线经过的站点
                for (int j : rec[site]) {//取出这个站点能到达的所以公交路线
                    edge[i][j] = edge[j][i] = true; //记录两条路线相连接

                }
                rec[site].push_back(i);
            }
        }
        vector<int> dis(n, -1);//每条公交路线到起点车站的距离
        queue<int> que;
        for (int bus : rec[source]) {
            dis[bus] = 1;  //与起点在同一条公交线上的点，到起点距离都是1，因为路线是循环的
            que.push(bus);
        }
        while (!que.empty()) {
            int x = que.front(); //对头出队
            que.pop();
            for (int y = 0; y < n; y++) {
                if (dis[y] == -1 && edge[x][y]) {
                    dis[y] = dis[x] + 1;
                    que.push(y);
                }

            }

        }
        int ret = INT_MAX;
        //取出能到终点的所有公交路线
        for (int bus : rec[target]) {
            if (dis[bus] != -1) {
                ret = min(ret, dis[bus]);
            }
        }
        return ret == INT_MAX ? -1 : ret;
    }
};



/*

2332. 坐上公交的最晚时间
已解答
中等
相关标签
相关企业
提示
给你一个下标从 0 开始长度为 n 的整数数组 buses ，其中 buses[i] 表示第 i 辆公交车的出发时间。同时给你一个下标从 0 开始长度为 m 的整数数组 passengers ，其中 passengers[j] 表示第 j 位乘客的到达时间。所有公交车出发的时间互不相同，所有乘客到达的时间也互不相同。

给你一个整数 capacity ，表示每辆公交车 最多 能容纳的乘客数目。

每位乘客都会搭乘下一辆有座位的公交车。如果你在 y 时刻到达，公交在 x 时刻出发，满足 y <= x  且公交没有满，那么你可以搭乘这一辆公交。最早 到达的乘客优先上车。

返回你可以搭乘公交车的最晚到达公交站时间。你 不能 跟别的乘客同时刻到达。

注意：数组 buses 和 passengers 不一定是有序的。

*/
class Solution {
public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        sort(buses.begin(), buses.end());
        sort(passengers.begin(), passengers.end());
        int pos = 0;  //乘客索引
        int space = 0;//容量
        for (int arrive : buses) {
            space = capacity;
            while (space > 0 && pos < passengers.size() && passengers[pos] <= arrive) {
                space--;
                pos++;
            }
        }

        pos--;
        int lastCatchTime = space > 0 ? buses.back() : passengers[pos]; //判断最后一辆公交车是否还有容量
        int lastCatchTime = buses.back();
        while (pos >= 0 && passengers[pos] == lastCatchTime) {
            pos--;
            lastCatchTime--;
        }

        return lastCatchTime;
    }
};


/*
2414. 最长的字母序连续子字符串的长度

提示
字母序连续字符串 是由字母表中连续字母组成的字符串。换句话说，字符串 "abcdefghijklmnopqrstuvwxyz" 的任意子字符串都是 字母序连续字符串 。

例如，"abc" 是一个字母序连续字符串，而 "acb" 和 "za" 不是。
给你一个仅由小写英文字母组成的字符串 s ，返回其 最长 的 字母序连续子字符串 的长度。
输入：s = "abacaba"
输出：2
解释：共有 4 个不同的字母序连续子字符串 "a"、"b"、"c" 和 "ab" 。
"ab" 是最长的字母序连续子字符串。

*/
class Solution {
public:
    int longestContinuousSubstring(string s) {
        int a = 1;
        int b = 1;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == s[i - 1] + 1) {
                a++;
                b = max(a, b);
            }
            else {

                a = 1;
            }


        }
        return b;
    }
};


/*
2376. 统计特殊整数
提示
如果一个正整数每一个数位都是 互不相同 的，我们称它是 特殊整数 。

给你一个 正 整数 n ，请你返回区间 [1, n] 之间特殊整数的数目。


示例 1：

输入：n = 20
输出：19
解释：1 到 20 之间所有整数除了 11 以外都是特殊整数。所以总共有 19 个特殊整数。
示例 2：

输入：n = 5
输出：5
解释：1 到 5 所有整数都是特殊整数。
示例 3：

输入：n = 135
输出：110
解释：从 1 到 135 总共有 110 个整数是特殊整数。
不特殊的部分数字为：22 ，114 和 131 。
*/
class Solution {
public:
    int countSpecialNumbers(int n) {
        int result = 0;
        for (int i = 1; i <= n; i++) {
            if (isSpecial(i)) {
                result++;
            }
        }

        return result;
    }

    bool isSpecial(int n) {
        bool v[10] = { false };  
        while (n > 0) {
            int digit = n % 10;
            if (v[digit]) {  
                return false;
            }
            v[digit] = true;  
            n /= 10;
        }
        return true;
    }
};



/*997. 找到小镇的法官
小镇里有 n 个人，按从 1 到 n 的顺序编号。传言称，这些人中有一个暗地里是小镇法官。

如果小镇法官真的存在，那么：

小镇法官不会信任任何人。
每个人（除了小镇法官）都信任这位小镇法官。
只有一个人同时满足属性 1 和属性 2 。
给你一个数组 trust ，其中 trust[i] = [ai, bi] 表示编号为 ai 的人信任编号为 bi 的人。

如果小镇法官存在并且可以确定他的身份，请返回该法官的编号；否则，返回 - 1 。*/

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        std::unordered_set<int> set;
        int size = trust.size();
        for (int i = 1; i < size; i++) {
            if (trust[i - 1][0] != trust[i][0]) {


            }

        }
        return trust[0][1];
    }
};