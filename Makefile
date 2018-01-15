CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wpedantic
LDFLAGS= 
OBJFILES=avl.o main.o
TARGET=simulacao

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET)* *~
