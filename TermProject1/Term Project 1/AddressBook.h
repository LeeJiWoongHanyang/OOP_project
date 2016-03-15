#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include "AddressStructs.h"
using namespace std;

static char* phoneGroupName[5] = {"오류", "휴대폰", "회사", "집", "팩스"};

class AddressBook{

private:
	AddressBook(); //AddressBook 생성자. 텍스트 파일을 불러와서 v_Address 컨테이너에 저장한 뒤 sorting한다.
	~AddressBook(); //AddressBook 소멸자. v_Address 컨테이너의 내용을 텍스트 파일에 출력한다.

	fstream file;	// 파일 입출력 객체

	vector<Address> v_Address; // 주소록을 담는 vector형 컨테이너.
	Address tempAdd;	// 주소록을 임시로 담아두는 구조체.
	Phone tempPhone;	// 전화번호를 임시로 담아두는 구조체.
	vector<Address>::iterator iter;	// 주소록 vector 컨테이너의 반복자.
	bool m_error; // 예외처리를 위한 bool형 변수.

public:
	void ShowAddress(vector<Address>::iterator iter); // v_Address 컨테이너에서 반복자 iter가 가리키는 노드를 출력하는 함수이다.
	
	void GetAddress(); // 주소록을 입력하는 void형 함수이다.

	void ReviseAddress(vector<Address>::iterator iter); // 입력된 반복자에 대한 주소록의 정보를 수정하는 void(iterator)형 함수이다.(미구현)


	vector<Address>::iterator AddressBook:: FindAddressByName(char* name); // 인자 이름과 동일한 이름을 가진 노드의 반복자를 반환하는 함수이다.
	void FindAddressByNameRenderer(); // FindAddressByName 함수를 보조하는 Renderer 함수

	vector<Address>::iterator AddressBook:: FindAddressByPhone(char* phoneNum); // 인자 전화번호와 동일한 전화번호를 가진 노드의 반복자를 반환하는 함수이다.
	void FindAddressByPhoneRenderer(); // FindAddressByPhone 함수를 보조하는 Renderer 함수

	void FindAddressByPhoneBNSearch(); // 입력된 이름에 대한 주소록의 정보를 출력하는 void(void)형 함수이다.

	void DeleteAddress(); // 입력된 주소록의 정보를 삭제하는 void(void)형 함수이다. (미구현)

	void ShowAddressList(); // 입력된 주소록의 정보를 리스트 형태로 출력하는 void(void)형 함수이다.

	void ShowMessageList_Renderer();

	void SendSMSRenderer(char* phoneNum); // SMS class의 SendSMS 함수에 인자를 전달하기 위한 Renderer 함수.

	void ShowMessage(char* phoneNum);

public:
	static AddressBook& GetInstance()
	{
		static AddressBook MyAddress;
		return MyAddress;
	}
	void ShowMenu(); // 메뉴를 출력하는 함수이다.
};

#define address AddressBook::GetInstance()