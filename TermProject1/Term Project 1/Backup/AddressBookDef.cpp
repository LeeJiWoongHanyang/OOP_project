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
	cout << "----------[�ּҷ� ���]----------"<<endl;
	m_error = false;

	cout << "�̸� : "; 	cin >> m_Address[m_AddNum].strName;	// �̸��� �Է¹޴´�
	while(1)
	{
		cout << "�Է��Ͻ� ��ȭ��ȣ�� ������ �����ϼ���" << endl << "1. �޴���   2. ȸ��   3. ��   4. �ѽ�   5. ����";
		cin >> m_Address[m_AddNum].phoneGroup1;
		if ( cin.fail() == true) // �Է��� �߸��Ǿ��� ��� �ٽ� �Է¹޴´�.
		{
			cout << "�Է� �����Դϴ�. Ȯ�� �� �ٽ� �Է����ּ���."<<endl;
			continue;
		}
		if (m_Address[m_AddNum].phoneGroup1 < '1' || '5' < m_Address[m_AddNum].phoneGroup1)
		{
			cout << "1���� 5������ ���ڸ��� �Է����ּ���."<<endl;
			continue;
		}
		if (m_Address[m_AddNum].phoneGroup1 == '5')
		{
			cout << "��ȭ��ȣ�� �ּ��� 1���� �Է����ּ���"<<endl;
			continue;
		}
		break;
	}
	while(1)
	{
		cin.clear(); // getline �Լ� ��뿡 ������ �־��� ���, �ݺ����� ���ѹݺ��� ���� ���� ������ û���Ѵ�.
		fflush(stdin); // �Է¹��۸� û���Ѵ�.

		cout << "��ȭ��ȣ : ";
		cin.getline (m_Address[m_AddNum].strPhone1, sizeof(m_Address[m_AddNum].strPhone1)); // ��ȭ��ȣ�� getline �Լ��� ���� �Է¹޴´�.

		if ( cin.fail() == true) // �Է��� �߸��Ǿ��� ��� �ٽ� �Է¹޴´�.
		{
			cout << "�Է� �����Դϴ�. Ȯ�� �� �ٽ� �Է����ּ���."<<endl;
			continue;
		}
		for (int i=0; i<13; i++) // �� ������(13��°)�� NULL ���ڸ� ������ ��ȭ��ȣ �迭�� ��ҵ��� 0~9 ������ ���� ���� - ���� Ȯ���Ͽ� ����ó���Ѵ�.
		{
			if (i == 12)
			{
				if (m_Address[m_AddNum].strPhone1[12] == NULL ) // ���� ��ȭ��ȣ (10�ڸ���)�� ��츦 ����Ͽ�, �ι��ڰ� �ϳ� ���� �������� �����Ͽ� ����ó���Ѵ�.
				{
					m_error = false;
					break;
				}
			}
			if ( (m_Address[m_AddNum].strPhone1[i] < '0' || '9' < m_Address[m_AddNum].strPhone1[i]) && ( m_Address[m_AddNum].strPhone1[i] != '-'))
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

		break; // ���������� �ԷµǾ����� �ݺ����� �����Ѵ�.
	}
	while(1)
	{
		cout << "�Է��Ͻ� ��ȭ��ȣ�� ������ �����ϼ���" << endl << "1. �޴���   2. ȸ��   3. ��   4. �ѽ�   5. ����";
		cin >> m_Address[m_AddNum].phoneGroup2;
		if ( cin.fail() == true) // �Է��� �߸��Ǿ��� ��� �ٽ� �Է¹޴´�.
		{
			cout << "�Է� �����Դϴ�. Ȯ�� �� �ٽ� �Է����ּ���."<<endl;
			continue;
		}
		if (m_Address[m_AddNum].phoneGroup2 < '1' || '5' < m_Address[m_AddNum].phoneGroup2)
		{
			cout << "1���� 5������ ���ڸ��� �Է����ּ���."<<endl;
			continue;
		}
		break;
	}
	if (m_Address[m_AddNum].phoneGroup2 != '5')
	{
		while(1)
		{
			cin.clear(); // getline �Լ� ��뿡 ������ �־��� ���, �ݺ����� ���ѹݺ��� ���� ���� ������ û���Ѵ�.
			fflush(stdin); // �Է¹��۸� û���Ѵ�.

			cout << "��ȭ��ȣ : ";
			cin.getline (m_Address[m_AddNum].strPhone2, sizeof(m_Address[m_AddNum].strPhone2)); // ��ȭ��ȣ�� getline �Լ��� ���� �Է¹޴´�.

			if ( cin.fail() == true) // �Է��� �߸��Ǿ��� ��� �ٽ� �Է¹޴´�.
			{
				cout << "�Է� �����Դϴ�. Ȯ�� �� �ٽ� �Է����ּ���."<<endl;
				continue;
			}
			for (int i=0; i<13; i++) // �� ������(13��°)�� NULL ���ڸ� ������ ��ȭ��ȣ �迭�� ��ҵ��� 0~9 ������ ���� ���� - ���� Ȯ���Ͽ� ����ó���Ѵ�.
			{
				if (i == 12)
				{
					if (m_Address[m_AddNum].strPhone2[12] == NULL ) // ���� ��ȭ��ȣ (10�ڸ���)�� ��츦 ����Ͽ�, �ι��ڰ� �ϳ� ���� �������� �����Ͽ� ����ó���Ѵ�.
					{
						m_error = false;
						break;
					}
				}
				if ( (m_Address[m_AddNum].strPhone2[i] < '0' || '9' < m_Address[m_AddNum].strPhone2[i]) && ( m_Address[m_AddNum].strPhone2[i] != '-'))
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

			break; // ���������� �ԷµǾ����� �ݺ����� �����Ѵ�.
		}
	}
	cout << "�̸��� : "; 	cin >> m_Address[m_AddNum].strEmail;	// �̸��� �Է¹޴´�
	cout << "�� ����� �Ϸ��Ͽ����ϴ�."<<endl;
	ofstream fout;
	fout.open("addressBook.txt",ios::app);
	fout<<m_Address[m_AddNum].strName<<setw(40)<<
		m_Address[m_AddNum].strEmail<<setw(20)<<
		m_Address[m_AddNum].strPhone1<<setw(20)<<
		m_Address[m_AddNum].strPhone2<<setw(20)<<
		m_Address[m_AddNum].phoneGroup1<<setw(20)<<
		m_Address[m_AddNum].phoneGroup2<<endl;
	m_AddNum++; // �� ����� �Ϸ�Ǹ� ���� ���� �ǹ��ϴ� m_CNum ������ ���� �����Ͽ� ���� ���� �þ���� �����Ѵ�.
	m_Address = (Address* ) realloc(m_Address,sizeof(Address) * (m_AddNum+1));  // �����Ҵ��� ���� Client �迭�� ������Ų��.
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
	cout << "--------------------[�� ��ü ��ȸ]--------------------"<<endl;
	cout << left << setw(16) << "�̸�" << " | "
		<< setw(10) << "��ȭ��ȣ" << " | "
		<< setw(6) << "��ȭ��ȣ" << " | "
		<< setw(20) << "�̸���" << endl;
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
		cout << "1. �ּҷ� ���"<<endl;
		cout << "2. ��ü ��ȸ"<<endl;
		cout << "3. ���α׷� ����"<<endl;
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
		case 3 : end = true; break;
		default :	cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �����ϼ���." << endl;	system("pause");	break;
		}
		if (end == true)
			break;
	}
	free(m_Address);
}