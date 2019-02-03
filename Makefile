build:
		g++ -o test main.cpp -std=c++11
		strip test

clean:
		rm test


test:
		g++ -o test main.cpp -std=c++11
		strip test
		./test
		rm test
