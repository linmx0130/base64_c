OBJS = main.o encode.o
CC = gcc
CFLAGS =
CLIBS = 
TARGET = base64

all: $(TARGET)

main.o: main.c base64.h
	$(CC) -c -o main.o main.c
encode.o: encode.c base64.h
	$(CC) -c -o encode.o encode.c
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

clean:
	rm $(OBJS)

