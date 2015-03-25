OBJS = main.o encode.o decode.o
CC = gcc
CFLAGS = -g
CLIBS = 
TARGET = base64

all: $(TARGET)

main.o: main.c base64.h
	$(CC) -c -o main.o main.c $(CFLAGS)
encode.o: encode.c base64.h
	$(CC) -c -o encode.o encode.c $(CFLAGS)
decode.o: decode.c base64.h
	$(CC) -c -o decode.o decode.c $(CFLAGS) 
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

clean:
	rm $(OBJS)

