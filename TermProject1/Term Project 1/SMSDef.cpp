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
	if ( file.is_open() == false ) //인덱스 파일을 불러들이는데 실패하면 새로운 인덱스 파일을 생성한다.
	{
		message_Num = 0;
		char foldername[256];
		strcpy(foldername, "SMS\\");
		strcat(foldername, phoneNum);
		_mkdir(foldername); // Multi-byte 버전 폴더 생성
		ofstream fout;
		fout.open(filename, ios_base::out);
		fout<<message_Num;
	}
	else //인덱스 파일을 불러오면 인덱스 파일의 내용에 의거하여 해당 폴더 내의 모든 메시지 파일을 읽어들여 vector 컨테이너에 저장한다. 
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
				file.getline(tempText, 1);	//'\0'을 버퍼에서 비워내기 위한 임시 코드
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
	if ( file.is_open() == false ) //인덱스 파일을 불러들이는데 실패하면 새로운 인덱스 파일을 생성한다.
	{
		char foldername[256];
		strcpy(foldername, "SMS\\");
		strcat(foldername, phoneNum);
		_mkdir(foldername); // Multi-byte 버전 폴더 생성
		ofstream fout(filename, ios_base::out);
		message_Num = 0;
		fout<<message_Num;
	}
	else //인덱스 파일을 불러오면 인덱스 파일의 내용에 의거하여 해당 폴더 내의 모든 메시지 파일을 읽어들여 vector 컨테이너에 저장한다. 
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
	ofstream fout_1(filename, ios_base::out); //파일 출력을 실시한 후 종료한다.
	fout_1<<message_Num<<endl<<tempMessage->strDate<<endl<<tempMessage->strPhone<<endl<<tempMessage->strText.c_str()<<endl;

	strcpy(filename, "SMS\\");
	strcat(filename, tempMessage->strPhone);
	strcat(filename, "\\");
	itoa(message_Num, tempNumber, 10);
	strcat(filename, tempNumber);
	strcat(filename, ".txt");
	ofstream fout_2(filename, ios_base::out); //파일 출력을 실시한 후 종료한다.
	fout_2<<tempMessage->strDate<<endl<<tempMessage->strPhone<<endl<<tempMessage->strText.c_str()<<endl;
}