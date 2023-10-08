#pragma once
#include <string>
#include <iostream>
#include "HashTableException.h"

using namespace std;

template <class Type>
class HashTable_BinaryTree //Key is only LONG
{
public:

	HashTable_BinaryTree<Type>(unsigned int capac, float MaxOverPerc = 1.5, float UpgadeTableMultipl = 2); // unsigned int capacity, float MaxiamOverflowPercent, UpgradeTableMultiplier
	~HashTable_BinaryTree<Type>();

	//Interfaces
	void insert(long key, Type val);
	void insert(long key, Type& val);

	void erase(long key);
	
	void clear();
	bool empty();

	void printHT(); //For tests. Not recommended to use in a large HT's
	void printHT_Info();

	void foreach(void (*action)(Type& val));

	Type& get(long key);//���� ������� �� ������ ����������� ���������� HT_ItemAcess_Error
	Type& operator[](long key);//���� ������� �� ������ ����������� ���������� HT_ItemAcess_Error

	inline Type* get_r(long key);//���������� ��������� �� ����������� ������� (nullptr ���� �� ������). �� ����������� ����������

private:

	class BT_Node
	{
	public:
		BT_Node(long k, Type val)
		{
			key = k;
			value = val;
			right = nullptr;
			left = nullptr;
		}
		BT_Node()
		{
			key = 000000;
			right = nullptr;
			left = nullptr;
		}
		long key;
		Type value;
		BT_Node* right;
		BT_Node* left;

	};

	BT_Node** arr;
	unsigned int capacity;
	long ht_size;
	float maxOverflowPercent;
	float UpgradeTableMultiplier;

	virtual unsigned int hash_function(long key);
	// Upgrade Table
	void UpgradeTable();
	void UpgradeTableRecursion(BT_Node* node);

	//������� ��� �������
	void findNewNodePlace(BT_Node* node, long& key, Type& val);

	//������� ��� ��������
	inline BT_Node* findMinimalLeftSubTreeValue(BT_Node* node) 
	{
		while (node->right != nullptr)
			node = node->right;

		return node;
	}

	//������� ��� �������� �� ����

	void foreachRecursion(BT_Node* node, void(*action)(Type& val));

	//������� ��� ������ ����
	void PrintRecursion(BT_Node* node);

	//������� ��� Crear()
	void ClearRecursion(BT_Node* node);
};

