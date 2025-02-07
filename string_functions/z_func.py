def prefix_function(s):
    n = len(s)
    p = [0] * n
    for i in range(1, n):
        j = p[i - 1]
        while j > 0 and s[i] != s[j]:
            j = p[j - 1]
        if s[i] == s[j]:
            j += 1
        p[i] = j
    return p


def kmp_search(a, b):
    n, m = len(a), len(b)
    p = prefix_function(b)
    positions = []
    j = 0
    count = 0

    for i in range(n):
        while j > 0 and a[i] != b[j]:
            j = p[j - 1]
        if a[i] == b[j]:
            j += 1
        if j == m:
            positions.append(i - m + 2)
            count += 1
            j = p[j - 1]

    return positions, count


a = input()
b = input()
pos, count = kmp_search(a, b)
print(count)
print(*pos)
