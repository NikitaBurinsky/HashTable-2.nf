HashTable_ForwardList

A hash table that uses a singly linked list to work with collisions and expands when the
overflow threshold set by the user is reached. It takes up less space than a hash table using a binary tree,
and also accepts keys of any type, but has a lower speed of searching for an element in case of
collisions.


Parameters of the table constructor:
	HashTable_ForwardList(unsigned int capacity, float MaxOverflowPercent, float UpgadeTableMultiplier)
	1. capacity: 
		The initial size of the table, the maximum number 
		elements in the table in the absence of collisions.
	2. MaxOverflowPercent
		With an increase in the number of elements, hence an increase in the number of collisions,
		the capacity of the table will expand. The expansion will occur if the expression is observed
		MaxOverflowPercent < (numberOfElements/Capacity), keeping the table constant
		аccess time (>0.001 sec). (Default = 1.5)
	3.UpgadeTableMultiplier
		A value that shows how many times the table will increase when overflowing (see above).
		(Default = 2)
