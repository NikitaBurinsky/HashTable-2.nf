#include "HashTable_2.h"

template<class Type>
inline HashTable<Type>::HashTable(long size, float SizePercentMax, float ResizeCapacity)
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
void HashTable<Type>::insert(string& key, Type value)
{
	long ik = hash_function(key);
	if (arr[ik] == nullptr)
	{
		string& x = key;
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
		string& x = key;
		iter->next = new CellNode(x, value);
		++ht_size;
		RecalculateSize();
}

template<class Type>
bool HashTable<Type>::erase(string& key) //True если элемент существовал и был удален
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
void HashTable<Type>::clear() 
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

template<class Type>
bool HashTable<Type>::empty()
{
	return ht_size == 0;
}

template<class Type>
void HashTable<Type>::printHT()
{
	cout << "Full Hash Table Information: \n ";
	cout << " - Number of values : " << ht_size << "\n";
	cout << " - Capacity (Except collisions) : " << capacity << "\n";
	cout << " - Oversize max capacity percent: " << OverSizePercentMax << "\n";
	cout << " - Resize Multiplier : " << ResizeMultiplier << "\n";


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
inline Type& HashTable<Type>::Get(string& key)
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
Type& HashTable<Type>::operator[](string& key)
{
	return Get(key);
}

template<class Type>
inline Type* HashTable<Type>::get_r(string key)
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
inline bool HashTable<Type>::RecalculateSize()
{
	if (((float)ht_size / (float)capacity) > OverSizePercentMax)
	{
		UpgradeTable();
		return true;
	}
	return false;
}



template<class Type>
void HashTable<Type>::UpgradeTable()
{
	long oldCapacity = capacity;
	capacity = capacity * ResizeMultiplier;

	long oldHt_size = ht_size;
	ht_size = 0;

	CellNode** oldArr = arr;

	arr = new CellNode *[capacity]();

	CellNode* iter;
	for (int i = 0; i < oldCapacity; ++i)
	{
		if (oldArr[i] == nullptr)
			continue;

		iter = oldArr[i];


		while (iter != nullptr)
		{
			insert(iter->key, iter->value);
				iter = iter->next;
		}
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
unsigned long HashTable<Type>::hash_function(string& key)
{
	int result = 0;
	for (int i = 0; i < key.size(); ++i)
	{
		result += (int)key[i];
	}
	return result % capacity;
}