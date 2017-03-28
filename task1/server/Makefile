# variables
CC = g++
STD = -std=c++11
NAME = dec
NAME_TEST = dectest

HEADERS = src/server.h \
					src/log.h

SOURCES = main.cpp \
					src/server.cpp \
					src/log.cpp

# release:
# make
# make release
# debug:
# make debug

all:
	$(CC) $(SOURCES) $(HEADERS) -o build/release/$(NAME) $(STD)

release:
	$(CC) $(SOURCES) $(HEADERS) -o build/release/$(NAME) $(STD)

debug:
	$(CC) $(SOURCES) $(HEADERS) -o build/debug/$(NAME) $(STD)

test:
	$(CC) test.cpp -o build/release/$(NAME_TEST) $(STD) -pthread
