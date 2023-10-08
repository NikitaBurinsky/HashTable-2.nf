#pragma once
#include "HashTable_ForwardList.h"

template<class Type>
inline HashTable_ForwardList<Type>::HashTable_ForwardList(long size, float SizePercentMax, float ResizeCapacity)
{
	capacity = size;
	OverSizePercentMax = SizePercentMax;
	ResizeMultiplier = ResizeCapacity;
	ht_size = 0;
	arr = new CellNode*[capacity];
	for (int i = 0; i < capacity; ++i)
		arr[i] = nullptr;
}

template<class Type>
HashTable_ForwardList<Type>::~HashTable_ForwardList()
{
	clear();
}

//INSERT ===================
template<class Type>
void HashTable_ForwardList<Type>::insert(string& key, Type value)
{
	long ik = hash_function(key);
	if (arr[ik] == nullptr)
	{
		Type& x = key;
		arr[ik] = new CellNode(x, value);
		++ht_size;
		RecalculateSize();
		return;
	}

		CellNode* iter = arr[ik];
		while (iter->next != nullptr)
		{
			if (key == iter->key)
			{
				iter->value = value;
				return;
			}
			iter = iter->next;
		}
		Type& x = key;
		iter->next = new CellNode(x, value);
		++ht_size;
		RecalculateSize();
}

template<class Type>
void HashTable_ForwardList<Type>::insert(string key, Type value)
{
	long ik = hash_function(key);
	if (arr[ik] == nullptr)
	{
		Type& x = key;
		arr[ik] = new CellNode(x, value);
		++ht_size;
		RecalculateSize();
		return;
	}

	CellNode* iter = arr[ik];
	while (iter->next != nullptr)
	{
		if (key == iter->key)
		{
			iter->value = value;
			return;
		}
		iter = iter->next;
	}
	Type& x = key;
	iter->next = new CellNode(x, value);
	++ht_size;
	RecalculateSize();
}

//ERASE =============
template<class Type>
bool HashTable_ForwardList<Type>::erase(string& key) //True если элемент существовал и был удален
{
	long ik = hash_function(key);
	if (arr[ik] == nullptr)
		return false;
	if (arr[ik]->key == key && arr[ik]->next == nullptr)
	{
		delete arr[ik];
		arr[ik] = nullptr;
		--ht_size;
	}


	CellNode* iter = arr[ik];
	while (iter->next != nullptr)
	{
		if (iter->next->key == key)
		{
			CellNode* third = iter->next->next;
			delete (iter->next);
			iter->next = third;
			--ht_size;
			return true;
		}
		iter = iter->next;
	}
	return false;
}

template<class Type>
bool HashTable_ForwardList<Type>::erase(string key)
{
	long ik = hash_function(key);
	if (arr[ik] == nullptr)
		return false;
	if (arr[ik]->key == key && arr[ik]->next == nullptr)
	{
		delete arr[ik];
		arr[ik] = nullptr;
		--ht_size;
	}


	CellNode* iter = arr[ik];
	while (iter->next != nullptr)
	{
		if (iter->next->key == key)
		{
			CellNode* third = iter->next->next;
			delete (iter->next);
			iter->next = third;
			--ht_size;
			return true;
		}
		iter = iter->next;
	}
	return false;
}

//CLEAR ==============
template<class Type>
void HashTable_ForwardList<Type>::clear() 
{
	CellNode* iter;
	CellNode* second;
	for (int i = 0; i < capacity; ++i)
	{
		iter = &arr[i];
		if (arr[i] == nullptr)
			continue;
		while (iter->next != nullptr)
		{
			second = iter->next;
			iter->next = iter->next->next;
			delete second;
		}
		delete iter;
		arr[i] = nullptr;
	}
	ht_size = 0;
	return;
}

//EMPTY ================
template<class Type>
bool HashTable_ForwardList<Type>::empty()
{
	return (ht_size == 0);
}

//PRINT ===================
template<class Type>
void HashTable_ForwardList<Type>::printHT()
{
	cout << endl;
	CellNode* iter;
	for (int i = 0; i < capacity; ++i)
	{
		iter = arr[i];
		if (arr[i] == nullptr)
		{
			cout << "\t - Null\n\n";
			continue;
		}

		while (iter != nullptr)
		{
			cout << "value: " << iter->value << "(key: " << iter->key + ")" << " | ";
			iter = iter->next;
		}
		cout << endl << endl;
	}
}

template<class Type>
void HashTable_ForwardList<Type>::printHT_Info()
{
	cout << "Full Hash Table Information: \n ";
	cout << " - Number of values : " << ht_size << "\n";
	cout << " - Capacity (Except collisions) : " << capacity << "\n";
	cout << " - Oversize max capacity percent: " << OverSizePercentMax << "\n";
	cout << " - Resize Multiplier : " << ResizeMultiplier << "\n";
}

template<class Type>
void HashTable_ForwardList<Type>::foreach(void(*action)(Type& val))
{
	CellNode* iter;
	for (int i = 0; i < capacity; ++i)
	{
		iter = arr[i];
		if (arr[i] != nullptr)
		while (iter != nullptr)
		{
			action(iter->value);
			iter = iter->next;
		}
	}
}

//GET ELEMENT =======================
template<class Type>
inline Type& HashTable_ForwardList<Type>::get(string& key)
{
	long ik = hash_function(key);
	
	if (arr[ik] == nullptr)
	{
		cout << "\nItem was not found\n";
		throw HT_ItemAcсess_Error(key);
	}

	CellNode* iter = arr[ik];
	while (iter != nullptr)
	{
		if (iter->key == key)
			return iter->value;

		iter = iter->next;
	}
	cout << "\nItem was not found\n";
	throw HT_ItemAcсess_Error(key);
}

template<class Type>
inline Type& HashTable_ForwardList<Type>::get(string key)
{
	long ik = hash_function(key);

	if (arr[ik] == nullptr)
	{
		cout << "\nItem was not found\n";
		throw HT_ItemAcсess_Error(key);
	}

	CellNode* iter = arr[ik];
	while (iter != nullptr)
	{
		if (iter->key == key)
			return iter->value;

		iter = iter->next;
	}
	cout << "\nItem was not found\n";
	throw HT_ItemAcсess_Error(key);
}

template<class Type>
Type& HashTable_ForwardList<Type>::operator[](string& key)
{
	return get(key);
}

template<class Type>
Type& HashTable_ForwardList<Type>::operator[](string key)
{
	return get(key);
}

template<class Type>
inline Type* HashTable_ForwardList<Type>::get_r(string& key)
{
	long ik = hash_function(key);

	if (arr[ik] == nullptr)
	{
		cout << "\nItem was not found\n";
		return nullptr;
	}

	CellNode* iter = arr[ik];
	while (iter != nullptr)
	{
		if (iter->key == key)
			return &(iter->value);

		iter = iter->next;
	}
	cout << "\nItem was not found\n";
	return nullptr;

}

template<class Type>
inline Type* HashTable_ForwardList<Type>::get_r(string key)
{
	long ik = hash_function(key);

	if (arr[ik] == nullptr)
	{
		cout << "\nItem was not found\n";
		return nullptr;
	}

	CellNode* iter = arr[ik];
	while (iter != nullptr)
	{
		if (iter->key == key)
			return &(iter->value);

		iter = iter->next;
	}
	cout << "\nItem was not found\n";
	return nullptr;

}

template<class Type>
inline bool HashTable_ForwardList<Type>::RecalculateSize()
{
	if (((float)ht_size / (float)capacity) > OverSizePercentMax)
	{
		UpgradeTable();
		return true;
	}
	return false;
}

template<class Type>
void HashTable_ForwardList<Type>::UpgradeTable()
{
	long oldCapacity = capacity;
	capacity = capacity * ResizeMultiplier;

	long oldHt_size = ht_size;
	ht_size = 0;

	CellNode** oldArr = arr;

	arr = new CellNode *[capacity]();

	for (int i = 0; i < oldCapacity; ++i)
	{
		if (oldArr[i] == nullptr)
			continue;
		MoveFLtoNewTable(oldArr[i]);
	}


	delete oldArr;


	if (ht_size == oldHt_size)
	{
		cout << "\n/// Upgrade Complete ///\n";
		return;
	}
	cout << "\n/// Upgrade Failed ///\n";
	return;
}

template<class Type>
void HashTable_ForwardList<Type>::MoveFLtoNewTable(CellNode* node)
{
	if (node == nullptr)
		return;

	unsigned int idkey = hash_function(node->key);
	if (arr[idkey] == nullptr)
		arr[idkey] = node;
	CellNode* iter = arr[idkey];
	while (iter->next != nullptr)
	{
		iter = iter->next;
	}
	iter->next = node;
	++ht_size;
	MoveFLtoNewTable(node->next);
}

template<class Type>
unsigned long HashTable_ForwardList<Type>::hash_function(string& key)
{
	int result = 0;
	for (int i = 0; i < key.size(); ++i)
	{
		result += (int)key[i];
	}
	return 1;//result % capacity;
}