# variables
CC = g++
STD = -std=c++11 -pthread
NAME = dec

HEADERS = src/clientchat.h

SOURCES = main.cpp src/clientchat.cpp

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
