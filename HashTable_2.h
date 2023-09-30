#pragma once
#include <string>
#include <list>
#include <cmath>
#include <exception>
#include <iostream>

using namespace std;

template <class Type>
class HashTable
{
private:
	class HT_ItemAc�ess_Error : public exception
	{
		string message;
	public:
		HT_ItemAc�ess_Error(string& key)
		{
			message = "No choosed key found : " + key;
		}
		string& what()
		{
			return message;
		}
	};

public:
	HashTable(long size, float OverSizePercentMax, float ResizeCapacity);
	void insert(string& key, Type value);
	bool erase(string& key);
	void clear();
	bool empty();
	void printHT();
	inline Type& Get(string& key);//���� ������� �� ������ ����������� ���������� HT_ItemAcess_Error
	Type& operator[](string& key);//c�. ����
	inline Type* get_r(string key);//���������� ��������� �� ����������� ������� (nullptr ���� �� ������). �� ����������� ����������


private:

	class CellNode
	{
	public:
		CellNode(string& k, Type val)
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

	unsigned long hash_function(string& key);

	//������
	float OverSizePercentMax;
	
	float ResizeMultiplier;

	CellNode** arr;								//��������� �� ���. ������ ����� (�������)

	long capacity;								//������� ����� ��� ������

	long ht_size;
};
