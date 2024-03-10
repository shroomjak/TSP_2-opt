#include "2loc.h"
using namespace std;
int main(void){
	string input_file = "data.txt";
	Parser parser(input_file);
	parser.calc_coord();
	
	Solver solver(&parser);
	solver.optimize_path();	
	
	cout << solver.pathlen() << endl;
	return 0;
}
