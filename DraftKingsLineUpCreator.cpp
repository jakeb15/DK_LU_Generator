// DraftKingsLineUpCreator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "KeyPress.h"
#include "PlayerInfo.h"
#include <Windows.h>
#include "LineUp.h"
#include <vector>
#include <fstream>


using namespace std;

void gotoLobby();
void gotoCreateLineup();
void CreateLineUP();
vector<LineUp> LUimport(vector<PlayerInfo> x);
void SelectPlayers(vector<LineUp> x);
void SelectopGuy();
void moveToSearchBox();
std::vector<PlayerInfo> LineUpData(string x);
bool playsPosition(string x, string y);
void ReloadDK();
vector<LineUp> KillDuplicates(vector<LineUp> x);
void PressEnterLineUp(); // hits the create line up after players are selected
void selectHittersTab();
void getCoordinates(int &x, int &y);


//CONFIGURE LineUp number to create and the file name of the dk provided file

//Holds the Draft Kings supplied roster for the players that are draftable
string DKROSTER = "DKroster818";
// Number of Line ups to create
int CreateLUNUMBER= 10;
//////////////////////////////////////////////////////////////////////

////Mouse Coordinates - will assign values with the shift key when asked, dont configure
int MLBDOT_X = 0;
int MLBDOT_Y = 0;

int GAMETIMEDOT_X = 0;
int GAMETIMEDOT_Y = 0;
int CONTINUE_X = 0;
int CONTINUE_Y = 0;

int SearchBOX_X = 0;
int SearchBOX_Y = 0;

int TopGuy_X = 0;
int TopGuy_Y = 0;

int CreateLU_X = 0;
int CreateLU_Y = 0;




int _tmain(int argc, _TCHAR* argv[])
{
	vector<PlayerInfo> pickablePlayers = LineUpData(DKROSTER);
	vector<LineUp> Player_Pool = LUimport(pickablePlayers);
	vector<LineUp> NonDuplicate_Player_Pool;

	ofstream nonDup;
	nonDup.open("C:\\progData\\nonDupList",std::ofstream::out | std::fstream::app);

	/*//test vector//
	for(std::vector<PlayerInfo>::iterator LU = pickablePlayers.begin(); LU != pickablePlayers.end(); LU++){
		cout <<  LU->getName() << " "<< LU->getSalary() << " " << LU->getPos() <<endl;
	}
	*/

	cout << "Lets find the MLB game Dot..." <<endl<<endl;
	getCoordinates(MLBDOT_X,MLBDOT_Y);
	cout << "checking..." << MLBDOT_X << " " << MLBDOT_Y << endl <<endl;
	cout << "Lets find the Game Time Dot..." << endl;
	getCoordinates(GAMETIMEDOT_X,GAMETIMEDOT_Y);
	cout << "checking..." << GAMETIMEDOT_X << " " << GAMETIMEDOT_Y << endl << endl;
	cout << "Lets find the create Line up button" << endl <<endl;
	getCoordinates(CONTINUE_X,CONTINUE_Y);
	cout << "checking..." << CONTINUE_X << " " << CONTINUE_X ;
	cout << "Lets find the Search Box..." <<endl << endl;
	getCoordinates(SearchBOX_X,SearchBOX_Y);
	cout << "checking..." << SearchBOX_X << " " << SearchBOX_Y << endl <<endl;
	cout << "Lets Find top Player.. " << endl <<endl;
	getCoordinates(TopGuy_X,TopGuy_Y);
	cout << "checking..." << TopGuy_X << " " << TopGuy_Y <<endl << endl;
	cout << "Lets find submit line up button ... " << endl <<endl;
	getCoordinates(CreateLU_X,CreateLU_Y);
	cout << "checking..." << CreateLU_X << " " << CreateLU_Y <<endl << endl;
	Sleep(2000);
	cout << endl << endl << "all positions locked in...creating line ups." << endl <<endl;
	cout << "QUICKLY go back to the DraftKings.com Home page" << endl;
	
	Sleep(6000);
	cout << "Open Draftkings.com" << endl;
	cout << "6 Seconds until program begins." << endl;
	Sleep(6000);

	cout << "Now Detecting Duplicates..." << endl;
	NonDuplicate_Player_Pool = KillDuplicates(Player_Pool);

	cout << "putting out non DUP list" << endl;
	for(std::vector<LineUp>::iterator LU = NonDuplicate_Player_Pool.begin(); LU != NonDuplicate_Player_Pool.end(); LU++){
		nonDup << LU->getPitcher1() << endl;
		nonDup << LU->getPitcher2() << endl;
		nonDup << LU->getCatcher() << endl;
		nonDup << LU->getFirstBase() << endl;
		nonDup << LU->getSecondBase() << endl;
		nonDup << LU->getThirdBase() << endl;
		nonDup << LU->getShortStop() << endl;
		nonDup << LU->getOutField1() << endl;
		nonDup << LU->getOutField2() << endl;
		nonDup << LU->getOutField3() << endl;
		nonDup << endl;
	}

	
	gotoCreateLineup();
	Sleep(1500);
	CreateLineUP();
	SelectPlayers(NonDuplicate_Player_Pool);
	
	return 0;
}


void gotoLobby(){
	Sleep(1000);
	SetCursorPos(336,73);
	Sleep(1000);
	leftMouseClick();
}

void gotoCreateLineup(){
	Sleep(1000);
	//SetCursorPos(531,504);
	SetCursorPos(712,473);// new lobby
	Sleep(1000);
	leftMouseClick();
	Sleep(4500);
}

void CreateLineUP(){
	SetCursorPos(MLBDOT_X,MLBDOT_Y);// select sport
	Sleep(1000);
	leftMouseClick();
	Sleep(2000);
	SetCursorPos(GAMETIMEDOT_X,GAMETIMEDOT_Y); // select games
	Sleep(2000);
	leftMouseClick();
	Sleep(2000);
	SetCursorPos(CONTINUE_X,CONTINUE_Y); // continue
	Sleep(2000);
	leftMouseClick();
	Sleep(2000);
}

vector<LineUp> LUimport(vector<PlayerInfo> x){ // parse lineup and places it into lineup vector
	vector<LineUp> AllLUS;
	vector<PlayerInfo> Pickable_Players = x;
	string fileLoc = "C:\\progData\\Generate\\";
	string LUFile = fileLoc  + "DKgenerate0001";
	ifstream myFile(LUFile);
	string templine = "";
	int pos = 0;
	string temp = "";

	ofstream ReadyList;
	ofstream DKGCLU;
	DKGCLU.open("C:\\progData\\DKGenerated",std::ofstream::out);
	ReadyList.open("C:\\progData\\ReadyList",std::ofstream::out | std::fstream::app);


	string firstBasemen[2];
	string secondBaseMen[2];
	string thirdBaseMen[2];
	string shortStop[2];
	string OutField[6];
	string Pitcher[3];
	string catcher[2];



	int salary =0;
	int PlayerCount = 0;
	int pitcherCount = 0;
	int catcherCount = 0;
	int firstbaseCount = 0;
	int secondBaseCount = 0;
	int thirdBaseCount = 0;
	int shortStopCount = 0;
	int OutFieldCount = 0;

	int value;

	//loads player pool
	while(getline(myFile,templine)){
		for(int x=0; x<templine.length();x++){
			if(templine[x]!= '\n'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		} // gets players Name

		for(std::vector<PlayerInfo>::iterator LU = Pickable_Players.begin(); LU != Pickable_Players.end(); LU++){
			if(LU->getName().compare(temp)==0){
				if((playsPosition(LU->getPos(),"SP") || playsPosition(LU->getPos(),"RP")) && pitcherCount < 3){
					cout << LU->getName() << " inserted into Pitcher" << endl;
					Pitcher[pitcherCount] = LU->getName();
					pitcherCount++;
					cout << pitcherCount << endl;
				}
				else if(playsPosition(LU->getPos(),"C") && catcherCount < 2){
					cout << LU->getName() << " inserted into Catcher" << endl;
					catcher[catcherCount] = LU->getName();
					catcherCount++;
					cout << catcherCount << endl;
				}
				else if(playsPosition(LU->getPos(),"1B") && firstbaseCount < 2){
					cout << LU->getName() << " inserted into firstBase" << endl;
					firstBasemen[firstbaseCount] = LU->getName();
					firstbaseCount++;
					cout << firstbaseCount << endl;
				}
				else if(playsPosition(LU->getPos(),"2B") && secondBaseCount < 2){
					cout << LU->getName() << " inserted into secondBase" << endl;
					secondBaseMen[secondBaseCount] = LU->getName();
					secondBaseCount++;
					cout << secondBaseCount << endl;
				}
				else if(playsPosition(LU->getPos(),"3B") && thirdBaseCount < 2){
					cout << LU->getName() << " inserted into thirdbase" << endl;
					thirdBaseMen[thirdBaseCount] = LU->getName();
					thirdBaseCount++;
					cout << thirdBaseCount << endl;
				}
				else if(playsPosition(LU->getPos(),"SS") && shortStopCount < 2){
					cout << LU->getName() << " inserted into ShortStop" << endl;
					shortStop[shortStopCount] = LU->getName();
					shortStopCount++;
					cout << shortStopCount << endl;
				}
				else if(playsPosition(LU->getPos(),"OF") && OutFieldCount < 6){
					cout << LU->getName() << " inserted into OutField" << endl;
					OutField[OutFieldCount] = LU->getName();
					OutFieldCount++;
					cout << OutFieldCount << endl;
				}
				else
					cout << "ERROR PICKING POS" <<endl;
			}
		}
		temp = "";

	}
	//player pool loaded into position arrays
	/*
	cout << "array check..." <<endl;
	cout << "firstBase1" << firstBasemen[rand()%2] << endl;
	cout << "firstBase2"<<firstBasemen[rand()%2] << endl;
	cout <<  "secondbase1" <<secondBaseMen[rand()%2] << endl;
	cout << "thirdbase1"<<thirdBaseMen[rand()%2]<< endl;
	cout << "shortstop1" <<shortStop[rand()%2]<< endl;
	cout <<  "outfield1"<<OutField[rand()%6]<< endl;
	*/

	cout << "pitcher1" <<Pitcher[0]<< endl;
	cout << "pitcher2" <<Pitcher[1]<< endl;
	cout << "Pitcher3" <<Pitcher[2]<< endl;
	//cout << "Pitcher4" << Pitcher[3]<<endl;

	cout << "OF1 " << OutField[0] << endl;
	cout << "OF2 " << OutField[1] << endl;
	cout << "OF3 " << OutField[2] << endl;
	cout << "OF4 " << OutField[3] << endl;
	cout << "OF5 " << OutField[4] << endl;
	cout << "OF6 " << OutField[5] << endl;
	
	bool goFlag = false;
	for(int x = 0; x<1000;x++){
		LineUp* mlbLineUp = new LineUp();

		mlbLineUp->setPitcher1(Pitcher[rand()%3]);
			while(goFlag==false){
				mlbLineUp->setPitcher2(Pitcher[rand()%3]);
				//cout << "setPitcher2 was just hit: new value is.." << mlbLineUp->getPitcher2() << endl;
				if(mlbLineUp->getPitcher1().compare(mlbLineUp->getPitcher2())!=0){
					goFlag = true;
				}
			}
			goFlag = false;
			DKGCLU <<  mlbLineUp->getPitcher1() << " " << "SP1" << endl;
			DKGCLU <<  mlbLineUp->getPitcher2()  << " " << "SP2"<< endl;
			//pitchers picked

			mlbLineUp->setCatcher(catcher[rand()%2]);
			DKGCLU << mlbLineUp->getCatcher()  << " " << "C"<< endl;
			//Catcher Picked

			mlbLineUp->setFirstBase(firstBasemen[rand()%2]);
			DKGCLU << mlbLineUp->getFirstBase() << " " << "1B" << endl;
			//firstBase picked

			mlbLineUp->setSecondBase(secondBaseMen[rand()%2]);
			DKGCLU << mlbLineUp->getSecondBase()  << " " << "2B"<< endl;
			//2nd base picked

			mlbLineUp->setThirdBase(thirdBaseMen[rand()%2]);
			DKGCLU << mlbLineUp->getThirdBase() << " " << "3B" <<endl;
			//3rd base picked

			mlbLineUp->setShortStop(shortStop[rand()%2]);
			DKGCLU << mlbLineUp->getShortStop() << " " << "SS" << endl;
			// SS picked

			mlbLineUp->setOutField1(OutField[rand()%6]);
			while(goFlag==false){
				mlbLineUp->setOutField2(OutField[rand()%6]);
				if(mlbLineUp->getOutField2().compare(mlbLineUp->getOutField1())!=0){
					goFlag = true;
				}
			}
			goFlag = false;
			while(goFlag==false){
				mlbLineUp->setOutField3(OutField[rand()%6]);
				if(mlbLineUp->getOutField3().compare(mlbLineUp->getOutField1())!=0 && mlbLineUp->getOutField3().compare(mlbLineUp->getOutField2())!=0 ){
					goFlag = true;
				}
			}
			goFlag = false;

			DKGCLU << mlbLineUp->getOutField1() << " "<< "OF1" << endl;
			DKGCLU << mlbLineUp->getOutField2() << " "<< "OF2" << endl;
			DKGCLU << mlbLineUp->getOutField3() << " "<< "OF3" << endl;

			for(std::vector<PlayerInfo>::iterator LU = Pickable_Players.begin(); LU != Pickable_Players.end(); LU++){
				if(LU->getName().compare(mlbLineUp->getPitcher1())==0  || LU->getName().compare(mlbLineUp->getPitcher2())==0
					|| LU->getName().compare(mlbLineUp->getCatcher())==0  || LU->getName().compare(mlbLineUp->getFirstBase())==0  
					|| LU->getName().compare(mlbLineUp->getSecondBase())==0  || LU->getName().compare(mlbLineUp->getThirdBase())==0  
					|| LU->getName().compare(mlbLineUp->getShortStop())==0  || LU->getName().compare(mlbLineUp->getOutField1())==0  
					|| LU->getName().compare(mlbLineUp->getOutField2())==0   || LU->getName().compare(mlbLineUp->getOutField3())==0 ){

						salary = salary + LU->getSalary();

				}
			}

			DKGCLU << "Salary: " << salary <<endl;
			DKGCLU << endl;

			if(salary <= 50000 && salary > 49500){
				ReadyList << mlbLineUp->getPitcher1() << endl;
				ReadyList << mlbLineUp->getPitcher2() << endl;
				ReadyList << mlbLineUp->getCatcher() << endl;
				ReadyList << mlbLineUp->getFirstBase() << endl;
				ReadyList << mlbLineUp->getSecondBase() << endl;
				ReadyList << mlbLineUp->getThirdBase() << endl;
				ReadyList << mlbLineUp->getShortStop() << endl;
				ReadyList << mlbLineUp->getOutField1() << endl;
				ReadyList << mlbLineUp->getOutField2() << endl;
				ReadyList << mlbLineUp->getOutField3() << endl;
				ReadyList << endl;
				AllLUS.push_back(*mlbLineUp);
			}
			salary = 0;
	}
	cout << "lineUps Generated" << endl;
	return AllLUS;
}

void SelectPlayers(vector<LineUp> x){
	vector<LineUp> LUP = x;
	int count = 0;

	//while(count<5){
		for(std::vector<LineUp>::iterator LU = LUP.begin(); LU != LUP.end() && count < CreateLUNUMBER; LU++){
			if(GetAsyncKeyState(VK_UP)){
				Sleep(10000);
				cout << "sleeping so taht you can kill process..." << endl;
			}


			moveToSearchBox();
			EnterString(LU->getPitcher1());
			Sleep(200);
			SelectopGuy();
			moveToSearchBox();
			EnterString(LU->getPitcher2());
			Sleep(200);
			SelectopGuy();
			moveToSearchBox();
			EnterString(LU->getCatcher());
			Sleep(200);
			SelectopGuy();
			moveToSearchBox();
			EnterString(LU->getFirstBase());
			Sleep(200);
			SelectopGuy();
			moveToSearchBox();
			EnterString(LU->getSecondBase());
			Sleep(200);
			SelectopGuy();
			moveToSearchBox();
			EnterString(LU->getThirdBase());
			Sleep(200);
			SelectopGuy();
			moveToSearchBox();
			EnterString(LU->getShortStop());
			Sleep(200);
			SelectopGuy();
			moveToSearchBox();
			EnterString(LU->getOutField1());
			//selectHittersTab();
			Sleep(200);
			SelectopGuy();
			moveToSearchBox();
			EnterString(LU->getOutField2());
			//selectHittersTab();
			Sleep(200);
			SelectopGuy();
			moveToSearchBox();
			EnterString(LU->getOutField3());
			//selectHittersTab();
			Sleep(200);
			SelectopGuy();
			Sleep(2000);
			PressEnterLineUp();
			Sleep(4000);
			ReloadDK();
			gotoCreateLineup();
			Sleep(1500);
			CreateLineUP();
			cout << "LineUP# Created: " << count << endl;
			count++;
		}
	//}
}

void SelectopGuy(){
	SetCursorPos(TopGuy_X,TopGuy_Y);
	Sleep(200);
	leftMouseClick();
	Sleep(200);
}
void moveToSearchBox(){
	SetCursorPos(SearchBOX_X,SearchBOX_Y);
	Sleep(200);
	leftMouseClick();
}

//Parse the line up data that is provided by draftkings in a .csv
std::vector<PlayerInfo> LineUpData(string x){
	//PlayerInfo temp;
	string line;
	string fileNumber = x;
	string fileName = "C:\\progData\\LineUps\\"  + fileNumber;
	ifstream infile(fileName);
	string data = "";
	int pos = 0;
	std::vector<PlayerInfo> LineUPS;

	while(getline(infile,line)){
		// get position
		PlayerInfo* temp = new PlayerInfo();
		for(int x = 0; x< line.length(); x++){
			if(line[x]!=' ' && line[x]!='\t'){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setPos(data);
			data = "";
			/// first/lastName
		for(int x = pos+1;x < line.length(); x++){
			if(line[x]!='\t'){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setName(data);
			data = "";
			//// Salary
			for(int x = pos+1;x < line.length(); x++){
			if(line[x]!='\t'){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setSalary(atoi(data.c_str()));
			data = "";
			//Team1...
			for(int x = pos+1;x < line.length(); x++){
			if(line[x]!='@' ){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setTeam1(data);
			data = "";
			//Team2...
			for(int x = pos+1;x < line.length(); x++){
			if(line[x]!=' ' ){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setTeam2(data);
			data = "";
			//time...
			for(int x = pos+1;x < line.length(); x++){
			if(line[x]!='\t' ){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setMatchUP(data);
			data = "";
			//get AVGPTS
			for(int x = pos+1;x < line.length(); x++){
			if(line[x]!='\t'){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setAVGPTS(atof(data.c_str()));
			data = "";

			LineUPS.push_back(*temp);
	}

	return LineUPS;
}


bool playsPosition(string x,string y){
	if (x.find(y) != std::string::npos) {
		return true;
	}
	else
		return false;
}

//moves mouse cursor to address bar and types in draftkings.com - used to reset the bot after a line up is created
void ReloadDK(){
	Sleep(2000);
	SetCursorPos(200,45);
	Sleep(1000);
	leftMouseClick();
	Sleep(1000);
	EnterString("draftkings.com");
	Sleep(500);
	pressKey_static(0x0D);
	Sleep(4000);
}

// takes out all duplicate Line ups.
vector<LineUp> KillDuplicates(vector<LineUp> x){
	vector<LineUp> main = x;
	vector<LineUp> NonDuplicate;
	static bool dupFlag = false;
	int xx = 0;
	for(std::vector<LineUp>::iterator LU = main.begin(); LU != main.end(); LU++){
		xx++;
		for(std::vector<LineUp>::iterator L2 = main.begin()+xx; L2 != main.end(); L2++){
			if(LU->getPitcher1().compare(L2->getPitcher1())==0 || LU->getPitcher1().compare(L2->getPitcher2())==0){
				if(LU->getPitcher2().compare(L2->getPitcher1())==0 || LU->getPitcher2().compare(L2->getPitcher2())==0){
					if(LU->getCatcher().compare(L2->getCatcher())==0){
						if(LU->getFirstBase().compare(L2->getFirstBase())==0){
							if(LU->getSecondBase().compare(L2->getSecondBase())==0){
								if(LU->getThirdBase().compare(L2->getThirdBase())==0){
									if(LU->getShortStop().compare(L2->getShortStop())==0){
										if(LU->getOutField1().compare(L2->getOutField1())==0 || LU->getOutField1().compare(L2->getOutField2())==0 || LU->getOutField1().compare(L2->getOutField3())==0){
											if(LU->getOutField2().compare(L2->getOutField1())==0 || LU->getOutField2().compare(L2->getOutField2())==0 || LU->getOutField2().compare(L2->getOutField3())==0){
												if(LU->getOutField3().compare(L2->getOutField1())==0 || LU->getOutField3().compare(L2->getOutField2())==0 || LU->getOutField3().compare(L2->getOutField3())==0){
													cout << "Duplicate" << endl;
													dupFlag = true;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		if(dupFlag==false){
			NonDuplicate.push_back(*LU);
			cout << "LU pushed back" << endl;
		}
		dupFlag = false;
	}

	return NonDuplicate;
}


//
void PressEnterLineUp(){
	SetCursorPos(CreateLU_X,CreateLU_Y);
	Sleep(1000);
	leftMouseClick();
	Sleep(1000);
}


// if players share the same name the bot will fail to create a line up if they are both playing.
// Ex: chris young kc starting pitcher and chris young the yankee right fielder
// function commented out
void selectHittersTab(){
	Sleep(1000);
	SetCursorPos(682,391);
	Sleep(1000);
	leftMouseClick();
	leftMouseClick();
	Sleep(1000);
}

//gets mouse position when shift key is pressed
void getCoordinates(int &x, int &y){
	cout << "Lets get Coordinates... Press SHIFT KEY to lock in mouse position." << endl;
	bool clickFlag = false;
	POINT mouseSpot;

	while (clickFlag==false){
		if(GetAsyncKeyState(VK_SHIFT)){
			clickFlag = true;
			GetCursorPos(&mouseSpot);
			Sleep(2000);
		}
	}

	x = mouseSpot.x;
	y = mouseSpot.y;

}