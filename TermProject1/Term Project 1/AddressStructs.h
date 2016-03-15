#pragma once
#include <iomanip>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct Phone{
	char strPhone[14];	// ��ȭ��ȣ
	int phoneGroup;		// ��ȭ��ȣ ����
}Phone;

typedef struct Address{
	char strName[15];	//�̸�
	vector<Phone> phone; //��ȭ��ȣ vector �����̳�
	int addNum;			//��ȭ��ȣ ����
	char strEmail[40];	 //E-Mail
	int groupID;		//�׷�
}Address; // �ּҷ��� ������ ����ü�� �����Ѵ�

typedef struct Message{
	char strPhone[14];//��ȭ��ȣ
	char strDate[20]; //�߼�����
	string strText;//�޽��� ����
}Message; // �޽����� ������ ������ ����ü