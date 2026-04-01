CC = gcc
CFLAGS = -Wall -Wextra -g -pthread

TARGET = bin

SRCS = main.c
OBJS = main.o


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all
