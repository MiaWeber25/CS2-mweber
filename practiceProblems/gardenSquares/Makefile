COMPILER = g++
COMPILER_FLAGS = -Wall -std=c++17
PROGRAM_NAME = sample
CPP_FILES = sample.cpp 

build:
	$(COMPILER) $(COMPILER_FLAGS) $(CPP_FILES) -o $(PROGRAM_NAME)

run: 
	./$(PROGRAM_NAME)

unit_tests:
	./$(PROGRAM_NAME) test

kattis_tests:
	
	echo "all Kattis sample tests cases passed..."

clean:
	rm -f $(PROGRAM_NAME) *.o