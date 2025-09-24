CC = gcc

CFLAGS = -Wall -Werror

LDFLAGS = -lsqlite3

SRCS = socket_server.c chat_server.c

TARGET = server

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o