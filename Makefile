CC=g++
EXECUTABLETEST=Test.out
FLAGS=-std=c++17 -Wall 
SOURCETEST=main.cpp

build:
	$(CC) -o $(EXECUTABLETEST) $(SOURCETEST) $(FLAGS) -g -Wextra -Werror -Wc++98-c++11-c++14-c++17-compat
	strip $(EXECUTABLETEST)

run:
	./$(EXECUTABLETEST) 1> out.log 2> error.log

debug:
	$(CC) -o $(EXECUTABLETEST) $(SOURCETEST) $(FLAGS) -g

release:
	$(CC) -o $(EXECUTABLETEST) $(SOURCETEST) $(FLAGS) -O3
	strip $(EXECUTABLETEST)
