CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lGL -lGLEW -lglfw -lm

TARGET = main
SOURCES = main.cpp

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
