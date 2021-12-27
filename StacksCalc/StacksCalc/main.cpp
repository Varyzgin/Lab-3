#include"TStack.h"
#include"TCalculator.h"

void main() {
	double a;
	string s;
	TCalculator str;
	str.SetExpr("((22)+ 8)");
	str.ToPostfix();
	s = str.GetPostfix();
	cout << s << endl;
	a = str.CalcPostfix();
	cout << a << endl;
}