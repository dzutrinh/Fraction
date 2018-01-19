CC=g++
CFLAGS=-s -Wall -O3 -std=c++11
ifeq ($(OS), Windows_NT)
	RM=del
	OUTPUT=fraction.exe
else
	RM=rm -f
	OUTPUT=fraction
endif

SOURCES=main.cpp \
		fraction.cpp \
		fraction.hpp

all: $(SOURCES)
	$(CC) $(CFLAGS) fraction.cpp main.cpp -o $(OUTPUT)

clean:
	$(RM) $(OUTPUT)
