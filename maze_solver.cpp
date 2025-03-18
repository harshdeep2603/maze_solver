#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Cell {
    int x, y, dist;
};

// Directions for moving in 4 directions (up, down, left, right)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Function to check if a position is within bounds and not blocked
bool isValid(int x, int y, vector<vector<int>>& maze, vector<vector<bool>>& visited) {
    return x >= 0 && y >= 0 && x < maze.size() && y < maze[0].size() && 
           maze[x][y] == 0 && !visited[x][y];
}

// BFS function to find the shortest path in the maze
int bfs(vector<vector<int>>& maze, pair<int, int> start, pair<int, int> end) {
    int rows = maze.size();
    int cols = maze[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    
    queue<Cell> q;
    q.push({start.first, start.second, 0});
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        Cell curr = q.front();
        q.pop();

        // If we reached the destination, return the distance
        if (curr.x == end.first && curr.y == end.second)
            return curr.dist;

        // Explore all 4 directions
        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (isValid(nx, ny, maze, visited)) {
                q.push({nx, ny, curr.dist + 1});
                visited[nx][ny] = true;
            }
        }
    }
    return -1; // Return -1 if no path is found
}

int main() {
    vector<vector<int>> maze = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}
    };
    
    pair<int, int> start = {0, 0};
    pair<int, int> end = {4, 4};

    int shortestPath = bfs(maze, start, end);

    if (shortestPath != -1)
        cout << "Shortest path length: " << shortestPath << endl;
    else
        cout << "No path found!" << endl;

    return 0;
}
