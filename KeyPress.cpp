// KeyPress.cpp
#include "stdafx.h"

#include "KeyPress.h"


void pressKey(WORD t, int x){
	// This structure will be used to create the keyboard
    // input event.
    INPUT ip;
	bool checkFlag = false;
	time_t timerStart;
	time_t timerNow;
	time_t timerDiff;
	timerStart = time(NULL);

    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
 
    // Press the "A" key

	while(checkFlag==false){
			if(Skill_Status(x)==true){
				ip.ki.wVk = t; // virtual-key code for the "a" key
			    ip.ki.dwFlags = 0; // 0 for key press
                SendInput(1, &ip, sizeof(ip)); 
                // Release the "A" key
                ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
                SendInput(1, &ip, sizeof(ip));

				checkFlag = true; //key pressed exit loop
				std::cout << "key Pressed"<<std::endl;
				Sleep(250);
			}
			else{
				Sleep(500);
				//std::cout << "sleep key not ready"<<std::endl;
			}
			timerNow = time(NULL);
			timerDiff = difftime(timerNow,timerStart);
			std::cout <<"time: " <<timerDiff <<std::endl;

			if(timerDiff > 12){
				std::cout <<"taking to long: " << std::endl;
				checkFlag = true;
			}
	}
	

}

bool Skill_Status(WORD t){
	HDC _hdc = GetDC(NULL);
	COLORREF skill;
	bool onFlag = false;

	int	_red;
	int	_green;
	int	_blue;

	if(t>0){
		Sleep(200);
		skill = GetPixel(_hdc,558 ,728);
		_red = GetRValue(skill);
		_green = GetGValue(skill);
		_blue = GetBValue(skill);
		if(_red==255 && _green == 247 && _blue==255){
			onFlag = true;
			Sleep(200);
		}
		else{
			onFlag = false;
		}

	}
	
	std::cout << _red << std::endl; 
	std::cout << _green <<std::endl;
	std::cout << _blue <<std::endl;

	ReleaseDC(NULL,_hdc);
	return onFlag;

}

void pressKey_static(WORD t){


	INPUT ip;

    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
	
	ip.ki.wVk = t; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(ip)); 
    // Release the "A" key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(ip));

}

void leftMouseClick(){
	INPUT mouseIn;
	mouseIn.type = INPUT_MOUSE;
	mouseIn.mi.time = 0;
	mouseIn.mi.dwExtraInfo = 0;
	mouseIn.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1,&mouseIn,sizeof(mouseIn));
	mouseIn.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	Sleep(75);
	SendInput(1,&mouseIn,sizeof(mouseIn));
}

void rightMouseClick(){
	INPUT mouseIn;
	mouseIn.type = INPUT_MOUSE;
	mouseIn.mi.time = 0;
	mouseIn.mi.dwExtraInfo = 0;
	mouseIn.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1,&mouseIn,sizeof(mouseIn));
	mouseIn.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	Sleep(75);
	SendInput(1,&mouseIn,sizeof(mouseIn));
}

void EnterString(string x){
	string temp = x;
	if (temp.compare("Rubby De La Rosa")==0){
		temp = "Rubby De";
	}

	for(int y = 0; y<temp.length(); y++){
		//Sleep(150);
		if(temp[y]=='a' || temp[y]=='A'){
			pressKey_static(0x41);
		}
		else if(temp[y]=='b' || temp[y]=='B'){
			pressKey_static(0x42);
		}
		else if(temp[y]=='c' || temp[y]=='C'){
			pressKey_static(0x43);
		}
		else if(temp[y]=='d' || temp[y]=='D'){
			pressKey_static(0x44);
		}
		else if(temp[y]=='e' || temp[y]=='E'){
			pressKey_static(0x45);
		}
		else if(temp[y]=='f' || temp[y]=='F'){
			pressKey_static(0x46);
		}
		else if(temp[y]=='g' || temp[y]=='G'){
			pressKey_static(0x47);
		}
		else if(temp[y]=='h'|| temp[y]=='H'){
			pressKey_static(0x48);
		}
		else if(temp[y]=='i' || temp[y]=='I'){
			pressKey_static(0x49);
		}
		else if(temp[y]=='j' || temp[y]=='J'){
			pressKey_static(0x4A);
		}
		else if(temp[y]=='k' || temp[y]=='K'){
			pressKey_static(0x4B);
		}
		else if(temp[y]=='l'|| temp[y]=='L'){
			pressKey_static(0x4C);
		}
		else if(temp[y]=='m' || temp[y]=='M'){
			pressKey_static(0x4D);
		}
		else if(temp[y]=='n'|| temp[y]=='N'){
			pressKey_static(0x4E);
		}
		else if(temp[y]=='o'|| temp[y]=='O'){
			pressKey_static(0x4F);
		}
		else if(temp[y]=='p' || temp[y]=='P'){
			pressKey_static(0x50);
		}
		else if(temp[y]=='q' || temp[y]=='Q'){
			pressKey_static(0x51);
		}
		else if(temp[y]=='r' || temp[y]=='R'){
			pressKey_static(0x52);
		}
		else if(temp[y]=='s' || temp[y]=='S'){
			pressKey_static(0x53);
		}
		else if(temp[y]=='t' || temp[y]=='T'){
			pressKey_static(0x54);
		}
		else if(temp[y]=='u'|| temp[y]=='U'){
			pressKey_static(0x55);
		}
		else if(temp[y]=='v' || temp[y]=='V'){
			pressKey_static(0x56);
		}
		else if(temp[y]=='w'|| temp[y]=='W'){
			pressKey_static(0x57);
		}
		else if(temp[y]=='x' || temp[y]=='X'){
			pressKey_static(0x58);
		}else if(temp[y]=='y' || temp[y]=='Y'){
			pressKey_static(0x59);
		}else if(temp[y]=='z' || temp[y]=='Z'){
			pressKey_static(0x5A);
		}
		else if(temp[y]==' '){
			pressKey_static(0x20);
		}
		else if(temp[y]=='1'){
			pressKey_static(0x31);
		}
		else if(temp[y]=='2'){
			pressKey_static(0x32);
		}
		else if(temp[y]=='3'){
			pressKey_static(0x33);
		}
		else if(temp[y]=='4'){
			pressKey_static(0x34);
		}
		else if(temp[y]=='5'){
			pressKey_static(0x35);
		}
		else if(temp[y]=='6'){
			pressKey_static(0x36);
		}
		else if(temp[y]=='7'){
			pressKey_static(0x37);
		}
		else if(temp[y]=='8'){
			pressKey_static(0x38);
		}
		else if(temp[y]=='9'){
			pressKey_static(0x39);
		}
		else if(temp[y]=='0'){
			pressKey_static(0x31);
		}
		else if(temp[y]=='.'){
			pressKey_static(0xBE);
		}
		else
			y = y + temp.length(); /// exit on error

	}

}