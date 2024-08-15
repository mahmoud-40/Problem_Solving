#include <vector>
#include <queue>
#include <limits>

using namespace std;

const long long N = 2e5 + 5;
const long long INF = numeric_limits<long long>::max();
vector<long long> adj[N];
long long dist[N];
long long parent[N];
long long n, m;

void bfs(long long src)
{
    fill(dist, dist + n + 1, INF);
    fill(parent, parent + n + 1, -1);
    dist[src] = 0;
    parent[src] = src;

    queue<long long> q;
    q.push(src);

    while (!q.empty())
    {
        long long u = q.front();
        q.pop();

        for (const auto &v : adj[u])
        {
            if (dist[v] == INF) // Check if v has not been visited
            {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}
