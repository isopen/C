# variables
CC = g++
STD = -std=c++11
NAME = dec

HEADERS = src/channelnotebook.h src/mainnotebook.h

SOURCES = main.cpp src/channelnotebook.cpp src/mainnotebook.cpp

# release:
# make
# make release
# debug:
# make debug

all:
	$(CC) $(SOURCES) $(HEADERS) -o build/release/$(NAME) -L/usr/lib/mysql -lmysqlclient $(STD)

release:
	$(CC) $(SOURCES) $(HEADERS) -o build/release/$(NAME) -L/usr/lib/mysql -lmysqlclient $(STD)

debug:
	$(CC) $(SOURCES) $(HEADERS) -o build/debug/$(NAME) -L/usr/lib/mysql -lmysqlclient $(STD)
