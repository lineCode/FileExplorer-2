CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = normalmode.h filelisting.h
OBJ = normalmode.o fileList.o openFileList.o
all: openFileList
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

openFileList: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

