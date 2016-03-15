#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include "AddressStructs.h"
using namespace std;

static char* phoneGroupName[5] = {"����", "�޴���", "ȸ��", "��", "�ѽ�"};

class AddressBook{

private:
	AddressBook(); //AddressBook ������. �ؽ�Ʈ ������ �ҷ��ͼ� v_Address �����̳ʿ� ������ �� sorting�Ѵ�.
	~AddressBook(); //AddressBook �Ҹ���. v_Address �����̳��� ������ �ؽ�Ʈ ���Ͽ� ����Ѵ�.

	fstream file;	// ���� ����� ��ü

	vector<Address> v_Address; // �ּҷ��� ��� vector�� �����̳�.
	Address tempAdd;	// �ּҷ��� �ӽ÷� ��Ƶδ� ����ü.
	Phone tempPhone;	// ��ȭ��ȣ�� �ӽ÷� ��Ƶδ� ����ü.
	vector<Address>::iterator iter;	// �ּҷ� vector �����̳��� �ݺ���.
	bool m_error; // ����ó���� ���� bool�� ����.

public:
	void ShowAddress(vector<Address>::iterator iter); // v_Address �����̳ʿ��� �ݺ��� iter�� ����Ű�� ��带 ����ϴ� �Լ��̴�.
	
	void GetAddress(); // �ּҷ��� �Է��ϴ� void�� �Լ��̴�.

	void ReviseAddress(vector<Address>::iterator iter); // �Էµ� �ݺ��ڿ� ���� �ּҷ��� ������ �����ϴ� void(iterator)�� �Լ��̴�.(�̱���)


	vector<Address>::iterator AddressBook:: FindAddressByName(char* name); // ���� �̸��� ������ �̸��� ���� ����� �ݺ��ڸ� ��ȯ�ϴ� �Լ��̴�.
	void FindAddressByNameRenderer(); // FindAddressByName �Լ��� �����ϴ� Renderer �Լ�

	vector<Address>::iterator AddressBook:: FindAddressByPhone(char* phoneNum); // ���� ��ȭ��ȣ�� ������ ��ȭ��ȣ�� ���� ����� �ݺ��ڸ� ��ȯ�ϴ� �Լ��̴�.
	void FindAddressByPhoneRenderer(); // FindAddressByPhone �Լ��� �����ϴ� Renderer �Լ�

	void FindAddressByPhoneBNSearch(); // �Էµ� �̸��� ���� �ּҷ��� ������ ����ϴ� void(void)�� �Լ��̴�.

	void DeleteAddress(); // �Էµ� �ּҷ��� ������ �����ϴ� void(void)�� �Լ��̴�. (�̱���)

	void ShowAddressList(); // �Էµ� �ּҷ��� ������ ����Ʈ ���·� ����ϴ� void(void)�� �Լ��̴�.

	void ShowMessageList_Renderer();

	void SendSMSRenderer(char* phoneNum); // SMS class�� SendSMS �Լ��� ���ڸ� �����ϱ� ���� Renderer �Լ�.

	void ShowMessage(char* phoneNum);

public:
	static AddressBook& GetInstance()
	{
		static AddressBook MyAddress;
		return MyAddress;
	}
	void ShowMenu(); // �޴��� ����ϴ� �Լ��̴�.
};

#define address AddressBook::GetInstance()