#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <utility>
#include <vector>

#define EPS 1e-5

using namespace std;
using point = pair<double, double>;

using namespace std;
class Error{
	string log = "log.txt";
	string Msg;
public:
	enum Err{ERROR_OPEN, ERROR_EMPTY, ERROR_NO_BEGIN, ERROR_NO_END, ERROR_NO_DATA, ERROR_NO_MEMORY,
			 ERROR_BAD_LONGITUDE, ERROR_BAD_LATITUDE, ERROR_BAD_N};
	Error(Err err){
		const char * ERR_MSG[] = {"Error opening file\n", "File is empty\n", "No begin keyword in file\n", 
		"No end keyword in file\n", "No data in opened file\n", "No memory\n", "Bad latitude interval\n", 
		"Bad longitude interval\n", "Bad N (less or equal to 0)\n"};
		Msg = ERR_MSG[err];
	}
	~Error(){}
    void msg(){
		ofstream out(log);
		out << Msg;
	}
};

class Parser{
	int size;
	vector<point> coord;
	string filename;
	void split_input(const string line, string & sx, string & sy) const;
public:
	Parser(string fname = ""){
		size = 0;
		filename = fname;
	}
	~Parser(){}
	
	int get_size() const{return size; }
	void calc_coord();
	vector<point> get_coord() const;
	void show_coord();
	
	Parser * operator= (Parser * p){
		for(auto & elem : p->get_coord())
			coord.push_back(elem);
		size = p->size;
		filename = p->filename;
		return this;
	}
};

class Solver{
	vector<point> path;
	Parser * parser;
	double dist(point p1, point p2);
	double diff(point a1, point a2, point b1, point b2);
public:
	Solver(){}
	Solver(Parser * p){
		parser = p;
		for(const auto & e : p->get_coord())
			path.push_back(e);	//init path 1->2->...->N->1
		path.push_back(*path.begin());
	}
	~Solver(){}
	//double pathlen(vector<pair<int, int>> p);
	void optimize_path();
	double pathlen();
	Solver * operator= (Solver * s){
		//allocate memory
		Parser tmp(*(s->parser));
		parser = &tmp;
		return this;
	}
};
