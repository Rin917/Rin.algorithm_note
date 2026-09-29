#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

const int N = 1000100;
int n, m;
int dist[N];
int h[N], e[N], ne[N], w[N], idx;
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx ++ ;
}

int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    
    heap.push({0,1});
    
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();
        int ver = t.second, Distance = t.first;
        
        if(st[ver]) continue;
        st[ver] = true;
        for(int i = h[ver]; i != -1;i = ne[i])
        {
            int j = e[i];
            if(dist[j] > Distance + w[i])
            {
                dist[j] = Distance + w[i];
                heap.push({dist[j],j});
            }
        }
    }
    
    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

int main()
{
    memset(h, -1, sizeof h);
    cin >> n >> m;
    while(m --)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        
    }
    
    cout << dijkstra();
    
    return 0;
}