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
	class HT_ItemAcсess_Error : public exception
	{
		string message;
	public:
		HT_ItemAcсess_Error(string& key)
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
	inline Type& Get(string& key);//Если элемент не найдет выбрасывают исключение HT_ItemAcess_Error
	Type& operator[](string& key);//cм. выше
	inline Type* get_r(string key);//Возвращает указатель на необходимый элемент (nullptr если не найден). Не выбрасывает исключений


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

	//Данные
	float OverSizePercentMax;
	
	float ResizeMultiplier;

	CellNode** arr;								//Указатель на дин. массив ячеек (таблицу)

	long capacity;								//Занятое место под массив

	long ht_size;
};
