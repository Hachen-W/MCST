CC = gcc
CFLAGS = -Wall -Wextra -g -pthread

TARGET = bin

SRCS = main.c fifo/fifo.c
OBJS = main.o fifo/fifo.o


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all
