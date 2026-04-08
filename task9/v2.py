def main():
    numbers = list(map(int, input().split()))
    length = len(numbers)
    if length == 0:
        return
    temp_sum = 0
    result = [0, 0, 0]
    index_start = 0
    for index in range(length):
        if numbers[index] > numbers[index - 1]:
            temp_sum += numbers[index]
        else:
            temp_sum = numbers[index]
            index_start = index

        if result[2] - result[1] != max(
                index + 1 - index_start, result[2] - result[1]
                ) \
                or (
                result[2] - result[1] == index + 1 - index_start and
                temp_sum > result[0]
                ):
            result[0] = temp_sum
            result[1] = index_start
            result[2] = index + 1

    print(*numbers[result[1]: result[2]])


if __name__ == "__main__":
    main()
