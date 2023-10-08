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

	inline Type& get(string& key);//Если элемент не найдет выбрасывают исключение HT_ItemAcess_Error
	inline Type& get(string key);//Если элемент не найдет выбрасывают исключение HT_ItemAcess_Error
	Type& operator[](string& key);//cм. выше
	Type& operator[](string key);

	inline Type* get_r(string& key);//Возвращает указатель на необходимый элемент (nullptr если не найден). Не выбрасывает исключений
	inline Type* get_r(string key);//Возвращает указатель на необходимый элемент (nullptr если не найден). Не выбрасывает исключений


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

	//Данные
	float OverSizePercentMax;
	
	float ResizeMultiplier;

	CellNode** arr;								//Указатель на дин. массив ячеек (таблицу)

	long capacity;								//Занятое место под массив

	long ht_size;
};