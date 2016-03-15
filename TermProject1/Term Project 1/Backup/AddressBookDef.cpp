#include <iostream>
#include <windows.h>
#include <limits>
#include <iomanip>
#include "AddressBook.h"
int compare(const void *a , const void *b){
	return strcmp( (char*)a , (char*)b );
}
void AddressBook::GetAddress()
{
	system("cls");
	cout << "----------[주소록 등록]----------"<<endl;
	m_error = false;

	cout << "이름 : "; 	cin >> m_Address[m_AddNum].strName;	// 이름을 입력받는다
	while(1)
	{
		cout << "입력하실 전화번호의 종류를 선택하세요" << endl << "1. 휴대폰   2. 회사   3. 집   4. 팩스   5. 없음";
		cin >> m_Address[m_AddNum].phoneGroup1;
		if ( cin.fail() == true) // 입력이 잘못되었을 경우 다시 입력받는다.
		{
			cout << "입력 오류입니다. 확인 후 다시 입력해주세요."<<endl;
			continue;
		}
		if (m_Address[m_AddNum].phoneGroup1 < '1' || '5' < m_Address[m_AddNum].phoneGroup1)
		{
			cout << "1부터 5까지의 숫자만을 입력해주세요."<<endl;
			continue;
		}
		if (m_Address[m_AddNum].phoneGroup1 == '5')
		{
			cout << "전화번호를 최소한 1개는 입력해주세요"<<endl;
			continue;
		}
		break;
	}
	while(1)
	{
		cin.clear(); // getline 함수 사용에 오류가 있었을 경우, 반복문의 무한반복을 막기 위해 오류를 청소한다.
		fflush(stdin); // 입력버퍼를 청소한다.

		cout << "전화번호 : ";
		cin.getline (m_Address[m_AddNum].strPhone1, sizeof(m_Address[m_AddNum].strPhone1)); // 전화번호를 getline 함수를 통해 입력받는다.

		if ( cin.fail() == true) // 입력이 잘못되었을 경우 다시 입력받는다.
		{
			cout << "입력 오류입니다. 확인 후 다시 입력해주세요."<<endl;
			continue;
		}
		for (int i=0; i<13; i++) // 맨 마지막(13번째)의 NULL 문자를 제외한 전화번호 배열의 요소들이 0~9 사이의 숫자 똑은 - 인지 확인하여 예외처리한다.
		{
			if (i == 12)
			{
				if (m_Address[m_AddNum].strPhone1[12] == NULL ) // 구형 전화번호 (10자리수)일 경우를 대비하여, 널문자가 하나 일찍 나오는지 조사하여 예외처리한다.
				{
					m_error = false;
					break;
				}
			}
			if ( (m_Address[m_AddNum].strPhone1[i] < '0' || '9' < m_Address[m_AddNum].strPhone1[i]) && ( m_Address[m_AddNum].strPhone1[i] != '-'))
			{
				cout << "잘못된 전화번호입니다."<<endl;
				m_error = true; // 잘못된 전화번호일 경우 bool형 변수 error에 true를 대입한다.
				break;
			}
		}
		if (m_error == true) // bool형 변수 error가 true이면 false로 바꾼 뒤 반복문을 다시 실행한다.
		{
			m_error = false;
			continue;
		}

		break; // 정상적으로 입력되었으면 반복문을 종료한다.
	}
	while(1)
	{
		cout << "입력하실 전화번호의 종류를 선택하세요" << endl << "1. 휴대폰   2. 회사   3. 집   4. 팩스   5. 없음";
		cin >> m_Address[m_AddNum].phoneGroup2;
		if ( cin.fail() == true) // 입력이 잘못되었을 경우 다시 입력받는다.
		{
			cout << "입력 오류입니다. 확인 후 다시 입력해주세요."<<endl;
			continue;
		}
		if (m_Address[m_AddNum].phoneGroup2 < '1' || '5' < m_Address[m_AddNum].phoneGroup2)
		{
			cout << "1부터 5까지의 숫자만을 입력해주세요."<<endl;
			continue;
		}
		break;
	}
	if (m_Address[m_AddNum].phoneGroup2 != '5')
	{
		while(1)
		{
			cin.clear(); // getline 함수 사용에 오류가 있었을 경우, 반복문의 무한반복을 막기 위해 오류를 청소한다.
			fflush(stdin); // 입력버퍼를 청소한다.

			cout << "전화번호 : ";
			cin.getline (m_Address[m_AddNum].strPhone2, sizeof(m_Address[m_AddNum].strPhone2)); // 전화번호를 getline 함수를 통해 입력받는다.

			if ( cin.fail() == true) // 입력이 잘못되었을 경우 다시 입력받는다.
			{
				cout << "입력 오류입니다. 확인 후 다시 입력해주세요."<<endl;
				continue;
			}
			for (int i=0; i<13; i++) // 맨 마지막(13번째)의 NULL 문자를 제외한 전화번호 배열의 요소들이 0~9 사이의 숫자 똑은 - 인지 확인하여 예외처리한다.
			{
				if (i == 12)
				{
					if (m_Address[m_AddNum].strPhone2[12] == NULL ) // 구형 전화번호 (10자리수)일 경우를 대비하여, 널문자가 하나 일찍 나오는지 조사하여 예외처리한다.
					{
						m_error = false;
						break;
					}
				}
				if ( (m_Address[m_AddNum].strPhone2[i] < '0' || '9' < m_Address[m_AddNum].strPhone2[i]) && ( m_Address[m_AddNum].strPhone2[i] != '-'))
				{
					cout << "잘못된 전화번호입니다."<<endl;
					m_error = true; // 잘못된 전화번호일 경우 bool형 변수 error에 true를 대입한다.
					break;
				}
			}
			if (m_error == true) // bool형 변수 error가 true이면 false로 바꾼 뒤 반복문을 다시 실행한다.
			{
				m_error = false;
				continue;
			}

			break; // 정상적으로 입력되었으면 반복문을 종료한다.
		}
	}
	cout << "이메일 : "; 	cin >> m_Address[m_AddNum].strEmail;	// 이름을 입력받는다
	cout << "고객 등록을 완료하였습니다."<<endl;
	ofstream fout;
	fout.open("addressBook.txt",ios::app);
	fout<<m_Address[m_AddNum].strName<<setw(40)<<
		m_Address[m_AddNum].strEmail<<setw(20)<<
		m_Address[m_AddNum].strPhone1<<setw(20)<<
		m_Address[m_AddNum].strPhone2<<setw(20)<<
		m_Address[m_AddNum].phoneGroup1<<setw(20)<<
		m_Address[m_AddNum].phoneGroup2<<endl;
	m_AddNum++; // 고객 등록이 완료되면 고객의 수를 의미하는 m_CNum 변수를 증감 연산하여 고객의 수가 늘어났음을 전달한다.
	m_Address = (Address* ) realloc(m_Address,sizeof(Address) * (m_AddNum+1));  // 동적할당을 통해 Client 배열을 증가시킨다.
	qsort(m_Address, m_AddNum, sizeof(m_Address[0]), compare);
	fout.open("addressBook.txt", ios_base::out);
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

void AddressBook::ShowAddressList()
{
	system("cls");
	fflush(stdin);
	cout << "--------------------[고객 전체 조회]--------------------"<<endl;
	cout << left << setw(16) << "이름" << " | "
		<< setw(10) << "전화번호" << " | "
		<< setw(6) << "전화번호" << " | "
		<< setw(20) << "이메일" << endl;
	cout << "--------------------------------------------------------"<<endl;
	for (int i = 0; i<m_AddNum; i++)
	{
		cout << left << setw(16) << m_Address[i].strName << " | "
			<< setw(10) << m_Address[i].strPhone1 << " | "
			<< setw(6) << m_Address[i].strPhone2 << " | "
			<< setw(20) << m_Address[i].strEmail << endl;
	}
	cout << "--------------------------------------------------------"<<endl;
	system("pause");
}

void AddressBook::ShowMenu()
{
	int choice;
	bool end = false;
	while(1)
	{
		system("cls");
		cout << "----------------------------------------------------"<<endl;
		cout << "1. 주소록 등록"<<endl;
		cout << "2. 전체 조회"<<endl;
		cout << "3. 프로그램 종료"<<endl;
		cout << "----------------------------------------------------"<<endl;
		cout << "선택 : ";
		fflush(stdin);
		while(1)
		{
			cin >> choice;
			if (cin.fail() == true)
			{
				cout << "잘못 입력하셨습니다. 다시 선택하세요." << endl;
				cin.clear();
				fflush(stdin);
			}
			else
				break;
		}
		switch (choice)
		{
		case 1 : GetAddress();	break;
		case 2 : ShowAddressList();	break;
		case 3 : end = true; break;
		default :	cout << "잘못 입력하셨습니다. 다시 선택하세요." << endl;	system("pause");	break;
		}
		if (end == true)
			break;
	}
	free(m_Address);
}