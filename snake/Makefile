CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lGL -lGLEW -lglfw -lm

TARGET = main
SOURCES = main.c

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET) $(LDFLAGS) $(CFLAGS)

clean:
	rm -f $(TARGET)
