CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lGL -lglfw -lm

TARGET = main
SOURCES = main.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
