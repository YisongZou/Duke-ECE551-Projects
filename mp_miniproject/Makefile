CPPFLAGS = -Wall -Werror -std=c++11 -pedantic -ggdb3
ffosh.: main.o analyst.o var_manager.o
	g++ -o ffosh. main.o analyst.o var_manager.o
main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp
analyst.o: analyst.cpp analyst.hpp
	g++ $(CPPFLAGS) -c analyst.cpp
var_manager.o: var_manager.cpp var_manager.hpp
	g++ $(CPPFLAGS) -c var_manager.cpp
.PHONY: clean
clean:
	rm -f *.o *~ ffosh.
