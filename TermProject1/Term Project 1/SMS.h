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
	//SMS Ŭ������ ������. ���ڷ� phoneNum�� ���޹޴´�.
	//phoneNum�� �ش��ϴ� SMS ���� ������ Ž�� �� ������ �� �ش� ������ ��� SMS txt ������ �о�鿩 v_Message �����̳ʿ� �����Ѵ�.
	
	SMS(char* phoneNum, char* IndexOnly);
	//SMSŬ������ Ư�� ������. ���ڷ� phoneNum�� �Բ� �ƹ��ų� ���ǹ��� ���ڿ� �ϳ��� �� ������ �ȴ�.
	//phoneNum�� �ش��ϴ� SMS ���� ������ Ž�� �� ������ ��, �ش� ������ Index ���ϸ��� �д´�.

	vector<Message>::iterator GetBeginIter(); // v_Message.begin()�� Getter
	vector<Message>::iterator GetEndIter(); // v_Message.end()�� Getter
	void DeleteSMS(); //�̱���
	void SendSMS(Message* tempMessage); // Message�� ����ü �����͸� �μ��� ���޹޾� �̸� txt ���Ϸ� �����ϴ� �Լ�.
	int GetSMSNum(); // message_Num�� Getter
};