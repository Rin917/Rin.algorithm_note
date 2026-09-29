# AcWing 850. Dijkstra求最短路 II (堆优化版)

- **题型标签**：图论 / 单源最短路 / 贪心 / 优先队列 (Heap)
- **题目链接**：[AcWing 850 题目页面](https://www.acwing.com/problem/content/852/)
- **我的状态**：核心逻辑写对，但在 C++ 底层内存边界和初始化上连踩三个大坑（WA + TLE）。

---

## 1. 踩坑复盘（核心价值区）

### 坑 1：致命的隐形踩踏 (数组越界导致 WA)
* **报错现象**：算法逻辑全对，但提交后报 Wrong Answer（答案错误），而不是直接崩溃 (RE)。
* **底层原因**：题目要求 $N, M \le 1.5 \times 10^5$，而我习惯性开成了 `const int N = 100010;`。
* **C++ 内存机制**：全局数组 `h, w, e, ne, dist` 紧挨着存在 BSS 段。当加边操作 `idx` 超过 10 万时，`w[idx] = c;` 并没有报错，而是**悄悄越界写到了相邻的 `dist` 数组的内存里**，篡改了核心状态，导致最终答案完全错误。
* **教训**：写 C++ 纯数组题目，宁可浪费点内存把 $N$ 多开一点（如 `150010`），也绝对不能卡着边界开！

### 坑 2：堆优化的“懒惰删除”失效 (忘记封存导致 TLE)
* **报错现象**：程序严重超时 (Time Limit Exceeded)。
* **底层原因**：从优先队列 `heap.top()` 取出状态后，**漏写了 `st[ver] = true;`**。
* **逻辑崩塌**：STL 的 `priority_queue` 不支持修改元素，只能压入新状态。这就导致同一个节点会有很多“历史废弃记录”在堆里。如果不马上 `st[ver] = true` 盖章封存，后续废弃记录弹出时，`if(st[ver]) continue;` 无法拦截，程序会傻乎乎地再次遍历该节点的所有邻居，时间复杂度从 $O(M \log N)$ 瞬间退化。

### 坑 3：memset 的字节填充陷阱
* **报错现象**：初始化写成了 `memset(dist, -1, sizeof dist);`，导致算法完全不更新。
* **底层原因**：Dijkstra 的松弛条件是 `if(dist[j] > distance + w[i])`。如果全初始化为 `-1`，由于边权 `w[i]` 是正数，`-1 > 正数` 永远为 false，水波永远无法向外扩散。
* **正确做法**：图论求最短路必须初始化为无穷大，使用 `memset(dist, 0x3f, sizeof dist);`。

---

## 2. 核心骨架 (C++11)

```cpp
// 1. 数组模拟链表 (零动态分配，榨干 CPU 缓存)
const int N = 150010;
int h[N], w[N], e[N], ne[N], idx;

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

// 2. STL 小根堆声明套路
typedef pair<int, int> PII;
priority_queue<PII, vector<PII>, greater<PII>> heap;