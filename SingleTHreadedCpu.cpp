#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        vector<int> result;
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> minHeap;
        vector<pair<int, int>> indexedTasks;
        
        for (int i = 0; i < n; i++) {
            indexedTasks.push_back({tasks[i][0], i});
        }

        sort(indexedTasks.begin(), indexedTasks.end());

        int currentTime = 0;
        int index = 0;

        while (index < n || !minHeap.empty()) {
            while (index < n && indexedTasks[index].first <= currentTime) {
                int taskIndex = indexedTasks[index].second;
                minHeap.push({tasks[taskIndex][1], taskIndex, tasks[taskIndex][0]});
                index++;
            }

            if (minHeap.empty()) {
                currentTime = indexedTasks[index].first;
            } else {
                auto [processTime, taskIndex, enqueueTime] = minHeap.top();
                minHeap.pop();
                result.push_back(taskIndex);
                currentTime += processTime;
            }
        }

        return result;
    }
};
