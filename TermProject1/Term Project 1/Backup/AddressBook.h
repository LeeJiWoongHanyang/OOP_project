#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
int compare(const void *a , const void *b);
class AddressBook{

private:
	AddressBook() // �ּҷ� ��� ���� �ǹ��ϴ� ������ m_AddNum�� 0���� �ʱ�ȭ��Ű��, temp�� m_AddNum���� 1 ���� ���� �ʱ�ȭ��Ű�� �������̴�.
	{
		file.open("addressBook.txt",ios::in);
		m_AddNum = 0;
		m_Address = (Address *)malloc(sizeof(Address)*(m_AddNum+1));	//����ü �迭�� �����Ҵ����� �����Ѵ�
		if ( file.is_open() ==false ) //������ �ҷ����̴µ� �����ϸ� ���ο� ������ �����Ѵ�.
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
				m_Address = (Address* ) realloc(m_Address,sizeof(Address) * (m_AddNum+1));  // �����Ҵ��� ���� Address �迭�� ������Ų��.
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
	}Address; // ���� ������ ����ü�� �����Ѵ�
	int m_AddNum; // ���� ���� �ǹ��ϴ� ������ �����Ѵ�.
	int temp;
	fstream file;
	// ����ü �迭�� ������ ��Ҹ� temp�� �����Ͽ�, ���� ������ �����ϴ� ���
	// �ּҷ��� ������ �˻��� ���� �ӽ� ����ҷ� ����Ѵ�.

	Address* m_Address; // ���� �Ҵ��� ����ü �迭�� �����Ѵ�.
	bool m_error; // ����ó���� ���� bool�� ������ �����Ѵ�.

	void ShowAddress(int n);	// ����ü �迭�� n��° �ּҷ��� ������ ����ϴ� void(int)�� �Լ��̴�.
	//{
	//	cout << "�̸� : " << m_Address[n].strName << endl;
	//	cout << m_Address[n].phoneGroup1 <<" : " << m_Address[n].phoneGroup1 << endl;
	//	if (m_Address[n].phoneGroup2)
	//		cout << m_Address[n].phoneGroup2 <<" : " << m_Address[n].phoneGroup2 << endl;
	//	if (m_Address[n].strEmail != "")
	//		cout << "�̸��� : " << m_Address[n].strEmail << endl;
	//}

	void GetAddress(); // ����ü �迭�� n��° �ּҷ��� ������ �Է��ϴ� void(int)�� �Լ��̴�.

	void ReviseAddressByName(); // �Էµ� �̸��� ���� �ּҷ��� ������ �����ϴ� void(void)�� �Լ��̴�.

	void ReviseAddressByPhone(); // �Էµ� ��ȭ��ȣ�� ���� �ּҷ��� ������ �����ϴ� void(void)�� �Լ��̴�.

	void FindAddressByName(); // �Էµ� �̸��� ���� �ּҷ��� ������ ����ϴ� void(void)�� �Լ��̴�.

	void FindAddressByPhone(); // �Էµ� �̸��� ���� �ּҷ��� ������ ����ϴ� void(void)�� �Լ��̴�.

	void DeleteAddress(); // �Էµ� �ּҷ��� ������ �����ϴ� void(void)�� �Լ��̴�.

	void ShowAddressList(); // �Էµ� �ּҷ��� ������ ����Ʈ ���·� ����ϴ� void(void)�� �Լ��̴�.

public:
	static AddressBook& GetInstance()
	{
		static AddressBook MyAddress;
		return MyAddress;
	}
	void ShowMenu(); // �޴��� ����ϴ� �Լ��̴�.
};

#define address AddressBook::GetInstance()