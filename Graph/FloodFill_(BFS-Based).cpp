#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool floodFillBFS(int start_x, int start_y, int dest_x, int dest_y, vector<vector<int>> &mat)
{
    int n = mat.size();
    int m = mat[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    // Directions arrays for moving up, down, left, right
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    // Queue for BFS
    queue<pair<int, int>> q;
    q.push({start_x, start_y});
    visited[start_x][start_y] = true;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        // Check if we have reached the destination
        if (x == dest_x && y == dest_y)
        {
            return true;
        }

        // Check all 4 possible directions
        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Check boundaries and if the cell is not visited and is visitable (1)
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && !visited[nx][ny] && mat[nx][ny] == 1)
            {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    return false; // If no path found
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> grid[i][j];
        }
    }

    int start_x = 0, start_y = 0, dest_x = n - 1, dest_y = m - 1; // Adjust these if start and destination are different

    if (floodFillBFS(start_x, start_y, dest_x, dest_y, grid))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}
