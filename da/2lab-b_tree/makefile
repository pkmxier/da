CC=g++
CFLAGS=-c -std=c++11 -pedantic -Wall -Wno-sign-compare -Wno-long-long -lm
SOURCES=main.cpp tstring.cpp tbtree.cpp tbtreenode.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=da2

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -frd $(OBJECTS) $(EXECUTABLE)
