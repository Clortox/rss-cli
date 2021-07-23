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

TARGET = $(BIN)/rss-cli

all : $(OBJ)
	$(CC) $(FLAGS) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBRARIES)

.cpp.o :
	$(CC) $(FLAGS) $(CFLAGS) $(LIBRARIES) -c $< -o $@

clean :
	find . -type f -name '*.o' -delete
	rm -rf $(TARGET)
