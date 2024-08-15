#include <vector>
#include <queue>
#include <limits>

using namespace std;

const long long N = 200005;
const long long INF = numeric_limits<long long>::max();
vector<long long> adj[N];
long long dist[N];
long long parent[N];
long long n, m;

void bfs(const vector<long long> &srcs)
{
    queue<long long> q;

    fill(dist, dist + n + 1, INF);
    for (const auto &src : srcs)
    {
        dist[src] = 0;
        parent[src] = src;
        q.push(src);
    }

    while (!q.empty())
    {
        long long u = q.front();
        q.pop();

        for (const auto &v : adj[u])
        {
            if (dist[v] == INF)
            {
                dist[v] = dist[u] + 1; // Check if v has not been visited
                parent[v] = u;
                q.push(v);
            }
        }
    }
}
