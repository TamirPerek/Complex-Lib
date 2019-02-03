build:
		g++ -o test main.cpp
		strip test

clean:
		rm test


test:
		g++ -o test main.cpp
		strip test
		./test
		rm test