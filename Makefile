
all: cli graphical benchmark unittest

cli:
	g++ *.cpp targets/cli.cpp -o cli.out -I.

graphical:
	g++ *.cpp targets/graphical.cpp -o graphical.out -IC:/SFML/include -LC:/SFML/lib -lsfml-window -lsfml-system -lsfml-graphics -I.

benchmark:
	g++ *.cpp targets/benchmark.cpp -o benchmark.out -I.

unittest:
	g++ *.cpp targets/unittest.cpp -o unittest.out -I.

clean:
	rm -rf *.out