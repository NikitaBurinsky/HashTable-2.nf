#pragma once
#include <string>
#include <list>
#include <cmath>
#include <iostream>
#include "HashTableException.h"
using namespace std;

template <class Type>
class HashTable_ForwardList
{
public:
	HashTable_ForwardList(long size, float OverSizePercentMax = 1.5, float ResizeCapacity = 2);
	~HashTable_ForwardList();


	//Interfaces
	void insert(string& key, Type value);
	void insert(string key, Type value);

	bool erase(string& key);
	bool erase(string key);

	void clear();
	bool empty();

	void printHT(); //For tests. Not recommended to use in a large HT's
	void printHT_Info();

	void foreach(void (*action)(Type& val));

	inline Type& get(string& key);//���� ������� �� ������ ����������� ���������� HT_ItemAcess_Error
	inline Type& get(string key);//���� ������� �� ������ ����������� ���������� HT_ItemAcess_Error
	Type& operator[](string& key);//c�. ����
	Type& operator[](string key);

	inline Type* get_r(string& key);//���������� ��������� �� ����������� ������� (nullptr ���� �� ������). �� ����������� ����������
	inline Type* get_r(string key);//���������� ��������� �� ����������� ������� (nullptr ���� �� ������). �� ����������� ����������


private:

	class CellNode
	{
	public:
		CellNode(Type& k, Type val)
		{
			value = val;
			key = k;
			next = nullptr;
		}
		CellNode()
		{
			value = 0;
			next = nullptr;
		}
		Type value;
		string key;
		CellNode* next;
	};

	inline bool RecalculateSize();

	 void UpgradeTable();

	 void MoveFLtoNewTable(CellNode* node);
	
	virtual unsigned long hash_function(string& key);

	//������
	float OverSizePercentMax;
	
	float ResizeMultiplier;

	CellNode** arr;								//��������� �� ���. ������ ����� (�������)

	long capacity;								//������� ����� ��� ������

	long ht_size;
};