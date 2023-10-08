HashTable_BinaryTree

A hash table that uses binary trees to work with collisions and expands when the
overflow threshold set by the user is reached. It takes up more space than a hash table using a singly
linked list, and can also use only numbers as keys, however, it has a higher speed
of searching for an element when collisions occur.


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

