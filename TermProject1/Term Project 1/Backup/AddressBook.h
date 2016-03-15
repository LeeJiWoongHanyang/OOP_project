#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
int compare(const void *a , const void *b);
class AddressBook{

private:
	AddressBook() // 주소록 등록 수를 의미하는 변수인 m_AddNum을 0으로 초기화시키고, temp를 m_AddNum보다 1 많은 수로 초기화시키는 생성자이다.
	{
		file.open("addressBook.txt",ios::in);
		m_AddNum = 0;
		m_Address = (Address *)malloc(sizeof(Address)*(m_AddNum+1));	//구조체 배열을 동적할당으로 선언한다
		if ( file.is_open() ==false ) //파일을 불러들이는데 실패하면 새로운 파일을 생성한다.
		{
			ofstream fout("addressBook.txt", ios_base::out);
		}
		else
		{
			while(file>>m_Address[m_AddNum].strName>>
				m_Address[m_AddNum].strEmail>>
				m_Address[m_AddNum].strPhone1>>
				m_Address[m_AddNum].strPhone2>>
				m_Address[m_AddNum].phoneGroup1>>
				m_Address[m_AddNum].phoneGroup2)
			{
				m_AddNum++;
				m_Address = (Address* ) realloc(m_Address,sizeof(Address) * (m_AddNum+1));  // 동적할당을 통해 Address 배열을 증가시킨다.
			}
		}
		qsort(m_Address, m_AddNum, sizeof(m_Address[0]), compare);
		temp = m_AddNum+1;
		ofstream fout("addressBook.txt", ios_base::out);
		{
			for(int i=0; i<m_AddNum; i++)
			{
				fout<<
					m_Address[i].strName<<setw(40)<<
					m_Address[i].strEmail<<setw(20)<<
					m_Address[i].strPhone1<<setw(20)<<
					m_Address[i].strPhone2<<setw(20)<<
					m_Address[i].phoneGroup1<<setw(20)<<
					m_Address[i].phoneGroup2<<endl;
			}
		}
	}
	typedef struct Address{
		char strName[15];
		char strPhone1[14];
		char strPhone2[14];
		char strEmail[20];
		char phoneGroup1;
		char phoneGroup2;
		int groupID;
	}Address; // 고객의 정보를 구조체로 정의한다
	int m_AddNum; // 고객의 수를 의미하는 변수를 선언한다.
	int temp;
	fstream file;
	// 구조체 배열의 마지막 요소를 temp로 지정하여, 고객의 정보를 저장하는 대신
	// 주소록의 정보를 검색할 때의 임시 저장소로 사용한다.

	Address* m_Address; // 동적 할당할 구조체 배열을 선언한다.
	bool m_error; // 예외처리를 위한 bool형 변수를 선언한다.

	void ShowAddress(int n);	// 구조체 배열의 n번째 주소록의 정보를 출력하는 void(int)형 함수이다.
	//{
	//	cout << "이름 : " << m_Address[n].strName << endl;
	//	cout << m_Address[n].phoneGroup1 <<" : " << m_Address[n].phoneGroup1 << endl;
	//	if (m_Address[n].phoneGroup2)
	//		cout << m_Address[n].phoneGroup2 <<" : " << m_Address[n].phoneGroup2 << endl;
	//	if (m_Address[n].strEmail != "")
	//		cout << "이메일 : " << m_Address[n].strEmail << endl;
	//}

	void GetAddress(); // 구조체 배열의 n번째 주소록의 정보를 입력하는 void(int)형 함수이다.

	void ReviseAddressByName(); // 입력된 이름에 대한 주소록의 정보를 수정하는 void(void)형 함수이다.

	void ReviseAddressByPhone(); // 입력된 전화번호에 대한 주소록의 정보를 수정하는 void(void)형 함수이다.

	void FindAddressByName(); // 입력된 이름에 대한 주소록의 정보를 출력하는 void(void)형 함수이다.

	void FindAddressByPhone(); // 입력된 이름에 대한 주소록의 정보를 출력하는 void(void)형 함수이다.

	void DeleteAddress(); // 입력된 주소록의 정보를 삭제하는 void(void)형 함수이다.

	void ShowAddressList(); // 입력된 주소록의 정보를 리스트 형태로 출력하는 void(void)형 함수이다.

public:
	static AddressBook& GetInstance()
	{
		static AddressBook MyAddress;
		return MyAddress;
	}
	void ShowMenu(); // 메뉴를 출력하는 함수이다.
};

#define address AddressBook::GetInstance()