CC = gcc
CFLAGS = -Wall -Wextra -g -pthread

TARGET = bin

SRCS = main.c array/array.c sort/sort.c
OBJS = main.o array/array.o sort/sort.c


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all
