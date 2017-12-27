# -*- coding: utf-8 -*-

def cycleSort(array):
    writes = 0

    for cycleStart in range(0, len(array)-1):
        item = arr[cycleStart]

        pos = cycleStart
        for i in range(cycleStart+1, len(array)):
            if arr[i] < item:
                pos += 1

        if pos == cycleStart:
            continue

        while array[pos] == item:
            pos += 1

        array[pos], item = item, array[pos]
        writes += 1

        while pos != cycleStart:
            pos = cycleStart
            for i in range(cycleStart+1, len(array)):
                if array[i] < item:
                    pos += 1

            while item == array[pos]:
                pos += 1

            array[pos], item = item, array[pos]
            writes += 1

    return writes

if __name__ == "__main__":
    arr = [ 1, 8, 3, 9, 10, 10, 2, 4]
    n = len(arr)
    writes = cycleSort(arr)

    print("After sort : ")
    print(n)
    for i in range(0, n):
        print(arr[i])

    
