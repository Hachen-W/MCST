CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = bin

SRCS = main.c array/array.c
OBJS = main.o array/array.o


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all
