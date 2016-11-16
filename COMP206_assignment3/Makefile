CC=gcc
CFLAGS=-c -Wall
EXECUTABLE=chat

all: $(EXECUTABLE)

$(EXECUTABLE): q3_encrypted_chat.o encryption.o queue.o
	$(CC) q3_encrypted_chat.o encryption.o queue.o -o $(EXECUTABLE)

q3_encrypted_chat.o: q3_encrypted_chat.c
	$(CC) $(CFLAGS) q3_encrypted_chat.c

encryption.o: encryption.c
	$(CC) $(CFLAGS) encryption.c

queue.o: queue.c
	$(CC) $(CFLAGS) queue.c

clean:
	rm *.o $(EXECUTABLE)