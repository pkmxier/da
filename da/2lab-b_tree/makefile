CC=g++
CFLAGS=-c -std=c++11 -ftest-coverage -fprofile-arcs -lgcov -pedantic -Wall -Wno-sign-compare -Wno-long-long -lm
SOURCES=main.cpp tstring.cpp tbtree.cpp tbtreenode.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=da2

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -ftest-coverage -fprofile-arcs -lgcov

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -frd $(OBJECTS) $(EXECUTABLE)
