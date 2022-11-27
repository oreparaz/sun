all: test_sun run_tests

sun: ../sun.c
	cc -c ../sun.c

test_sun: test_sun.cc sun
	# go mod vendor
	go run generate_test_vectors.go > vectors.inc
	c++ -std=c++11 test_sun.cc -o test_sun sun.o

run_tests:
	./test_sun
