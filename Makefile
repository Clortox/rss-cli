###############################################################################
# Tyler Perkins
# 7-21-21
# Makefile
#

CC = g++

FLAGS  = -pipe

CFLAGS  = -Wall
CFLAGS += -Ofast
#CFLAGS += -g

LIBRARIES = -lcurl

SRC = $(shell find . -name '*.cpp')
OBJ = $(subst .cpp,.o,$(SRC))
BIN = ./bin

PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

TARGET = rss-cli

all : $(OBJ)
	$(CC) $(FLAGS) $(CFLAGS) -o $(BIN)/$(TARGET) $(OBJ) $(LIBRARIES)

.cpp.o :
	$(CC) $(FLAGS) $(CFLAGS) $(LIBRARIES) -c $< -o $@

install : all
	mkdir -p $(PREFIX)/bin
	cp -f $(BIN)/$(TARGET) $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/$(TARGET)

uninstall :
	rm -rf $(PREFIX)/bin/$(TARGET)

clean :
	find . -type f -name '*.o' -delete
	rm -rf $(TARGET)
