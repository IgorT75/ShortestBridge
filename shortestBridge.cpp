#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/shortest-bridge/
int shortestBridge(vector<vector<int>>& vec) {
	
	size_t s1 = 0, nRows = vec.size(), nCols = vec.front().size();
	for (size_t i = 0, n = nRows; i < n; ++i)
		for (size_t j = 0, m = nCols; j < n; ++j)
			if (vec[i][j] == 1)
				s1 = nCols * i + j;

	std::queue<size_t> qRow, qCol;


}

int main() {
	
	vector<vector<int>> vec{ {1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1} };
	int nLen = shortestBridge(vec);
	printf("%d ", nLen);

	return 0;
}