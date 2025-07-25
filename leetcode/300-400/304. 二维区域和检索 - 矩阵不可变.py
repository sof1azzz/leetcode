from typing import List


class NumMatrix:

    def __init__(self, matrix: List[List[int]]):
        m, n = len(matrix), len(matrix[0])
        mat = [[0] * (n + 1) for _ in range(m + 1)]
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                mat[i][j] = (
                    mat[i - 1][j]
                    + mat[i][j - 1]
                    - mat[i - 1][j - 1]
                    + matrix[i - 1][j - 1]
                )
        self.mat = mat

    def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:
        return (
            self.mat[row2 + 1][col2 + 1]
            - self.mat[row2 + 1][col1]
            - self.mat[row1][col2 + 1]
            + self.mat[row1][col1]
        )


# Your NumMatrix object will be instantiated and called as such:
# obj = NumMatrix(matrix)
# param_1 = obj.sumRegion(row1,col1,row2,col2)
