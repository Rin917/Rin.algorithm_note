#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 520, M = 10010;

int n, m, k;
int dist[N], backup[N];

struct edge
{
    int a, b, c;
}edge[M];

int bellman_ford()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    for(int i = 0;i < k; i ++ )
    {
        memcpy(backup, dist, sizeof dist);
        for(int j = 1; j <= m; j ++)
        {
            int a = edge[j].a, b = edge[j].b, c = edge[j].c;
            if(backup[a] + c < dist[b])
                dist[b] = backup[a] + c;
        }
    }

    return dist[n];
}

int main()
{
    cin >> n >> m >> k;
    for(int i = 1;i <= m; i ++ )
    {
        int a, b, c;
        cin >> a >> b >> c;
        edge[i] = {a, b, c};
    }

    int t = bellman_ford();
    if(t > 0x3f3f3f3f / 2) cout << "impossible" << endl;
    else cout << t << endl;
    return 0;
}
