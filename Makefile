
all:
	g++ *.cpp -o a.out

benchmark:
	g++ *.cpp -o benchmark.out -DBENCHMARK

unittest:
	g++ *.cpp -o unittest.out -DUNIT_TEST

clean:
	rm a.out