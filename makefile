main:
	g++ -c 2loc.h
	g++ -c 2loc.cpp
	g++ all.cpp 2loc.cpp -o result
clean:
	rm -f result
