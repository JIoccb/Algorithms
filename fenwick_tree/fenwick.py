class FenwickTree:
    def __init__(self, n):
        self.size = n
        self.bit = [0] * (n + 1)

    def update(self, idx, delta):
        while idx <= self.size:
            self.bit[idx] += delta
            idx += idx & -idx

    def prefix_sum(self, idx):
        result = 0
        while idx > 0:
            result += self.bit[idx]
            idx -= idx & -idx
        return result

    def range_sum(self, left, right):
        return self.prefix_sum(right) - self.prefix_sum(left - 1)


