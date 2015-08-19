#include "stdafx.h"
#include "LineUp.h"




LineUp::LineUp(){
	string Pitcher1 = "";
	string Pitcher2 = "";
	string Catcher = "";
	string firstBase = "";
	string secondBase = "";
	string thirdBase = "";
	string shortStop = "";
	string OutField1 = "";
	string OutFiled2 = "";
	string OutField3 = "";
	Salary = 0;
}
 
void LineUp::setPitcher1(string x){
	Pitcher1 = x;
}
string LineUp::getPitcher1(){
	return Pitcher1;
}
	
void LineUp::setPitcher2(string x){
	Pitcher2 = x;
}
	
string LineUp::getPitcher2(){
	return Pitcher2;
}
	
void LineUp::setCatcher(string x){
	Catcher = x;
}	
	
string LineUp::getCatcher(){
	return Catcher;
}
	
void LineUp::setFirstBase(string x){
	firstBase = x;
}

string LineUp::getFirstBase(){
	return firstBase;
}

void LineUp::setSecondBase(string x){
	secondBase = x;
}

string LineUp::getSecondBase(){
	return secondBase;
}
	
void LineUp::setThirdBase(string x){
	thirdBase = x;
}

string LineUp::getThirdBase(){
	return thirdBase;
}

void LineUp::setShortStop(string x){
	shortStop = x;
}

string LineUp::getShortStop(){
	return shortStop;
}
	
void LineUp::setOutField1(string x){
	OutField1 = x;
}

string LineUp::getOutField1(){
	return OutField1;
}

void LineUp::setOutField2(string x){
	OutFiled2 = x;
}

string LineUp::getOutField2(){
	return OutFiled2;
}
	
void LineUp::setOutField3(string x){
	OutField3 = x;
}

string LineUp::getOutField3(){
	return OutField3;
}

void LineUp::setSalary(int x){
	Salary = x;
}

int LineUp::getSalary(){
	return Salary;
}