#include <iostream>
#include <windows.h>
#include <limits>
#include <iomanip>
#include <ctime>
#include <string>
#include <chrono>
#include "AddressBook.h"
#include "SMS.h"

template<class _FwdIt, class _Ty, class _Pr> inline
	_FwdIt binary_return(_FwdIt _First, _FwdIt _Last,
	const _Ty& _Val, _Pr _Pred)	// binary serach 시행 후 해당 Node를 반환하는 함수
{	// test if _Val equivalent to some element, using _Pred
	_First = _STD lower_bound(_First, _Last, _Val, _Pred);
	return ((_First != _Last && !_Pred(_Val, *_First))) ?
		(_Rechecked(_First,	_Lower_bound(_Unchecked(_First), _Unchecked(_Last), _Val, _Pred, _Dist_type(_First))))
		: _Last;
}
//binary_return 함수. binary_search가 가능한 상태의 vector형 컨테이너의 begin과 end, 탐색 대상, 탐색 조건 함수를 전달하면
//해당 탐색 대상과 일치하는 노드가 존재할 시 해당 노드를 가리키는 iterator를 return하며
//해당 탐색 대상과 일치하는 노드가 없을 시 end()를 가리키는 iterator를 return한다.
bool CompareAddressByName(Address a, Address b){
	return (strcmp(a.strName, b.strName)==-1) ? true : false;
}

bool CompareAddressByPhone(Address a, Address b){
	return (strcmp( a.phone[0].strPhone, b.phone[0].strPhone)==-1) ? true : false;
}

bool CompareMessageByDate(Message a, Message b){
	return (strcmp( a.strDate, b.strDate )==-1) ? true : false;
}

bool CompareMessageByDateBackward(Message a, Message b){
	return (strcmp( a.strDate, b.strDate )==1) ? true : false;
}

AddressBook::AddressBook() // 생성자
{
	file.open("addressBook.txt",ios::in);	// 텍스트 파일을 불러온다
	if ( file.is_open() == false ) //파일을 불러들이는데 실패하면 새로운 파일을 생성한다.
	{
		ofstream fout("addressBook.txt", ios_base::out);
	}
	else
	{
		while(file>>tempAdd.strName>>tempAdd.strEmail>>tempAdd.addNum) // 이름, 이메일, 전화번호 개수를 파일에서 불러와 임시 구조체에 저장한다.
		{
			for(int i=0; i<tempAdd.addNum; i++) //전화번호 개수만큼 반복문을 돌려 전화번호를 tempAdd의 vector형 컨테이너 phone에 push_back한다.
			{
				file>>tempPhone.strPhone>>
					tempPhone.phoneGroup;
				tempAdd.phone.push_back(tempPhone);
			}
			v_Address.push_back(tempAdd); // 완성된 임시 구조체 tempAdd를 vector형 컨테이너 v_Address에 push_back한다.
			tempAdd.phone.clear(); //재사용을 위해 tempAdd의 phone 컨테이너를 clear한다.
		}
	}
	sort(v_Address.begin(), v_Address.end(), CompareAddressByName);	// v_Address 컨테이너를 CompareAddressByName 조건에 따라 Sorting한다.
}
AddressBook::~AddressBook() //소멸자
{
	ofstream fout("addressBook.txt", ios_base::out); //파일 출력을 실시한 후 종료한다.
	{
		for(vector<Address>::size_type i=0; i<v_Address.size(); i++)
		{
			fout<<
				v_Address[i].strName<<setw(40)<<
				v_Address[i].strEmail<<setw(20)<<
				v_Address[i].addNum;
			for(int j=0; j<v_Address[i].addNum; j++)
			{
				fout<<setw(20)<<
					v_Address[i].phone[j].strPhone<<setw(20)<<
					v_Address[i].phone[j].phoneGroup;
			}
			fout<<endl;
		}
	}
}

void AddressBook::GetAddress()
{
	Phone tempPhone;
	tempAdd.phone.clear();
	system("cls");
	cout << "----------[주소록 등록]----------"<<endl;
	m_error = false;
	tempAdd.addNum=0;
	cout << "이름 : "; 	cin >> tempAdd.strName;	// 이름을 입력받는다

	while(1)
	{
		cout << "입력하실 전화번호의 종류를 선택하세요" << endl << "1. 휴대폰   2. 회사   3. 집   4. 팩스   5. 없음";
		cin >> tempPhone.phoneGroup;
		if ( cin.fail() == true) // 입력이 잘못되었을 경우 다시 입력받는다.
		{
			cout << "입력 오류입니다. 확인 후 다시 입력해주세요."<<endl;
			continue;
		}
		else if (tempPhone.phoneGroup < 1 || 5 < tempPhone.phoneGroup)
		{
			cout << "1부터 5까지의 숫자만을 입력해주세요."<<endl;
			continue;
		}
		else if (tempPhone.phoneGroup == 5)
		{
			if (tempAdd.addNum == 0)
			{
				cout << "전화번호를 최소한 1개는 입력해주세요"<<endl;
				continue;
			}
			else
				break;
		}
		else
		{
			while(1)
			{
				cin.clear(); // getline 함수 사용에 오류가 있었을 경우, 반복문의 무한반복을 막기 위해 오류를 청소한다.
				fflush(stdin); // 입력버퍼를 청소한다.

				cout << "전화번호 : ";
				cin.getline (tempPhone.strPhone, sizeof(tempPhone.strPhone)); // 전화번호를 getline 함수를 통해 입력받는다.

				if ( cin.fail() == true) // 입력이 잘못되었을 경우 다시 입력받는다.
				{
					cout << "입력 오류입니다. 확인 후 다시 입력해주세요."<<endl;
					continue;
				}
				for (int i=0; i<13; i++) // 맨 마지막(13번째)의 NULL 문자를 제외한 전화번호 배열의 요소들이 0~9 사이의 숫자 똑은 - 인지 확인하여 예외처리한다.
				{
					if (i == 12)
					{
						if (tempPhone.strPhone[12] == NULL ) // 구형 전화번호 (10자리수)일 경우를 대비하여, 널문자가 하나 일찍 나오는지 조사하여 예외처리한다.
						{
							m_error = false;
							break;
						}
					}
					if ( (tempPhone.strPhone[i] < '0' || '9' < tempPhone.strPhone[i]) && ( tempPhone.strPhone[i] != '-'))
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
				tempAdd.phone.push_back(tempPhone);
				tempAdd.addNum++;
				break; // 정상적으로 입력되었으면 반복문을 종료한다.
			}
		}
	}
	cout << "이메일 : "; 	cin >> tempAdd.strEmail;	// 이름을 입력받는다
	cout << "주소록 등록을 완료하였습니다."<<endl;

	v_Address.push_back(tempAdd);
	sort(v_Address.begin(), v_Address.end(), CompareAddressByName);	//주소록을 정렬한다

	//file.open("addressBook.txt",ios::app);
	//file<<
	//	tempAdd.strName<<setw(40)<<
	//	tempAdd.strEmail<<setw(20)<<
	//	tempAdd.addNum<<setw(20);
	//for(int i=0; i<tempAdd.addNum; i++)
	//{
	//	file<<
	//		tempAdd.phone[i].strPhone<<setw(20)<<
	//		tempAdd.phone[i].phoneGroup<<setw(20);
	//}
	//file<<endl;
	/*file.open("addressBook.txt", ios_base::out);
	{
	for(vector<Address>::size_type i=0; i<v_Address.size(); i++)
	{
	file<<
	v_Address[i].strName<<setw(40)<<
	v_Address[i].strEmail<<setw(20)<<
	v_Address[i].addNum<<setw(20);
	for(int j=0; j<v_Address[i].addNum; j++)
	{
	file<<
	v_Address[i].phone[j].strPhone<<setw(20)<<
	v_Address[i].phone[j].phoneGroup<<setw(20);
	}
	file<<endl;
	}
	}*/
}

void AddressBook::ShowAddressList()
{
	system("cls");
	fflush(stdin);
	cout << "--------------------[주소록 전체 조회]--------------------"<<endl;
	cout << left << setw(16) << "이름" << " | "
		<< setw(10) << "번호 종류" << " | "
		<< setw(16) << "전화번호" << " | "
		<< setw(20) << "이메일" << endl;
	cout << "--------------------------------------------------------"<<endl;
	for(vector<Address>::size_type i=0; i<v_Address.size(); i++)
	{
		cout << left << setw(16) << v_Address[i].strName << " | "
			<< setw(10) << phoneGroupName[v_Address[i].phone[0].phoneGroup] << " | "
			<< setw(16) << v_Address[i].phone[0].strPhone << " | "
			<< setw(20) << v_Address[i].strEmail << endl;
	}
	cout << "--------------------------------------------------------"<<endl;
	system("pause");
}

void AddressBook::ShowAddress(vector<Address>::iterator iter)
{
	int choice;
	bool loop=true;
	while(loop)
	{
		system("cls");
		cout << left << setw(16) << "이름" << " | ";
		for(int j=0; j<iter->addNum; j++)
		{
			cout <<  setw(10) << "번호 종류" << " | " << setw(16) << "전화번호" << " | ";
		}
		cout << setw(16) << "이메일" << endl;
		cout << "--------------------------------------------------------"<<endl;
		cout << left << setw(16) << iter->strName << " | ";
		for(int j=0; j<iter->addNum; j++)
		{
			cout << setw(10) <<	phoneGroupName[iter->phone[j].phoneGroup]<< " | "
				<< setw(16) << iter->phone[j].strPhone << " | ";
		}
		cout << setw(16) << iter->strEmail << endl;
		cout << "--------------------------------------------------------"<<endl;
		cout << "1. SMS / 2.통화 / 3.나가기 : ";

		cin >> choice;
		if (cin.fail() == true)
		{
			cout << "잘못 입력하셨습니다. 다시 선택하세요." << endl;
			cin.clear();
			fflush(stdin);
		}
		else
		{
			switch (choice)
			{
			case 1 : 
				ShowMessage(iter->phone[0].strPhone); // 해당 사용자와의 메시지 이력 출력
				SendSMSRenderer(iter->phone[0].strPhone); //해당 사용자에게 메시지 전송
				break;
			case 2 : cout << "미구현 기능입니다" << endl;	system("pause");	break;
			case 3 : loop = false; break;
			default :	cout << "잘못 입력하셨습니다. 다시 선택하세요." << endl;	system("pause");	break;
			}
		}
	}
}

void AddressBook::FindAddressByNameRenderer()
{
	system("cls");
	char tempName[15];
	cout << "이름을 입력하세요 :";	cin >> tempName; //이름을 입력받는다.
	iter = FindAddressByName(tempName);
	if (iter != v_Address.end())
	{
		ShowAddress(iter);
	}
	else
		cout << "해당하는 이름을 찾지 못했습니다." << endl;
	system("pause");
}
vector<Address>::iterator AddressBook::FindAddressByName(char* name)
{
	strcpy(tempAdd.strName, name);
	return binary_return(v_Address.begin(), v_Address.end(), tempAdd, CompareAddressByName);;
}

void AddressBook::FindAddressByPhoneRenderer()
{
	char tempPhoneNum[14];
	system("cls");
	cout << "전화번호를 입력하세요 : ";	cin >> tempPhoneNum; //전화번호를 입력받는다.
	vector<Address>::iterator iter = FindAddressByPhone(tempPhoneNum);
	if (iter != v_Address.end())
	{
		ShowAddress(iter);
	}
	else
	{
		cout << "해당하는 전화번호를 찾지 못했습니다." << endl;
	}
	system("pause");
}
vector<Address>::iterator AddressBook::FindAddressByPhone(char* phoneNum)
{
	bool loop = true;
	vector<Address>::iterator iter;
	for(iter = v_Address.begin(); iter<v_Address.end(); iter++)
	{
		for(vector<Phone>::size_type j=0; j<iter->phone.size(); j++)
		{
			//iter->phone[j].strPhone
			if ( strcmp( (((((iter)._Ptr)->phone)._Myfirst)[j]).strPhone, phoneNum)==0 )
			{
				loop = false;
				break;
			}
		}
		if (loop == false)
			break;
	}
	return iter;
}

void AddressBook::FindAddressByPhoneBNSearch()
{
	sort(v_Address.begin(), v_Address.end(), CompareAddressByPhone);	//주소록을 정렬한다
	Phone tempPhone;
	system("cls");
	cout << "전화번호를 입력하세요 :";	cin >> tempPhone.strPhone; //전화번호를 입력받는다.
	tempPhone.phoneGroup = 1;
	tempAdd.phone.clear();
	tempAdd.phone.push_back(tempPhone);
	iter = binary_return(v_Address.begin(), v_Address.end(), tempAdd, CompareAddressByPhone);
	if (iter != v_Address.end())
	{
		ShowAddress(iter);
	}
	else
		cout << "해당하는 전화번호를 찾지 못했습니다." << endl;
	sort(v_Address.begin(), v_Address.end(), CompareAddressByName);	//주소록을 정렬한다
	system("pause");
}

void AddressBook::ShowMessageList_Renderer()
{
	vector<Message> v_SMSIndexlist;
	Message tempSMS;
	char filename[64];
	char tempNumber[3];
	for(vector<Address>::size_type i=0; i<v_Address.size(); i++)
	{
		ifstream file;
		SMS SMSList(v_Address[i].phone[0].strPhone, "ListOnly");
		strcpy(filename, "SMS\\");
		strcat(filename, v_Address[i].phone[0].strPhone);
		strcat(filename, "\\");
		itoa(SMSList.GetSMSNum(), tempNumber, 10);
		strcat(filename, tempNumber);
		strcat(filename, ".txt");
		file.open(filename, ios::in);
		if (file.is_open() == true)
		{
			char tempText[512];
			file.getline(tempSMS.strDate, sizeof(tempSMS.strDate)/sizeof(char)+1);
			file>>tempSMS.strPhone;
			file.getline(tempText, 1);	//'\0'을 버퍼에서 비워내기 위한 임시 코드
			file.getline(tempText, 512);
			tempSMS.strText = (string)tempText;
			v_SMSIndexlist.push_back(tempSMS);
		}
	}
	sort(v_SMSIndexlist.begin(), v_SMSIndexlist.end(), CompareMessageByDateBackward);
	for(vector<Message>::iterator m_iter = v_SMSIndexlist.begin(); m_iter < v_SMSIndexlist.end(); m_iter++)
	{
		this->iter=FindAddressByPhone(m_iter->strPhone);
		if (iter != v_Address.end())
			cout<<left<<setw(8)<<iter->strName<<" | ";
		else
			cout<<left<<setw(8)<<"미등록"<<" | ";
		cout << left << setw(16) << m_iter->strPhone << " | "
			<< setw(16) << m_iter->strDate << " | " << endl
			<< setw(20) << m_iter->strText << endl << endl;
	}
	system("pause");
}

void AddressBook::ShowMessage(char* phoneNum)
{
	SMS v_SMS(phoneNum);
	for (vector<Message>::iterator iter = v_SMS.GetBeginIter(); iter < v_SMS.GetEndIter(); iter++)
	{
		cout << left << setw(16) << iter->strPhone << " | "
			<< setw(16) << iter->strDate << " | " << endl
			<< setw(20) << iter->strText << endl;
	}
}

void AddressBook::SendSMSRenderer(char* phoneNum)
{
	Message tempMessage;
	string tempText;

	using chrono::system_clock;
	time_t rawtime = system_clock::to_time_t(system_clock::now());
	struct tm* ptm = localtime(&rawtime);
	sprintf(tempMessage.strDate, "%04d-%02d-%02d %02d:%02d:%02d", 
		ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	strcpy(tempMessage.strPhone, phoneNum);
	fflush(stdin); 
	cout << "메시지를 입력하세요 : "; getline(cin, tempMessage.strText);
	
	SMS cSMS(phoneNum);
	cSMS.SendSMS(&tempMessage);
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
		cout << "2. 주소록 전체 조회"<<endl;
		cout << "3. 이름으로 주소록 검색"<<endl;
		cout << "4. 전화번호로 주소록 검색"<<endl;
		cout << "5. 메시지 보내기"<<endl;
		cout << "6. 메시지 리스트 보기" << endl;
		cout << "7. 프로그램 종료"<<endl;
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
		case 3 : FindAddressByNameRenderer(); break;
		case 4 : FindAddressByPhoneRenderer(); break;
		case 5 : char tempPhoneNum[14];
			cout << "전화번호를 입력하세요: "; fflush(stdin); cin >> tempPhoneNum; SendSMSRenderer(tempPhoneNum);  break;
		case 6 : ShowMessageList_Renderer(); break;
		case 7 : end = true; break;
		default :	cout << "잘못 입력하셨습니다. 다시 선택하세요." << endl;	system("pause");	break;
		}
		if (end == true)
			break;
	}
}
