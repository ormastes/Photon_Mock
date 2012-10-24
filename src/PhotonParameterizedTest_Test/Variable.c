#include "PP.h"

PPListBy(int, externList, 2,,3 ,1);
PPSet(int, externSet, 2, 3 ,1);
PPTable(
	externTable, 
	{int a; int b;},  
	{1,1},
	{1,2},
	{1,3}
);
PPRandom(int, externRandom, 1,,3,2)	;

