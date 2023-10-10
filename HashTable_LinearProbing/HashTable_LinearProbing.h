#pragma once
#include <iostream>
#include <string>
#include "HashTableException.h"

using namespace std;

template <class Type>
class HashTable_LinearProbing
{
public:
	HashTable_LinearProbing(unsigned int size, float OverSizePercentMax = 0.8, float ResizeCapacity = 2);
	~HashTable_LinearProbing();


	//Interfaces
	void insert(string& key, Type value);
	void insert(string key, Type value);

	void erase(string& key);
	void erase(string key);

	void clear();
	bool empty();

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
		inline CellNode()
		{
			isWritten = false;
		}
		bool isWritten;
		string key;
		Type value;
	};


	CellNode* arr;

	unsigned int capacity;

	unsigned int ht_size;

	float MaxOverSizePercent;

	float UpgradeMultiplier;
	
	//Functions

	unsigned int hash_function(string& key);

	void UpgradeTable();

};

