#include "HashTable_LinearProbing.h"

//Constructor / Destructor ==============
template<class Type>
inline HashTable_LinearProbing<Type>::HashTable_LinearProbing(unsigned int size, float OverSizePercentMax, float ResizeCapacity)
{
	ht_size = 0;
	capacity = size;

	if (OverSizePercentMax < 0.95)
		MaxOverSizePercent = OverSizePercentMax;
	else
		MaxOverSizePercent = 0.95;
	UpgradeMultiplier = ResizeCapacity;
	arr = new CellNode[capacity]();
}

template<class Type>
HashTable_LinearProbing<Type>::~HashTable_LinearProbing()
{
		delete[] arr;
}

//Insert  =====================
template<class Type>
void HashTable_LinearProbing<Type>::insert(string& key, Type value)
{
	unsigned int idkey = hash_function(key);
	auto temp = idkey;
	while (idkey < capacity)
	{
		if (!(arr[idkey].isWritten))
		{
			arr[idkey].key = key;
			arr[idkey].value = value;
			arr[idkey].isWritten = true;
			++ht_size;
			UpgradeTable();
			return;
		}
		++idkey;
	}
	idkey = 0;

	while (idkey < temp)
	{
		if (!(arr[idkey].isWritten))
		{
			arr[idkey].key = key;
			arr[idkey].value = value;
			arr[idkey].isWritten = true;
			++ht_size;
			UpgradeTable();
			return;
		}
		++idkey;
	}
	cout << "\n\nERROR_It Cant be There";


}

template<class Type>
void HashTable_LinearProbing<Type>::insert(string key, Type value)
{
	unsigned int idkey = hash_function(key);
	auto temp = idkey;
	while (idkey < capacity)
	{
		if (!(arr[idkey].isWritten))
		{
			arr[idkey].key = key;
			arr[idkey].value = value;
			arr[idkey].isWritten = true;
			++ht_size;
			UpgradeTable();
			return;
		}
		++idkey;
	}
	idkey = 0;

	while (idkey < temp)
	{
		if (!(arr[idkey].isWritten))
		{
			arr[idkey].key = key;
			arr[idkey].value = value;
			arr[idkey].isWritten = true;
			++ht_size;
			UpgradeTable();
			return;
		}
		++idkey;
	}
	cout << "\n\nERROR_It Cant be There";
}

//Hash Function ===============
template<class Type>
inline unsigned int HashTable_LinearProbing<Type>::hash_function(string& key)
{
	int result = 0;
	for (int i = 0; i < key.size(); ++i)
	{
		result += (int)key[i];
	}
	return result % capacity;
}

//Upgrade Table
template<class Type>
void HashTable_LinearProbing<Type>::UpgradeTable()
{
	if (((float)ht_size / (float)capacity) < MaxOverSizePercent)
		return;
	capacity = capacity * UpgradeMultiplier;
	ht_size = 0;
	auto oldArr = arr;
	arr = new CellNode[capacity];
	for (int i = 0; i < capacity; ++i)
	{
		if (oldArr[i].isWritten == false)
			continue;
		//Insert
		{
			unsigned int idkey = hash_function(oldArr[i].key);
			auto temp = idkey;
			while (idkey < capacity)
			{
				if (!(arr[idkey].isWritten))
				{
					arr[idkey].key = oldArr[i].key;
					arr[idkey].value = oldArr[i].value;
					arr[idkey].isWritten = true;
					++ht_size;
					return;
				}
				++idkey;
			}
			idkey = 0;

			while (idkey < temp)
			{
				if (!(arr[idkey].isWritten))
				{
					arr[idkey].key = oldArr[i].key;
					arr[idkey].value = oldArr[i].value;
					arr[idkey].isWritten = true;
					++ht_size;
					return;
				}
				++idkey;
			}
			cout << "\n\nERROR_It Cant be There";
		} 
	}
	cout << "\nUpgrade Complete!\n";
}

//Erase ======================
template<class Type>
void HashTable_LinearProbing<Type>::erase(string& key)
{
	unsigned int idkey = hash_function(key);
	auto temp = idkey;
	while (idkey < capacity)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key) 
			{
				arr[idkey].isWritten = false;
				return;
			}
		++idkey;
	}
	idkey = 0;
	while (idkey < temp)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				arr[idkey].isWritten = false;
				return;
			}
		++idkey;
	}
	return;
}
template<class Type>
void HashTable_LinearProbing<Type>::erase(string key)
{
	unsigned int idkey = hash_function(key);
	auto temp = idkey;
	while (idkey < capacity)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				arr[idkey].isWritten = false;
				return;
			}
		++idkey;
	}
	idkey = 0;
	while (idkey < temp)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				arr[idkey].isWritten = false;
				return;
			}
		++idkey;
	}
	return;
}

//Clear ======================
template<class Type>
void HashTable_LinearProbing<Type>::clear()
{
		delete[] arr;
}

//Empty ======================
template<class Type>
bool HashTable_LinearProbing<Type>::empty()
{
	return ht_size == 0;
}

//Print =======================
template<class Type>
void HashTable_LinearProbing<Type>::printHT_Info()
{
	cout << "Full Hash Table Information: \n ";
	cout << " - Number of values : " << ht_size << "\n";
	cout << " - Capacity : " << capacity << "\n";
	cout << " - Oversize max capacity percent: " << MaxOverSizePercent;
	cout << " - Resize Multiplier : " << UpgradeMultiplier << "\n";
}

//Foreach =====================
template<class Type>
void HashTable_LinearProbing<Type>::foreach(void(*action)(Type& val))
{
	for (int i = 0; i < capacity; ++i)
		if (arr[i].isWritten)
			action(arr[i].value);
}

//Get element
template<class Type>
inline Type& HashTable_LinearProbing<Type>::get(string& key)
{
	unsigned int idkey = hash_function(key);
	auto temp = idkey;
	while (idkey < capacity)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				return arr[idkey].value;
			}
		++idkey;
	}
	idkey = 0;
	while (idkey < temp)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				return arr[idkey].value;
			}
		++idkey;
	}
	throw HT_ItemAcñess_Error(key);
}
template<class Type>
inline Type& HashTable_LinearProbing<Type>::get(string key)
{
	unsigned int idkey = hash_function(key);
	auto temp = idkey;
	while (idkey < capacity)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				return arr[idkey].value;
			}
		++idkey;
	}
	idkey = 0;
	while (idkey < temp)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				return arr[idkey].value;
			}
		++idkey;
	}
	throw HT_ItemAcñess_Error(key);
}

template<class Type>
Type& HashTable_LinearProbing<Type>::operator[](string& key)
{
	unsigned int idkey = hash_function(key);
	auto temp = idkey;
	while (idkey < capacity)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				return arr[idkey].value;
			}
		++idkey;
	}
	idkey = 0;
	while (idkey < temp)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				return arr[idkey].value;
			}
		++idkey;
	}
	throw HT_ItemAcñess_Error(key);
}

template<class Type>
Type& HashTable_LinearProbing<Type>::operator[](string key)
{
	unsigned int idkey = hash_function(key);
	auto temp = idkey;
	while (idkey < capacity)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				return arr[idkey].value;
			}
		++idkey;
	}
	idkey = 0;
	while (idkey < temp)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				return arr[idkey].value;
			}
		++idkey;
	}
	throw HT_ItemAcñess_Error(key);
}

//Get Reference
template<class Type>
inline Type* HashTable_LinearProbing<Type>::get_r(string& key)
{
	unsigned int idkey = hash_function(key);
	auto temp = idkey;
	while (idkey < capacity)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				return &(arr[idkey].value);
			}
		++idkey;
	}
	idkey = 0;
	while (idkey < temp)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				return &(arr[idkey].value);
			}
		++idkey;
	}
	throw HT_ItemAcñess_Error(key);
}

template<class Type>
inline Type* HashTable_LinearProbing<Type>::get_r(string key)
{
	unsigned int idkey = hash_function(key);
	auto temp = idkey;
	while (idkey < capacity)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				return &(arr[idkey].value);
			}
		++idkey;
	}
	idkey = 0;
	while (idkey < temp)
	{
		if (arr[idkey].isWritten)
			if (arr[idkey].key == key)
			{
				return &(arr[idkey].value);
			}
		++idkey;
	}
	throw HT_ItemAcñess_Error(key);
}

