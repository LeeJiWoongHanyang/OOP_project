#include <iostream>
#include <windows.h>
#include <limits>
#include <iomanip>
#include <direct.h>
#include "SMS.h"

SMS::SMS(char* phoneNum) 
{
	strcpy(filename, "SMS\\");
	strcat(filename, phoneNum);
	strcat(filename, "\\Index.txt");
	file.open(filename, ios::in);
	if ( file.is_open() == false ) //�ε��� ������ �ҷ����̴µ� �����ϸ� ���ο� �ε��� ������ �����Ѵ�.
	{
		message_Num = 0;
		char foldername[256];
		strcpy(foldername, "SMS\\");
		strcat(foldername, phoneNum);
		_mkdir(foldername); // Multi-byte ���� ���� ����
		ofstream fout;
		fout.open(filename, ios_base::out);
		fout<<message_Num;
	}
	else //�ε��� ������ �ҷ����� �ε��� ������ ���뿡 �ǰ��Ͽ� �ش� ���� ���� ��� �޽��� ������ �о�鿩 vector �����̳ʿ� �����Ѵ�. 
	{
		file>>message_Num;
		for(int i=0; i<message_Num; i++)
		{
			ifstream file;
			char number[3];
			strcpy(filename, "SMS\\");
			strcat(filename, phoneNum);
			strcat(filename, "\\");
			itoa(i+1, number, 10);
			strcat(filename, number);
			strcat(filename, ".txt");
			file.open(filename, ios::in);
			if (file.is_open() == true)
			{
				char tempText[512];
				file.getline(tempMessage.strDate, sizeof(tempMessage.strDate)/sizeof(char));
				file>>tempMessage.strPhone;
				file.getline(tempText, 1);	//'\0'�� ���ۿ��� ������� ���� �ӽ� �ڵ�
				file.getline(tempText, 512);
				tempMessage.strText = (string)tempText;
				v_Message.push_back(tempMessage);
			}
		}
	}
} 
SMS::SMS(char* phoneNum, char* IndexOnly)
{
	strcpy(filename, "SMS\\");
	strcat(filename, phoneNum);
	strcat(filename, "\\Index.txt");
	file.open(filename, ios::in);
	if ( file.is_open() == false ) //�ε��� ������ �ҷ����̴µ� �����ϸ� ���ο� �ε��� ������ �����Ѵ�.
	{
		char foldername[256];
		strcpy(foldername, "SMS\\");
		strcat(foldername, phoneNum);
		_mkdir(foldername); // Multi-byte ���� ���� ����
		ofstream fout(filename, ios_base::out);
		message_Num = 0;
		fout<<message_Num;
	}
	else //�ε��� ������ �ҷ����� �ε��� ������ ���뿡 �ǰ��Ͽ� �ش� ���� ���� ��� �޽��� ������ �о�鿩 vector �����̳ʿ� �����Ѵ�. 
	{
		strcpy(filename, "SMS\\");
		strcat(filename, phoneNum);
		strcat(filename, "\\");
		file>>message_Num;	
	}
}
vector<Message>::iterator SMS::GetBeginIter()
{
	return v_Message.begin();
}
vector<Message>::iterator SMS::GetEndIter()
{
	return v_Message.end();
}
int SMS:: GetSMSNum()
{
	return message_Num;
}

void SMS::SendSMS(Message* tempMessage)
{
	char tempNumber[3];
	v_Message.push_back(*tempMessage);
	message_Num++;
	strcpy(filename, "SMS\\");
	strcat(filename, tempMessage->strPhone);
	strcat(filename, "\\Index.txt");
	ofstream fout_1(filename, ios_base::out); //���� ����� �ǽ��� �� �����Ѵ�.
	fout_1<<message_Num<<endl<<tempMessage->strDate<<endl<<tempMessage->strPhone<<endl<<tempMessage->strText.c_str()<<endl;

	strcpy(filename, "SMS\\");
	strcat(filename, tempMessage->strPhone);
	strcat(filename, "\\");
	itoa(message_Num, tempNumber, 10);
	strcat(filename, tempNumber);
	strcat(filename, ".txt");
	ofstream fout_2(filename, ios_base::out); //���� ����� �ǽ��� �� �����Ѵ�.
	fout_2<<tempMessage->strDate<<endl<<tempMessage->strPhone<<endl<<tempMessage->strText.c_str()<<endl;
}