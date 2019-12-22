CFLAGS=-std=gnu++98 -Wall -Werror -pedantic
test: search.o function.h test-bsearch.o
	g++ $(CFLAGS) -o test search.o test-bsearch.o
search.o: search.cpp function.h
	g++ $(CFLAGS) -c search.cpp
test-bsearch.o: test-bsearch.cpp function.h
	g++ $(CFLAGS) -c test-bsearch.cpp
