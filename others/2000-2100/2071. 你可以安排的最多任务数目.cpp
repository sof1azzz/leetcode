#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>
#include <queue>
#include <cstring>
#include <array> 
#include <bitset>

using namespace std;

class Solution {
public:
  int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills,
                    int strength) {
    int m = workers.size();
    ranges::sort(tasks);
    ranges::sort(workers);

    auto check = [&](int target) -> bool {
      deque<int> dq;
      int j = 0;
      int used = 0;
      for (int i = m - target; i < m; i++) {
        int worker = workers[i];
        while (j < tasks.size() && j < target &&
               tasks[j] <= worker + strength) {
          dq.emplace_back(tasks[j++]);
               }

        if (dq.empty()) {
          return false;
        }

        if (worker >= dq.front()) {
          dq.pop_front();
          continue;
        }

        if (used == pills) {
          return false;
        }

        used++;
        dq.pop_back();
      }
      return true;
    };

    int ans = 0;
    int lo = 0;
    int hi = m + 1;
    while (lo < hi) {
      if (const int mid = lo + (hi - lo) / 2; check(mid)) {
        ans = mid;
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    return ans;
  }
};


class Solution2 {
public:
    int maxTaskAssign(vector<int> &tasks, vector<int> &workers, int pills, int strength) {
        ranges::sort(tasks);
        ranges::sort(workers);
        int m = workers.size();

        auto check = [&](int k) -> bool {
            // 贪心：用最强的 k 名工人，完成最简单的 k 个任务
            int i = 0, p = pills;
            deque<int> valid_tasks;
            for (int j = m - k; j < m; j++) { // 枚举工人
                int w = workers[j];
                // 在吃药的情况下，把能完成的任务记录到 valid_tasks 中
                while (i < k && tasks[i] <= w + strength) {
                    valid_tasks.push_back(tasks[i]);
                    i++;
                }
                // 即使吃药也无法完成任务
                if (valid_tasks.empty()) {
                    return false;
                }
                // 无需吃药就能完成（最简单的）任务
                if (w >= valid_tasks.front()) {
                    valid_tasks.pop_front();
                    continue;
                }
                // 必须吃药
                if (p == 0) { // 没药了
                    return false;
                }
                p--;
                // 完成（能完成的）最难的任务
                valid_tasks.pop_back();
            }
            return true;
            };

        int left = 0, right = min((int)tasks.size(), m) + 1;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (check(mid) ? left : right) = mid;
        }
        return left;
    }
};