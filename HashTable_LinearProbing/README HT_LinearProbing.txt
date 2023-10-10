HashTable_LinearProbing

A hash table that uses a linear probing to work with collisions and expands when the
overflow threshold set by the user is reached. 
Шt takes up less space than a hash table using linked chains, limiting the number of elements to the capacity value.



Parameters of the table constructor:
	HashTable_LinearProbing(unsigned int capacity, float MaxOverflowPercent, float UpgadeTableMultiplier)
	1. capacity: 
		The initial size of the table, the maximum number 
		elements.
	2. MaxOverflowPercent
		With an increase in the number of elements, hence an increase in the number of collisions,
		the capacity of the table will expand. The expansion will occur if the expression is observed
		MaxOverflowPercent < (numberOfElements/Capacity), keeping the table constant
		аccess time (>0.001 sec). (Default = 1.5)
	3.UpgadeTableMultiplier
		A value that shows how many times the table will increase when overflowing (see above).
		(Default = 2)
