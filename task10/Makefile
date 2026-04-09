CC = g++
CFLAGS = -Wall -Wextra -g

TARGET = bin

SRCS = main.cpp truth/truth.cpp
OBJS = main.o truth/truth.o


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all
