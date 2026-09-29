#include<bits/stdc++.h>


using namespace std;

int getMinInconvenience(vector<vector<int>>& grid){
    int n = grid.size();
        int m = grid[0].size();

        // 8 directions because distance is Chebyshev distance
        int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        // dist[i][j] = distance from nearest existing 1
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        queue<pair<int, int>> q;

        // Multi-source BFS
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        // No existing 1
        // We still need to handle this case separately.
        if (q.empty()) {
            // For an empty grid, choose one cell as the new center.
            // The answer is the minimum possible maximum
            // Chebyshev distance from one cell to all cells.
            int ans = INT_MAX;

            for (int r = 0; r < n; r++) {
                for (int c = 0; c < m; c++) {
                    int mx = 0;

                    mx = max(mx, r);
                    mx = max(mx, n - 1 - r);
                    mx = max(mx, c);
                    mx = max(mx, m - 1 - c);

                    ans = min(ans, mx);
                }
            }

            return ans;
        }

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int k = 0; k < 8; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                    continue;

                if (dist[nr][nc] > dist[r][c] + 1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        // Binary search on answer
        int low = 0;
        int high = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                high = max(high, dist[i][j]);
            }
        }

        auto canAchieve = [&](int D) {
            int rowLow = 0;
            int rowHigh = n - 1;

            int colLow = 0;
            int colHigh = m - 1;

            for (int r = 0; r < n; r++) {
                for (int c = 0; c < m; c++) {

                    // This cell needs the new center
                    if (dist[r][c] > D) {

                        // New center must be within D
                        // in both row and column directions.

                        rowLow = max(rowLow, r - D);
                        rowHigh = min(rowHigh, r + D);

                        colLow = max(colLow, c - D);
                        colHigh = min(colHigh, c + D);

                        // No possible position
                        if (rowLow > rowHigh ||
                            colLow > colHigh) {
                            return false;
                        }
                    }
                }
            }

            return true;
        };

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (canAchieve(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        return low;
}

int main(){
    vector<vector<int>> grid = {{0}};
    cout<<getMinInconvenience(grid);

    return 0;
}







/*


Minimum Grid Inconvenience
Amazon logo
Amazon
● Hard
FULLTIME
NEW GRAD
OA
Learn
Seen this before?
Question
Function
Examples
Constraints
Problem statement
Special thanks: ദ്ദി(˵ •̀ ᴗ - ˵ ) ✧ An amazing fren for sharing that this question showed up again today (09-20-2026)

A city is represented by a binary grid. A cell marked 1 is a delivery center, and a cell marked 0 is any other place.

The distance between two cells is the maximum of the absolute row-coordinate difference and the absolute column-coordinate difference. The inconvenience of the grid is the maximum, over every 0 cell, of its distance to the nearest delivery center.

Amazon may open one new delivery center by converting at most one 0 cell into 1. Return the minimum possible inconvenience after this conversion.

Function
getMinInconvenience(grid: int[][]) → int
Examples
Example 1
grid = [[0,0,0,0],[0,0,0,0],[0,0,0,0]]
return = 2
With no existing delivery center, it is optimal to convert the center cell (1,1) to 1. The farthest cells then have distance 2.

Example 2
grid = [[0]]
return = 0
Convert the only cell to a delivery center, leaving no 0 cell with positive distance.

Constraints
1 <= n, m <= 500
0 <= grid[i][j] <= 1


*/