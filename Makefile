# Makefile for running two programs

# Choose the compiler.
CC = g++ -pthread -std=c++11
# Have the right clean command.
ifeq ($(OS),Windows_NT)
	CLN=del
else
	CLN=rm
endif

BUILD_FILES += distance_functions.o
BUILD_FILES += DataProcessor.o
BUILD_FILES += input_validation.o
BUILD_FILES += KNeighborsClassifier.o
BUILD_FILES += SocketIO.o
BUILD_FILES += Command1_UploadData.o
BUILD_FILES += Command2_AlgorithmSettings.o
BUILD_FILES += Command3_ClassifyData.o
BUILD_FILES += Command4_DisplayResults.o
BUILD_FILES += Command5_downloadResults.o
BUILD_FILES += CLI.o


all: $(BUILD_FILES) server.o client.o
	$(CC) $(BUILD_FILES) server.o -o server.out
	$(CC) $(BUILD_FILES) client.o -o client.out

run: $(BUILD_FILES) server.o client.o
	$(CC) $(BUILD_FILES) server.o -o server.out & $(CC) $(BUILD_FILES) client.o -o client.out

# Build the algs folder
%.o: %.cpp %.h
	$(CC) -c -o $@ $<

server.o: server.cpp
	$(CC) -c -o server.o server.cpp
client.o: client.cpp
	$(CC) -c -o client.o client.cpp

# Clean command
clean:
	$(CLN) *.o server.out client.out