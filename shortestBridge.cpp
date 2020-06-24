#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/shortest-bridge/
int shortestBridge(vector<vector<int>>& vec) {

	// find 1st one in array
	std::queue<size_t> qRow, qCol;
	vector<size_t> srcIsland;

	const size_t nRows = vec.size(), nCols = vec.front().size();
	size_t row = 0, col = 0;
	bool found = false;
	for (; row < nRows; ++row)
	{
		auto it = std::find(vec[row].begin(), vec[row].end(), 1);
		if (it != vec[row].end()) {
			col = std::distance(vec[row].begin(), it);
			qRow.push(row); qCol.push(col);
			srcIsland.push_back(nCols * row + col);
			break;
		}
	}

	// run BFS to find all positions of this island
	vector<vector<int>> dirs { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
	while (!qRow.empty()) {
		row = qRow.front(); col = qCol.front();
		qRow.pop(); qCol.pop();

		for (auto& dir : dirs) {
			if ((row == 0 && dir[0] == -1) || (col == 0 && dir[1] == -1) ||
				(row == nRows - 1 && dir[0] == +1) || (col == nCols - 1 && dir[1] == +1))
				continue;

			size_t nextRow = row + dir[0], nextCol = col + dir[1];
			if (vec[nextRow][nextCol] == 0) continue;
			auto p = nCols * nextRow + nextCol;
			if (std::find(srcIsland.begin(), srcIsland.end(), p) != srcIsland.end())
				continue;

			srcIsland.push_back(nCols * nextRow + nextCol);
			qRow.push(nextRow); qCol.push(nextCol);
		}
	}

	// put all positions from srcIsland to qRow and qCol
	for (size_t p : srcIsland) {
		qRow.push(p / nCols); qCol.push(p % nCols);
	}

	// run BFS on all positions from srcIsland - stop on 1st alien 1 encountered
	int nSteps = 0;
	queue<size_t> qRow1, qCol1;
	while (!qRow.empty()) { // empty here means there is no 2nd island
		while (!qRow.empty()) {
			row = qRow.front(); col = qCol.front();
			qRow.pop(); qCol.pop();

			for (auto& dir : dirs) {
				if ((row == 0 && dir[0] == -1) || (col == 0 && dir[1] == -1) ||
						(row == nRows - 1 && dir[0] == +1) || (col == nCols - 1 && dir[1] == +1))
					continue;

				size_t nextRow = row + dir[0], nextCol = col + dir[1];
				size_t p = nCols * nextRow + nextCol;
				if (std::find(srcIsland.begin(), srcIsland.end(), p) != srcIsland.end())
					continue;

				if (vec[nextRow][nextCol] == 1)
					return nSteps;

				srcIsland.push_back(p); // it's visited
				qRow1.push(nextRow); qCol1.push(nextCol);
			}
		}
		std::swap(qRow, qRow1); std::swap(qCol, qCol1);
		++nSteps;
	}
	return -1;
}

int main() {

	vector<vector<int>> vec{ {1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1} };
	vec = { {1, 0, 0}, {0, 0, 0}, {0, 0, 1} };
	//vec = { {1,0}, {0,1} };
	//vec = { {0,0,0,0,0,0},{0,1,0,0,0,0},{1,1,0,0,0,0},{1,1,0,0,0,0},{0,0,0,0,0,0},{0,0,1,1,0,0 }};
	int nLen = shortestBridge(vec);
	printf("%d\n", nLen);

	return 0;
}
