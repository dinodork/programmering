#!python

from typing import List

def quicksort(l: List[int]) -> List[int]:
    print("quicksorting")
    print(l)
    middle = round(len(l) / 2)
    pivot = l[middle]
    print("pivot")
    print(pivot)
    print("middle")
    print(middle)
    i = 0
    j = len(l) - 1
    while i < j - 1:
        while l[i] <= pivot:
            i = i + 1
        while l[j] > pivot:
            j = j - 1
        l[i], l[j] = l[j], l[i]
    print("first pass")
    print(l)
    print("i = {}".format(i))
    print("j = {}".format(j))


quicksort([5, 4, 3, 2, 1])
quicksort([4, 3, 2, 1, 5])
quicksort([5, 4, 1, 3, 2])
