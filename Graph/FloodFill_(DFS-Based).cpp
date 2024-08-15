#include <iostream>
#include <vector>
using namespace std;

bool floodFillDFS(int x, int y, vector<vector<bool>> &visited, int n, int m, vector<vector<int>> &mat, int dest_x, int dest_y)
{
    // Base cases
    if (x == dest_x && y == dest_y) // Destination reached
        return true;
    if (x >= n || y >= m || x < 0 || y < 0) // Out of bounds
        return false;
    if (visited[x][y]) // Already visited
        return false;
    if (mat[x][y] == 0) // Not a visitable cell
        return false;

    // Mark the cell as visited
    visited[x][y] = true;

    // Explore the four directions (right, left, down, up)
    if (floodFillDFS(x + 1, y, visited, n, m, mat, dest_x, dest_y))
        return true;
    if (floodFillDFS(x - 1, y, visited, n, m, mat, dest_x, dest_y))
        return true;
    if (floodFillDFS(x, y + 1, visited, n, m, mat, dest_x, dest_y))
        return true;
    if (floodFillDFS(x, y - 1, visited, n, m, mat, dest_x, dest_y))
        return true;

    return false; // No path found
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

    int start_x = 0, start_y = 0, dest_x = n - 1, dest_y = m - 1; // Starting and destination cells

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    if (floodFillDFS(start_x, start_y, visited, n, m, grid, dest_x, dest_y))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}
