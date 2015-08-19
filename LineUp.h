#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

class LineUp{
	string Pitcher1;
	string Pitcher2;
	string Catcher; 
	string firstBase;
	string secondBase;
	string thirdBase;
	string shortStop; 
	string OutField1;
	string OutFiled2;
	string OutField3;
	int Salary;


public:
	LineUp();
	void setPitcher1(string x);
	string getPitcher1();
	void setPitcher2(string x);
	string getPitcher2();
	void setCatcher(string x);
	string getCatcher();
	void setFirstBase(string x);
	string getFirstBase();
	void setSecondBase(string x);
	string getSecondBase();
	void setThirdBase(string x);
	string getThirdBase();
	void setShortStop(string x);
	string getShortStop();
	void setOutField1(string x);
	string getOutField1();
	void setOutField2(string x);
	string getOutField2();
	void setOutField3(string x);
	string getOutField3();
	void setSalary(int x);
	int getSalary();
};