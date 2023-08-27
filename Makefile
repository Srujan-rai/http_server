
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -pthread


SRC = myserver.cpp


TARGET = myserver

all: $(TARGET)

$(TARGET): $(SRC)
    $(CXX) $(CXXFLAGS) -o $@ $^

clean:
    rm -f $(TARGET)

.PHONY: all clean
