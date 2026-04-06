def main():
    numbers = list(map(int, input().split()))
    length = len(numbers)
    if length == 0:
        return
    temp_index = [1]
    temp_sum = numbers[0]
    result = [0, 0, 0]
    index_start = 0
    for index in range(1, length):
        if numbers[index - 1] < 0 and numbers[index] > 0:
            temp_index.append(index)
        if numbers[index] > numbers[index - 1]:
            temp_sum += numbers[index]
        else:
            if result[0] != max(temp_sum, result[0]):
                result[0] = temp_sum
                result[1] = index_start
                result[2] = index + 1
            temp_sum = 0
            temp_index.append(index)
            index = temp_index.pop(0)
            index_start = index + 1
    if result[0] != max(temp_sum, result[0]):
        result[0] = temp_sum
        result[1] = index_start
        result[2] = index + 1

    print(numbers[result[1]: result[2]])


if __name__ == "__main__":
    main()
