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
	const _Ty& _Val, _Pr _Pred)	// binary serach ���� �� �ش� Node�� ��ȯ�ϴ� �Լ�
{	// test if _Val equivalent to some element, using _Pred
	_First = _STD lower_bound(_First, _Last, _Val, _Pred);
	return ((_First != _Last && !_Pred(_Val, *_First))) ?
		(_Rechecked(_First,	_Lower_bound(_Unchecked(_First), _Unchecked(_Last), _Val, _Pred, _Dist_type(_First))))
		: _Last;
}
//binary_return �Լ�. binary_search�� ������ ������ vector�� �����̳��� begin�� end, Ž�� ���, Ž�� ���� �Լ��� �����ϸ�
//�ش� Ž�� ���� ��ġ�ϴ� ��尡 ������ �� �ش� ��带 ����Ű�� iterator�� return�ϸ�
//�ش� Ž�� ���� ��ġ�ϴ� ��尡 ���� �� end()�� ����Ű�� iterator�� return�Ѵ�.
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

AddressBook::AddressBook() // ������
{
	file.open("addressBook.txt",ios::in);	// �ؽ�Ʈ ������ �ҷ��´�
	if ( file.is_open() == false ) //������ �ҷ����̴µ� �����ϸ� ���ο� ������ �����Ѵ�.
	{
		ofstream fout("addressBook.txt", ios_base::out);
	}
	else
	{
		while(file>>tempAdd.strName>>tempAdd.strEmail>>tempAdd.addNum) // �̸�, �̸���, ��ȭ��ȣ ������ ���Ͽ��� �ҷ��� �ӽ� ����ü�� �����Ѵ�.
		{
			for(int i=0; i<tempAdd.addNum; i++) //��ȭ��ȣ ������ŭ �ݺ����� ���� ��ȭ��ȣ�� tempAdd�� vector�� �����̳� phone�� push_back�Ѵ�.
			{
				file>>tempPhone.strPhone>>
					tempPhone.phoneGroup;
				tempAdd.phone.push_back(tempPhone);
			}
			v_Address.push_back(tempAdd); // �ϼ��� �ӽ� ����ü tempAdd�� vector�� �����̳� v_Address�� push_back�Ѵ�.
			tempAdd.phone.clear(); //������ ���� tempAdd�� phone �����̳ʸ� clear�Ѵ�.
		}
	}
	sort(v_Address.begin(), v_Address.end(), CompareAddressByName);	// v_Address �����̳ʸ� CompareAddressByName ���ǿ� ���� Sorting�Ѵ�.
}
AddressBook::~AddressBook() //�Ҹ���
{
	ofstream fout("addressBook.txt", ios_base::out); //���� ����� �ǽ��� �� �����Ѵ�.
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
	cout << "----------[�ּҷ� ���]----------"<<endl;
	m_error = false;
	tempAdd.addNum=0;
	cout << "�̸� : "; 	cin >> tempAdd.strName;	// �̸��� �Է¹޴´�

	while(1)
	{
		cout << "�Է��Ͻ� ��ȭ��ȣ�� ������ �����ϼ���" << endl << "1. �޴���   2. ȸ��   3. ��   4. �ѽ�   5. ����";
		cin >> tempPhone.phoneGroup;
		if ( cin.fail() == true) // �Է��� �߸��Ǿ��� ��� �ٽ� �Է¹޴´�.
		{
			cout << "�Է� �����Դϴ�. Ȯ�� �� �ٽ� �Է����ּ���."<<endl;
			continue;
		}
		else if (tempPhone.phoneGroup < 1 || 5 < tempPhone.phoneGroup)
		{
			cout << "1���� 5������ ���ڸ��� �Է����ּ���."<<endl;
			continue;
		}
		else if (tempPhone.phoneGroup == 5)
		{
			if (tempAdd.addNum == 0)
			{
				cout << "��ȭ��ȣ�� �ּ��� 1���� �Է����ּ���"<<endl;
				continue;
			}
			else
				break;
		}
		else
		{
			while(1)
			{
				cin.clear(); // getline �Լ� ��뿡 ������ �־��� ���, �ݺ����� ���ѹݺ��� ���� ���� ������ û���Ѵ�.
				fflush(stdin); // �Է¹��۸� û���Ѵ�.

				cout << "��ȭ��ȣ : ";
				cin.getline (tempPhone.strPhone, sizeof(tempPhone.strPhone)); // ��ȭ��ȣ�� getline �Լ��� ���� �Է¹޴´�.

				if ( cin.fail() == true) // �Է��� �߸��Ǿ��� ��� �ٽ� �Է¹޴´�.
				{
					cout << "�Է� �����Դϴ�. Ȯ�� �� �ٽ� �Է����ּ���."<<endl;
					continue;
				}
				for (int i=0; i<13; i++) // �� ������(13��°)�� NULL ���ڸ� ������ ��ȭ��ȣ �迭�� ��ҵ��� 0~9 ������ ���� ���� - ���� Ȯ���Ͽ� ����ó���Ѵ�.
				{
					if (i == 12)
					{
						if (tempPhone.strPhone[12] == NULL ) // ���� ��ȭ��ȣ (10�ڸ���)�� ��츦 ����Ͽ�, �ι��ڰ� �ϳ� ���� �������� �����Ͽ� ����ó���Ѵ�.
						{
							m_error = false;
							break;
						}
					}
					if ( (tempPhone.strPhone[i] < '0' || '9' < tempPhone.strPhone[i]) && ( tempPhone.strPhone[i] != '-'))
					{
						cout << "�߸��� ��ȭ��ȣ�Դϴ�."<<endl;
						m_error = true; // �߸��� ��ȭ��ȣ�� ��� bool�� ���� error�� true�� �����Ѵ�.
						break;
					}
				}
				if (m_error == true) // bool�� ���� error�� true�̸� false�� �ٲ� �� �ݺ����� �ٽ� �����Ѵ�.
				{
					m_error = false;
					continue;
				}
				tempAdd.phone.push_back(tempPhone);
				tempAdd.addNum++;
				break; // ���������� �ԷµǾ����� �ݺ����� �����Ѵ�.
			}
		}
	}
	cout << "�̸��� : "; 	cin >> tempAdd.strEmail;	// �̸��� �Է¹޴´�
	cout << "�ּҷ� ����� �Ϸ��Ͽ����ϴ�."<<endl;

	v_Address.push_back(tempAdd);
	sort(v_Address.begin(), v_Address.end(), CompareAddressByName);	//�ּҷ��� �����Ѵ�

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
	cout << "--------------------[�ּҷ� ��ü ��ȸ]--------------------"<<endl;
	cout << left << setw(16) << "�̸�" << " | "
		<< setw(10) << "��ȣ ����" << " | "
		<< setw(16) << "��ȭ��ȣ" << " | "
		<< setw(20) << "�̸���" << endl;
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
		cout << left << setw(16) << "�̸�" << " | ";
		for(int j=0; j<iter->addNum; j++)
		{
			cout <<  setw(10) << "��ȣ ����" << " | " << setw(16) << "��ȭ��ȣ" << " | ";
		}
		cout << setw(16) << "�̸���" << endl;
		cout << "--------------------------------------------------------"<<endl;
		cout << left << setw(16) << iter->strName << " | ";
		for(int j=0; j<iter->addNum; j++)
		{
			cout << setw(10) <<	phoneGroupName[iter->phone[j].phoneGroup]<< " | "
				<< setw(16) << iter->phone[j].strPhone << " | ";
		}
		cout << setw(16) << iter->strEmail << endl;
		cout << "--------------------------------------------------------"<<endl;
		cout << "1. SMS / 2.��ȭ / 3.������ : ";

		cin >> choice;
		if (cin.fail() == true)
		{
			cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �����ϼ���." << endl;
			cin.clear();
			fflush(stdin);
		}
		else
		{
			switch (choice)
			{
			case 1 : 
				ShowMessage(iter->phone[0].strPhone); // �ش� ����ڿ��� �޽��� �̷� ���
				SendSMSRenderer(iter->phone[0].strPhone); //�ش� ����ڿ��� �޽��� ����
				break;
			case 2 : cout << "�̱��� ����Դϴ�" << endl;	system("pause");	break;
			case 3 : loop = false; break;
			default :	cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �����ϼ���." << endl;	system("pause");	break;
			}
		}
	}
}

void AddressBook::FindAddressByNameRenderer()
{
	system("cls");
	char tempName[15];
	cout << "�̸��� �Է��ϼ��� :";	cin >> tempName; //�̸��� �Է¹޴´�.
	iter = FindAddressByName(tempName);
	if (iter != v_Address.end())
	{
		ShowAddress(iter);
	}
	else
		cout << "�ش��ϴ� �̸��� ã�� ���߽��ϴ�." << endl;
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
	cout << "��ȭ��ȣ�� �Է��ϼ��� : ";	cin >> tempPhoneNum; //��ȭ��ȣ�� �Է¹޴´�.
	vector<Address>::iterator iter = FindAddressByPhone(tempPhoneNum);
	if (iter != v_Address.end())
	{
		ShowAddress(iter);
	}
	else
	{
		cout << "�ش��ϴ� ��ȭ��ȣ�� ã�� ���߽��ϴ�." << endl;
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
	sort(v_Address.begin(), v_Address.end(), CompareAddressByPhone);	//�ּҷ��� �����Ѵ�
	Phone tempPhone;
	system("cls");
	cout << "��ȭ��ȣ�� �Է��ϼ��� :";	cin >> tempPhone.strPhone; //��ȭ��ȣ�� �Է¹޴´�.
	tempPhone.phoneGroup = 1;
	tempAdd.phone.clear();
	tempAdd.phone.push_back(tempPhone);
	iter = binary_return(v_Address.begin(), v_Address.end(), tempAdd, CompareAddressByPhone);
	if (iter != v_Address.end())
	{
		ShowAddress(iter);
	}
	else
		cout << "�ش��ϴ� ��ȭ��ȣ�� ã�� ���߽��ϴ�." << endl;
	sort(v_Address.begin(), v_Address.end(), CompareAddressByName);	//�ּҷ��� �����Ѵ�
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
			file.getline(tempText, 1);	//'\0'�� ���ۿ��� ������� ���� �ӽ� �ڵ�
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
			cout<<left<<setw(8)<<"�̵��"<<" | ";
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
	cout << "�޽����� �Է��ϼ��� : "; getline(cin, tempMessage.strText);
	
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
		cout << "1. �ּҷ� ���"<<endl;
		cout << "2. �ּҷ� ��ü ��ȸ"<<endl;
		cout << "3. �̸����� �ּҷ� �˻�"<<endl;
		cout << "4. ��ȭ��ȣ�� �ּҷ� �˻�"<<endl;
		cout << "5. �޽��� ������"<<endl;
		cout << "6. �޽��� ����Ʈ ����" << endl;
		cout << "7. ���α׷� ����"<<endl;
		cout << "----------------------------------------------------"<<endl;
		cout << "���� : ";
		fflush(stdin);
		while(1)
		{
			cin >> choice;
			if (cin.fail() == true)
			{
				cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �����ϼ���." << endl;
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
			cout << "��ȭ��ȣ�� �Է��ϼ���: "; fflush(stdin); cin >> tempPhoneNum; SendSMSRenderer(tempPhoneNum);  break;
		case 6 : ShowMessageList_Renderer(); break;
		case 7 : end = true; break;
		default :	cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �����ϼ���." << endl;	system("pause");	break;
		}
		if (end == true)
			break;
	}
}
