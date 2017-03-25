# variables
CC = g++
STD = -std=c++11
NAME = dec

HEADERS = src/server.h

SOURCES = main.cpp \
					src/server.cpp

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
