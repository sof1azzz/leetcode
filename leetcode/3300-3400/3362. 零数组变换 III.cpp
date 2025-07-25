//
// Created by 123 on 25-5-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
public:
  int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
    ranges::sort(queries, [&](const auto& a, const auto& b) {
      return a[0] < b[0];
    });

    int n = nums.size();
    int m = queries.size();
    int j = 0;
    priority_queue<int> pq;
    vector<int> diff(n + 2, 0);
    int prefix_sum = 0;
    for (int i = 0; i < n; i++) {
      int x = nums[i];
      prefix_sum += diff[i];
      while (j < m && queries[j][0] <= i) {
        pq.push(queries[j][1]);
        j++;
      }

      while (!pq.empty() && prefix_sum < x && pq.top() >= i) {
        prefix_sum++;
        diff[pq.top() + 1]--;
        pq.pop();
      }

      if (x > 0) {
        return -1;
      }
    }

    return pq.size();
  }
};

class Solution2 {
public:
  int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
    ranges::sort(queries, [&](const auto& a, const auto& b) {
      return a[0] < b[0];
    });

    int n = nums.size(), j = 0, sum_d = 0;
    vector<int> diff(n + 1, 0);
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
      sum_d += diff[i];
      // 维护左端点 <= i 的区间
      while (j < queries.size() && queries[j][0] <= i) {
        pq.push(queries[j][1]);
        j++;
      }
      // 选择右端点最大的区间
      while (sum_d < nums[i] && !pq.empty() && pq.top() >= i) {
        sum_d++;
        diff[pq.top() + 1]--;
        pq.pop();
      }
      if (sum_d < nums[i]) {
        return -1;
      }
    }
    return pq.size();
  }
};