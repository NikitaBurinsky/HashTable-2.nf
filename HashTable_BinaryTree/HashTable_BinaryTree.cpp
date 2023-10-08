#pragma once
#include "HashTable_BinaryTree.h"
#include <vector>
#include <ctime>

template <class Type>
HashTable_BinaryTree<Type>::HashTable_BinaryTree(unsigned int capac, float MaxOverPerc, float UpgadeTableMultipl)
{
	capacity = capac;
	maxOverflowPercent = MaxOverPerc;
	ht_size = 0;
	arr = new BT_Node * [capacity]();
	for (int i = 0; i < capacity; ++i)
		arr[i] = nullptr;

	UpgradeTableMultiplier = UpgadeTableMultipl;
}

template <class Type>
unsigned int HashTable_BinaryTree<Type>::hash_function(long key)
{
	unsigned int result = 0;
	result = key % capacity;
	return result;
}

//Upgrade Table ===============
template <class Type>
void HashTable_BinaryTree<Type>::UpgradeTable()
{
	if (((float)ht_size / (float)capacity) < maxOverflowPercent)
		return;

	unsigned int oldCapacity = capacity;
	capacity = capacity * UpgradeTableMultiplier;

	unsigned int oldSize = ht_size;
	ht_size = 0;

	BT_Node** oldArr = arr;
	arr = new BT_Node * [capacity];
	for (int i = 0; i < capacity; ++i)
		arr[i] = nullptr;


	for (int i = 0; i < oldCapacity; ++i)
		UpgradeTableRecursion(oldArr[i]);

	if (oldSize == ht_size)
		cout << "\n\n///Upgrade Complete!///\n\n";
	else
		cout << "\n\n///Upgrade Failed///\n\n";

	delete[] oldArr;
}


template <class Type>
void HashTable_BinaryTree<Type>::UpgradeTableRecursion(BT_Node* node)
{
	if (node == nullptr)
		return;
	
	unsigned int idkey = hash_function(node->key);

	if (arr[idkey] == nullptr)
	{
		arr[idkey] = new BT_Node(node->key, node->value);
		++ht_size;
	}
	if (arr[idkey] != nullptr)
	{
		findNewNodePlace(arr[idkey], node->key, node->value);
	}
	
	UpgradeTableRecursion(node->right);
	UpgradeTableRecursion(node->left);
	return;

	
}


//Insert ===================
template <class Type>
void HashTable_BinaryTree<Type>::insert(long key, Type val)
{
	unsigned int idkey = hash_function(key);
	
	if (arr[idkey] == nullptr)
	{
		arr[idkey] = new BT_Node(key, val);
		++ht_size;
		UpgradeTable();
		return;
	}
	if (arr[idkey] != nullptr)
	{
		findNewNodePlace(arr[idkey], key, val);
		UpgradeTable();
		return;
	}
	cout << "\\\\\nNe dolzno doiti suda///\n";
}

template <class Type>
void HashTable_BinaryTree<Type>::insert(long key, Type& val)
{
	unsigned int idkey = hash_function(key);

	if (arr[idkey] == nullptr)
	{
		arr[idkey] = new BT_Node(key, val);
		++ht_size;
		UpgradeTable();
		return;
	}
	if (arr[idkey] != nullptr)
	{
		findNewNodePlace(arr[idkey], key, val);
		UpgradeTable();
		return;
	}
	cout << "\\\\\nNe dolzno doiti suda///\n";
}
template <class Type>
void HashTable_BinaryTree<Type>::findNewNodePlace(BT_Node* node, long& key, Type& val)
{
	if (node->key == key)
	{
		node->value = val;
		return;
	}
	if (key > node->key)
	{
		if (node->left == nullptr)
		{
			node->left = new BT_Node(key, val);
			++ht_size;
			UpgradeTable();
			return;
		}
		else
		{
			findNewNodePlace(node->left, key, val);
			return;
		}
	}
	if (key < node->key)
	{
		if (node->right == nullptr)
		{
			node->right = new BT_Node(key, val);
			++ht_size;
			UpgradeTable();
			return;
		}
		else
		{
			findNewNodePlace(node->right, key, val);
			return;
		}
	}
}

//CLEAR
template<class Type>
void HashTable_BinaryTree<Type>::clear()
{
	for (int i = 0; i < capacity; ++i)
	{
		if (arr[i] == nullptr)
			continue;
		ClearRecursion(arr[i]);
	}
	ht_size = 0;
	delete[] arr;
	capacity = 4;
	arr = new BT_Node * [capacity]();
}

template<class Type>
void HashTable_BinaryTree<Type>::ClearRecursion(BT_Node* node)
{
	if (node == nullptr)
		return;
	ClearRecursion(node->right);
	ClearRecursion(node->left);
	delete node;
}

//Erase ====================
template <class Type>
void HashTable_BinaryTree<Type>::erase(long key)
{
	/*
	Осужествляется поиск удаляемого элемента
	
	Сохраняется адрес его правого (меньшего) поддерева

	Ищется наименьший элемент его большего поддерева и в его правый некст сохраняется сохраненный адрес

	Ищется родительский элемент удаляемого и сохраняется адрес большего удаляемого

	Удаляется нужный элемент 

	В родителский элемент записывается сохраненный адрес поддерева
	*/


	unsigned int idkey = hash_function(key);
	if (arr[idkey] == nullptr)
		return;
	BT_Node* rightSubTree;
	BT_Node* iter = arr[idkey];
	while (iter != nullptr)
	{
		if (key > iter->key)
		{
			iter = iter->left;
			continue;
		}
		else if (key < iter->key)
		{
			iter = iter->right;
			continue;
		}
		//Если нужный ключ равен текущему
		if(iter->key == key)
		if (iter->left == nullptr)
		{
			iter->left = iter->right;
			break;
		}
		rightSubTree = iter->right;


		BT_Node* minimalLeft = findMinimalLeftSubTreeValue(iter->left);
		minimalLeft->right = rightSubTree;
		break;
	}

	if (iter == nullptr)
		return;


	//Второй поиск удаляемого элемента
	iter = arr[idkey];
	while ((iter->left != nullptr) && (iter->right != nullptr))
	{
		if (iter->left->key == key)
		{
			rightSubTree = iter->left->right;
			delete (iter->left);
			iter->left = rightSubTree;
			break;
		}
		if (iter->right->key == key)
		{
			rightSubTree = iter->right->right;
			delete (iter->right);
			iter->right = rightSubTree;
			break;
		}


		if (key > iter->key)
		{
			iter = iter->left;
			continue;
		}
		else if (key < iter->key)
		{
			iter = iter->right;
			continue;
		}
	}
	
	cout << "\nErase Complete\n";


}

//FOREACH ==================
template<class Type>
void HashTable_BinaryTree<Type>::foreachRecursion(BT_Node* node, void(*action)(Type& val))
{
	if (node == nullptr)
		return;
	action(node->value);
	foreachRecursion(node->right, action);
	foreachRecursion(node->left, action);
	return;
}

template <class Type>
void HashTable_BinaryTree<Type>::foreach(void(*action)(Type& val))
{
	for (int i = 0; 0 < capacity; ++i)
		foreachRecursion(arr[i], action);

	return;
}

//GET ELEMENT ===============
template <class Type>
Type& HashTable_BinaryTree<Type>::get(long key)
{

	unsigned int idkey = hash_function(key);
	BT_Node* iter = arr[idkey];
	while (iter != nullptr)
	{
		if (iter->key == key)
		{
			return iter->value;
		}
		if (key > iter->key)
		{
			iter = iter->left;
			continue;
		}
		iter = iter->right;
	}
	throw HT_ItemAcсess_Error(key);

}

template <class Type>
Type& HashTable_BinaryTree<Type>::operator[](long key)
{

	unsigned int idkey = hash_function(key);
	BT_Node* iter = arr[idkey];
	while (iter != nullptr)
	{
		if (iter->key == key)
		{
			return iter->value;
		}
		if (key > iter->key)
		{
			iter = iter->left;
			continue;
		}
		iter = iter->right;
	}
	throw HT_ItemAcсess_Error(key);

}

template <class Type>
Type* HashTable_BinaryTree<Type>::get_r(long key)
{
	unsigned int idkey = hash_function(key);
	BT_Node* iter = arr[idkey];
	while (iter != nullptr)
	{
		if (iter->key == key)
		{
			return iter->value;
		}
		if (key > iter->key)
		{
			iter = iter->left;
			continue;
		}
		iter = iter->right;
	}
	return nullptr;
}

//EMPTY ============
template <class Type>
bool HashTable_BinaryTree<Type>::empty()
{
	return ht_size == 0;
}
// PRINT =====================
template <class Type>
void HashTable_BinaryTree<Type>::printHT()
{
	for (int i = 0; i < capacity; ++i)
	{
		PrintRecursion(arr[i]);
		cout << "\n";
	}
		

	return;

}
template <class Type>
void HashTable_BinaryTree<Type>::printHT_Info()
{
	cout << "\n\nHT Type : Binary Tree";
	cout << "\nCapacity : " << capacity;
	cout << "\nSize : " << ht_size;
}

template <class Type>
void HashTable_BinaryTree<Type>::PrintRecursion(BT_Node* node)
{
	if (node == nullptr)
		return;
	cout << "(key: " << node->key << " / val: " << node->value << ")" << ",  ";
	PrintRecursion(node->left);
	PrintRecursion(node->right);
	return;
}