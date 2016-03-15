#pragma once
#include <iomanip>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct Phone{
	char strPhone[14];	// 전화번호
	int phoneGroup;		// 전화번호 종류
}Phone;

typedef struct Address{
	char strName[15];	//이름
	vector<Phone> phone; //전화번호 vector 컨테이너
	int addNum;			//전화번호 개수
	char strEmail[40];	 //E-Mail
	int groupID;		//그룹
}Address; // 주소록의 정보를 구조체로 정의한다

typedef struct Message{
	char strPhone[14];//전화번호
	char strDate[20]; //발송일자
	string strText;//메시지 내용
}Message; // 메시지의 정보를 정의한 구조체