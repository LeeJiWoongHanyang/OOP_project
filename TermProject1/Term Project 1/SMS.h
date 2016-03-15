#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include "AddressStructs.h"
using namespace std;

class SMS{
private:
	fstream file;
	vector<Message> v_Message;
	int message_Num;
	char filename[256];
public:
	Message tempMessage;
	SMS(char* phoneNum);
	//SMS 클래스의 생성자. 인자로 phoneNum을 전달받는다.
	//phoneNum에 해당하는 SMS 저장 폴더를 탐색 및 생성한 후 해당 폴더의 모든 SMS txt 파일을 읽어들여 v_Message 컨테이너에 저장한다.
	
	SMS(char* phoneNum, char* IndexOnly);
	//SMS클래스의 특수 생성자. 인자로 phoneNum과 함께 아무거나 무의미한 문자열 하나를 더 넣으면 된다.
	//phoneNum에 해당하는 SMS 저장 폴더를 탐색 및 생성한 후, 해당 폴더의 Index 파일만을 읽는다.

	vector<Message>::iterator GetBeginIter(); // v_Message.begin()의 Getter
	vector<Message>::iterator GetEndIter(); // v_Message.end()의 Getter
	void DeleteSMS(); //미구현
	void SendSMS(Message* tempMessage); // Message형 구조체 포인터를 인수로 전달받아 이를 txt 파일로 저장하는 함수.
	int GetSMSNum(); // message_Num의 Getter
};