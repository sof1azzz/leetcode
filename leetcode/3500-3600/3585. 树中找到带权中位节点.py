from typing import List


class LcaBinaryLifting:
    def __init__(self, edges: List[List[int]]):
        n = len(edges) + 1
        self.m = m = n.bit_length()
        g = [[] for _ in range(n)]
        for x, y, w in edges:
            g[x].append((y, w))
            g[y].append((x, w))

        depth = [0] * n
        dis = [0] * n
        pa = [[-1] * m for _ in range(n)]

        def dfs(x: int, fa: int) -> None:
            pa[x][0] = fa
            for y, w in g[x]:
                if y != fa:
                    depth[y] = depth[x] + 1
                    dis[y] = dis[x] + w
                    dfs(y, x)

        dfs(0, -1)

        for i in range(m - 1):
            for x in range(n):
                if (p := pa[x][i]) != -1:
                    pa[x][i + 1] = pa[p][i]

        self.depth = depth
        self.dis = dis
        self.pa = pa

    def get_kth_ancestor(self, node: int, k: int) -> int:
        for i in range(k.bit_length()):
            if k >> i & 1:
                node = self.pa[node][i]
        return node

    def get_lca(self, x: int, y: int) -> int:
        if self.depth[x] > self.depth[y]:
            x, y = y, x
        y = self.get_kth_ancestor(y, self.depth[y] - self.depth[x])
        if x == y:
            return x
        for i in range(self.m - 1, -1, -1):
            if self.pa[x][i] != self.pa[y][i]:
                x = self.pa[x][i]
                y = self.pa[y][i]
        return self.pa[x][0]

    def get_dis(self, x: int, y: int) -> int:
        return self.dis[x] + self.dis[y] - 2 * self.dis[self.get_lca(x, y)]

    def upto_dis(self, x: int, d: int) -> int:
        dx = self.dis[x]
        for i in range(self.m - 1, -1, -1):
            p = self.pa[x][i]
            if p != -1 and dx - self.dis[p] <= d:
                x = p
        return x


class Solution:
    def findMedian(
        self, n: int, edges: List[List[int]], queries: List[List[int]]
    ) -> List[int]:
        lca_tool = LcaBinaryLifting(edges)
        ans = []
        for a, b in queries:
            if a == b:
                ans.append(a)
                continue

            lca = lca_tool.get_lca(a, b)
            total_dis = lca_tool.get_dis(a, b)
            half = (total_dis + 1) // 2

            da = lca_tool.dis[a] - lca_tool.dis[lca]
            if da >= half:
                to = lca_tool.upto_dis(a, half - 1)
                res = lca_tool.pa[to][0]
            else:
                res = lca_tool.upto_dis(b, total_dis - half)
            ans.append(res)

        return ans


class LcaBinaryLifting:

    def __init__(self, edges: List[List[int]]):
        n = len(edges) + 1
        self.m = m = n.bit_length()
        g = [[] for _ in range(n)]
        for x, y, w in edges:
            g[x].append((y, w))
            g[y].append((x, w))

        depth = [0] * n
        dis = [0] * n
        pa = [[-1] * m for _ in range(n)]

        def dfs(x: int, fa: int) -> None:
            pa[x][0] = fa
            for y, w in g[x]:
                if y != fa:
                    depth[y] = depth[x] + 1
                    dis[y] = dis[x] + w
                    dfs(y, x)

        dfs(0, -1)

        for i in range(m - 1):
            for x in range(n):
                if (p := pa[x][i]) != -1:
                    pa[x][i + 1] = pa[p][i]

        self.depth = depth
        self.dis = dis
        self.pa = pa

    def get_kth_ancestor(self, node: int, k: int) -> int:
        for i in range(k.bit_length()):
            if k >> i & 1:
                node = self.pa[node][i]
        return node

    def get_lca(self, x: int, y: int) -> int:
        if self.depth[x] > self.depth[y]:
            x, y = y, x
        y = self.get_kth_ancestor(y, self.depth[y] - self.depth[x])
        if x == y:
            return x
        for i in range(self.m - 1, -1, -1):
            if self.pa[x][i] != self.pa[y][i]:
                x = self.pa[x][i]
                y = self.pa[y][i]
        return self.pa[x][0]

    def get_dis(self, x: int, y: int) -> int:
        return self.dis[x] + self.dis[y] - self.dis[self.get_lca(x, y)] * 2

    def upto_dis(self, x: int, d: int) -> int:
        dx = self.dis[x]
        for i in range(self.m - 1, -1, -1):
            p = self.pa[x][i]
            if p != -1 and dx - self.dis[p] <= d:
                x = p
        return x


class Solution:
    def findMedian(
        self, n: int, edges: List[List[int]], queries: List[List[int]]
    ) -> List[int]:
        lca_tool = LcaBinaryLifting(edges)
        ans = []
        for a, b in queries:
            if a == b:
                ans.append(a)
                continue

            lca = lca_tool.get_lca(a, b)
            total_dis = lca_tool.get_dis(a, b)
            half = (total_dis + 1) // 2

            da = lca_tool.dis[a] - lca_tool.dis[lca]
            if da >= half:
                to = lca_tool.upto_dis(a, half - 1)
                res = lca_tool.pa[to][0]
            else:
                res = lca_tool.upto_dis(b, total_dis - half)
            ans.append(res)

        return ans
