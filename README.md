# HashTable-2.nf
Template classes have the ability to insert and delete elements by key, as well as receive an element by key. To solve the problem of collisions, the main methods
of processing are used: Collision chains, Binary trees.
The table automatically expands N times when the ratio "Number of elements/X" is reached,
with X and T being configurable parameters (X will mean the maximum number of elements in the table without collisions and with the maximum speed of access to the element)

Each class has a set of functions:
1. insert(key, value) - Adding an element (Template type) by key (string). For a binary tree, the key is of type long;
2. erase(key) - Deleting an element by key
3. get() & operator[] - Returns a reference to an element by key
4. get_r() - Returns a pointer to an element by key
5. clear() - Clearing the table
6. empty() - Returns true if the table is empty, otherwise false
7. print_Info() - Displays information about the table
8. foreach(void(*func)(Type& value)) - Uses the passed unary function for each element in the table

Parameters of the table constructor:
	HashTable_BinaryTree(unsigned int capacity, float MaxOverflowPercent, float UpgadeTableMultiplier)
	1. capacity: 
		The initial size of the table, the maximum number 
		elements in the table in the absence of collisions.
	2. MaxOverflowPercent
		With an increase in the number of elements, hence an increase in the number of collisions,
		the capacity of the table will expand. The expansion will occur if the expression is observed
		MaxOverflowPercent < (numberOfElements/Capacity), keeping the table constant 
		время доступа (>0.001sec). (По умолчанию = 1,5)
	3.UpgadeTableMultiplier
		A value that shows how many times the table will increase when overflowing (see above).
		(Default = 2)
