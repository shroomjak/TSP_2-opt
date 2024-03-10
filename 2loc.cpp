#include "2loc.h"
using namespace std;
void Parser::split_input(const string line, string & sx, string & sy) const{
	stringstream str(line);			//make artifical stream
	str >> sx >> sy;			 	//and read from it
}

void Parser::calc_coord(){
	ifstream file(filename);
	if(!file) throw Error(Error::ERROR_OPEN);
	file.seekg(0, std::ios::end);
	if(file.tellg() == 0) throw Error(Error::ERROR_EMPTY);
	file.seekg(0, std::ios::beg);
	string line;
	getline(file, line);
	size = stoi(line);
	while (getline(file, line) and !file.eof()){
		string sx, sy;
		split_input(line, sx, sy);
		coord.push_back(make_pair(stod(sx), stod(sy)));
	}
	file.close();
}
vector<point> Parser::get_coord() const{
	return coord;
}

double Solver::dist(point p1, point p2){
	return sqrt((p1.first-p2.first)*(p1.first-p2.first)+(p1.second-p2.second)*(p1.second-p2.second));
}
double Solver::diff(point a1, point a2, point b1, point b2){
	return -dist(a1, a2)-dist(b1, b2)+dist(a1, b1)+dist(a2, b2);
}

double Solver::pathlen(void){
	double len = 0;
	int size = path.size(); 
	for(int i = 0; i < size; i++)
		len += Solver::dist(path[i], path[(i+1)%size]);
	return len;
}

void Solver::optimize_path(){
	int flag = 1;
	while(flag){
		flag = 0;	
		double delta;
		vector<point>::iterator p1, p2;
		for(p1 = path.begin(); p1+1 != path.end(); ++p1){
			for(p2 = p1+1; p2 != path.end(); ++p2){
				delta = diff(*p1, *(p1+1), *p2, *(p2+1));
				if(delta < -EPS){
					reverse(p1+1, p2+1);
					flag = 1;
				}
			}
		}
	}
}

