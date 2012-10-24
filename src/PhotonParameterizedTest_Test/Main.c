#include "PP.h"
#include "Variable.h"

#define PPAssert(Expected, Actual) if (Expected != Actual) while(1);
#define PPAssertTrue(Expression) if (!(Expression)) while(1);


void testPPListBy(void) {
	PPListBy(int, variable, 2,,3 ,1);
	variable = 4;
	PPAssert(2, __PP_variable_Name_Original);
	PPAssert(4, variable);

	PPAssert(1, __PP_variable_By);	
}
void testPPListBy2LoopAll(void) {
	int sum=0;
	PPListBy(int, variable, 2,,4 ,2);
	PPLoopAll1(variable) {
		sum+=a_(variable);
	}
	PPAssert(6, sum);
}

PPList(int, variable2, 2,,3);
void testPPList(void) {
	PPAssert(1, __PP_variable2_By);	
}

void testPPListLoopAll(void) {
	int i=0;
	PPList(int, variable3, 2,,3);
	PPLoopAll1(variable3) {
		i++;
	}
	PPAssert(2, i);
}

void testPPListLoopAllVariableAccess(void) {
	PPList(int, variable4, 2,,2);
	PPLoopAll1(variable4) {
		PPAssert(2, a_(variable4));
	}
}

void testArgumentCounter(void) {
	PPAssert(1, __PP_ArgumentCounter(_1));
	PPAssert(20, __PP_ArgumentCounter(_1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20));
}
/*Try to make universal apply for each function but fail
#define __PP_MacroApplyForEach(Call,...) __PP__MacroApplyForEach_merge((Call,__VA_ARGS__,,,,,,,,,,,,,,,,,,,,,Dummy,Dummy,Dummy))
#define __PP__MacroApplyForEach_merge(VariableWithCount) __PP__MacroApplyForEach_count VariableWithCount
#define __PP__MacroApplyForEach_count(Call,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, PostFix, ...) \
	__PP__MacroApplyForEach_merge##PostFix##((Call,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, PostFix, __VA_ARGS__)) 
//__PP__MacroApplyForEach_merge##PostFix##((Call,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,PostFix,__VA_ARGS__))
#define __PP__MacroApplyForEach_mergeA(VariableWithCount) __PP__MacroApplyForEach_count VariableWithCount
#define __PP__MacroApplyForEach_mergeDummy(...) 
int __Test_Helper_Macro=0;
#define __Test_Helper_MacroA(A) (A*A)+
#define __Test_Helper_MacroDummy(A) (A*A)+

void testMacroApplyForEach(void) {
	int i;
	i = __PP__MacroApplyForEach_merge(__Test_Helper_Macro,1,,,,,,,,,,,,,,,,,,,,A,Dummy) + 0;
	PPAssert(-20, i);
}*/


#define __Test_Helper_Macro2(A, B,...) (A+B)
void testArgumentCounterWithCall(void) {
	int i;
	i = __PP_ArgumentCounterWithCall(__Test_Helper_Macro,1,2);
	PPAssert(3, i);
}
#define __Test_Helper_Macro3(A, B, C,...) (__Test_Helper_Macro2(A,B) +C)
void testArgumentCounterWithCall3Parameter(void) {
	int i;
	i = __PP_ArgumentCounterWithCall(__Test_Helper_Macro,1,2,3);
	PPAssert(6, i);
}

void testPPSet(void) {
	PPSet(int, variable, 1, 2);
	variable = __PP_variable_Name_Original;
	PPAssert(1, *variable);
	PPAssert(2, __PP_variable_Count);
	__PP_variable_From = variable;
	PPAssert(variable, __PP_variable_From);
	__PP_variable_To = __PP_variable_From + __PP_variable_Count;
	PPAssert(variable+2, __PP_variable_To);
}

void testPPSetLoopAll(void) {
	int i=0;
	PPSet(int, variable, 1, 2);
	PPLoopAll1(variable) {
		i++;
	}
	PPAssert(2, i);
}

void testPPSetLoopAllVariableAccess(void) {
	PPSet(int, variable, 1);
	PPLoopAll1(variable) {
		PPAssert(1, a_(variable));
	}
}



PPSet(int, variable1, 1,2);
void testPPSetLoopAllMutilple(void) {
	int i=0;
	PPSet(int, variable2, 1,2);
	PPLoopAll(variable1,variable2) {
		i++;
	}
	PPAssert(4, i);
}
PPSet(int, variable3, 3,2);
void testPPSetLoopAllMutilpleVariableAccess(void) {
	int i = 0;
	int toCompare[] = {3,2};
	PPSet(int, variable4,2);
	PPLoopAll(variable3,variable4) {
		PPAssert(toCompare[i++], a_(variable3));
		PPAssert(2, a_(variable4));
	}
}
void testPPSetLoopAllTriple(void) {
	int i = 0;
	int toCompare1[] = {1,1,2,2};
	int toCompare3[] = {3,2,3,2};
	PPSet(int, variable4,2);
	PPLoopAll(variable1, variable3,variable4) {
		PPAssert(toCompare1[i], a_(variable1));
		PPAssert(toCompare3[i++], a_(variable3));
		PPAssert(2, a_(variable4));
	}
}
PPSet(int, LoopAllVariable1, 1);
PPSet(int, LoopAllVariable2, 2);
PPSet(int, LoopAllVariable3, 3);
PPSet(int, LoopAllVariable4, 4);
PPSet(int, LoopAllVariable5, 5);
PPSet(int, LoopAllVariable6, 6);
PPSet(int, LoopAllVariable7, 7);
PPSet(int, LoopAllVariable8, 8);
PPSet(int, LoopAllVariable9, 9);
PPSet(int, LoopAllVariable10, 10);
void testPPSetLoopAllMoreThanTriple(void) {
	PPLoopAll(LoopAllVariable1,LoopAllVariable2,LoopAllVariable3,LoopAllVariable4,LoopAllVariable5,LoopAllVariable6,LoopAllVariable7,LoopAllVariable8,LoopAllVariable9,LoopAllVariable10) {
		PPAssert(1, a_(LoopAllVariable1))
		PPAssert(2, a_(LoopAllVariable2));
		PPAssert(3, a_(LoopAllVariable3));
		PPAssert(4, a_(LoopAllVariable4));
		PPAssert(5, a_(LoopAllVariable5));
		PPAssert(6, a_(LoopAllVariable6));
		PPAssert(7, a_(LoopAllVariable7));
		PPAssert(8, a_(LoopAllVariable8));
		PPAssert(9, a_(LoopAllVariable9));
		PPAssert(10, a_(LoopAllVariable10));
	}
}
void testPPSetStruct(void)  {
	int i=0;
	PPSet(struct {int a; int b;}, variable, {1,2}, {2,4});
	PPLoopAll1(variable) {
		i++;
		PPAssert(i, variable->a);
		PPAssert(i*2, variable->b);
	}
	PPAssert(2, i);
}

void testPPSetEmbeddedStruct(void)  {
	int i=0;
	PPSet(struct {int a;  struct {int c;int d;}b;}, variable, {1,{2, 4}}, {2,{4, 8}});
	PPLoopAll1(variable) {
		i++;
		PPAssert(i, variable->a);
		PPAssert(i*2, variable->b.c);
		PPAssert(i*4, variable->b.d);
	}
	PPAssert(2, i);
}
void testPPSetCharType(void)  {
	int i=0;
	PPSet(char, variable, 'a', 'b');
	PPLoopAll1(variable) {
		i++;
		PPAssert((int)'a'+i-1, (int)a_(variable));
	}
	PPAssert(2, i);
}

void testPPLoopCombi(void) {
	PPLoop(Combi, LoopAllVariable1,LoopAllVariable2,LoopAllVariable3,LoopAllVariable4,LoopAllVariable5,LoopAllVariable6,LoopAllVariable7,LoopAllVariable8,LoopAllVariable9,LoopAllVariable10) {
		PPAssert(1, a_(LoopAllVariable1))
		PPAssert(2, a_(LoopAllVariable2));
		PPAssert(3, a_(LoopAllVariable3));
		PPAssert(4, a_(LoopAllVariable4));
		PPAssert(5, a_(LoopAllVariable5));
		PPAssert(6, a_(LoopAllVariable6));
		PPAssert(7, a_(LoopAllVariable7));
		PPAssert(8, a_(LoopAllVariable8));
		PPAssert(9, a_(LoopAllVariable9));
		PPAssert(10, a_(LoopAllVariable10));
	}
}


void testPPMax2(void) {
	PPAssert(2,__PP_MAX2(1,2));
}
void testPPMax3(void) {
	PPAssert(3,__PP_MAX3(3,2,1));
}
void testPPMax10(void) {
	PPAssert(10,__PP_MAX10(10,9,8,7,6,5,4,3,2,1));
}
void testPPMax(void) {
	PPAssert(2,__PP_MAX(1,2));
}


int testNameCompose(void) {
	int __PP_NameCompose(a,b,c)= 0;
	return __PP_NameCompose(a,b,c);
}

void testInitMultipleVariable(void) {
	PPListBy(int, Name, 1,,3, 2);
	Name = 3;
	__PP_Init(Name);
	PPAssert(1,Name);
}


void testIncreaseUntilMaxAndLoop(void) {
	int sum =0;
	PPListBy(int, Name, 1,,3, 2);
	Name = 1;
	sum += Name;
	IncreaseUntilMaxAndLoop(Name);
	sum += Name;
	IncreaseUntilMaxAndLoop(Name);
	sum += Name;
	PPAssert(1+3+1, sum);
}

PPListBy(int, LoopOnceListVariable, 1,,3, 2);
void testMaxFromNameList(void) {
	int count = __PP_MAX_WithCount(LoopOnceListVariable);
	PPAssert(2,count);
}
void testLoopOnce1(void) {
	int sum =0;
	PPLoopOnce(LoopOnceListVariable) {
		sum += a_(LoopOnceListVariable);
	}
	PPAssert(1+3,sum);
}
PPSet(int, LoopOnceListVariable2, 1,2,3);
void testLoopOnce2(void) {
	int sum1 =0;
	int sum2 =0;
	PPLoopOnce(LoopOnceListVariable,LoopOnceListVariable2) {
		sum1 += a_(LoopOnceListVariable);
		sum2 += a_(LoopOnceListVariable2);
	}
	PPAssert(1+3+1,sum1);
	PPAssert(1+2+3,sum2);
}

PPSet(int, LoopOnceVariable1, 1,2);
PPSet(int, LoopOnceVariable2, 3,4,5);
PPSet(int, LoopOnceVariable3, 6);
PPSet(int, LoopOnceVariable4, 1,2);
PPSet(int, LoopOnceVariable5, 1,2);
PPSet(int, LoopOnceVariable6, 1,2);
PPSet(int, LoopOnceVariable7, 1,2);
PPSet(int, LoopOnceVariable8, 1,2);
PPSet(int, LoopOnceVariable9, 1,2);
PPSet(int, LoopOnceVariable10, 7,8,9,10);
void testPPLoopOnceSet10(void) {
	int i =0;
	int toCompare1[] = {1,2,1,2};
	int toCompare2[] = {3,4,5,3};
	int toCompare3[] = {6,6,6,6};
	int toCompare4[] = {1,2,1,2};
	int toCompare5[] = {1,2,1,2};
	int toCompare6[] = {1,2,1,2};
	int toCompare7[] = {1,2,1,2};
	int toCompare8[] = {1,2,1,2};
	int toCompare9[] = {1,2,1,2};
	int toCompare10[] = {7,8,9,10};

	PPLoopOnce(LoopOnceVariable1,LoopOnceVariable2,LoopOnceVariable3,LoopOnceVariable4,
			LoopOnceVariable5,LoopOnceVariable6,LoopOnceVariable7,LoopOnceVariable8,LoopOnceVariable9,LoopOnceVariable10)  {
	/*	PPAssert(toCompare1[i], a_(LoopOnceVariable1));
		PPAssert(toCompare2[i], a_(LoopOnceVariable2));
		PPAssert(toCompare3[i], a_(LoopOnceVariable3))
		PPAssert(toCompare4[i], a_(LoopOnceVariable4));
		PPAssert(toCompare5[i], a_(LoopOnceVariable5));
		PPAssert(toCompare6[i], a_(LoopOnceVariable6));
		PPAssert(toCompare7[i], a_(LoopOnceVariable7));
		PPAssert(toCompare8[i], a_(LoopOnceVariable8));
		PPAssert(toCompare9[i], a_(LoopOnceVariable9));
		PPAssert(toCompare10[i++], a_(LoopOnceVariable10));*/
		
	}
}
#define IF(BOOL, BLOCK) if(BOOL) BLOCK
struct userid {
char uid[10];
int insize, outsize;
} list[] = {
{"user1", 10, 20},
{"user2", 0, 20},
{"user3", 11, 2}
};
//#define PPTable(TableName, size, TypeAndNameList) typedef struct TypeAndNameList TableName##Type; struct TypeAndNameList __PP_Table_##TableName[size] = 
//#define PPTable2(TableName, size, TypeAndNameList, data, data2) typedef struct TypeAndNameList TableName##Type; struct TypeAndNameList __PP_Table_##TableName[size] =\
//{data,data2};


void testPPTable(void) {

	int i=0;
	PPTable(
		TableName, 
		{int a; int b;},  
		{1,1},
		{1,2},
		{1,3}
	);
	PPLoopAll(TableName) {
		i++;
		PPAssert(i, TableName->b);
		TableName;
	}
	PPAssert(3, i);
}

void testPPTableStruct(void) {
	int i=0;
	PPTable(
		TableName, 
		{struct {int a; int b;}a; int b;},  
		{{2,4},1},
		{{4,8},2},
		{{6,12},3}
	);
	PPLoopAll(TableName) {
		i++;
		PPAssert(i, TableName->b);
		PPAssert(i*2, TableName->a.a);
		PPAssert(i*4, TableName->a.b);
		TableName;
	}
	PPAssert(3, i);
}
void testPPTableChar(void) {
	int i=0;
	PPTable(
		TableName, 
		{int a; char b;},  
		{1,'a'},
		{1,'b'},
		{1,'c'}
	);
	PPLoopAll(TableName) {
		i++;
		PPAssert((int)'a'+i-1, (int)TableName->b);
		TableName;
	}
	PPAssert(3, i);
}

/*
Table(Name, int, a, int, b) 
typedef struct { int a, int b} list[]
NameType							{
	{12,		13}
	{13,		14}
};
		Type(	a,b,c,d,e,f)

	=> struct


Table(int columnCount, nameA, nameB, nameC, sizeA, sizeB, sizeC, dataA1, dataB1, dataC1)
>Table
Table (

)
Table (2,2
	Name,	Name,
	int,	int,
	1,		2,
	2,		3,
);
Set(Name1, row2(col2(_1,_2,_3,...))); col2>컬럼 인자를뽑고, row2 2개만 받고 버린다.
Set(Name2, row2(col2(_2,_3,_4,...);
void* TableName[2];\
void* TableRowTypeSize[2];\
int tableColumnSize=XX;\
int tablerowCount;
TableName_row...

looPPable(TableName)
tablerowCount=0;
tablerowCount<tableColumnSize;
tablerowCount++, (TableName[1]+=TableRowTypeSize[1])=>increase(tableName, typesize, columnSize) 

>Pair
int count
Pair(context, col, Name, from,to,by,....) 
PairCompare(context,count)
PairINcreae(context,count,Name,Name...)

가장 큰거 순으로 LOOP
ab loop 값할당, doesn't care bit setup
ac loop 값할당, doesn't care bit setup
bc loop 값할당, doesn't care bit setup
모두 Doesn't care 면 리턴
AB a값
AB other값
AC a값
AC other값
BC [b]
BC [other]
*/


void testRandom_JustSeedReturnRandomGenerator_LoopAll(void) {
	PPRandom(int, random, 1,,3,1);
	PPLoopAll(random) {
		PPAssert(PP_RANDOM_SEED, PPA(random));
	}
}



void testRandom_JustSeedReturnRandomGenerator_LoopOnce(void) {
	PPRandom(int, arandom, 1,,3,1);
	PPLoopOnce(arandom) {
		PPAssert(PP_RANDOM_SEED, PPA(arandom));
	}
}

void testRandom_JustSeedReturnRandomGenerator_LoopAll_2times(void) {
	int expectedValue[] = {0,0,1,1};
	int i = 0;
	PPRandom(int, random, 1,,3,2);
	PPLoopAll(random, LoopOnceVariable1) {
		PPAssert(PP_RANDOM_SEED+expectedValue[i++], PPA(random));
	}
}

void testRandom_JustSeedReturnRandomGenerator_LoopOnce_2times(void) {
	int expectedValue[] = {0,1};
	int i = 0;
	PPRandom(int, arandom, 1,,3,2);
	PPLoopOnce(arandom, LoopOnceVariable1) {
		PPAssert(PP_RANDOM_SEED+expectedValue[i++], PPA(arandom));
	}
}
/*
void testPair() {
	PPListBy(int, variable, 2,,3 ,1);
	PPListBy(int, variable1, 2,,2 ,1);
	PPListBy(int, variable2, 2,,14 ,3);
	PPListBy(int, variable3, 2,,8 ,2);
	unsigned int __PP_Index_;
	unsigned int __PP_Max_ = __PP_MAX_WithCount(variable, variable1, variable2, variable3);
	unsigned int __PP_Index_Array_[__PP_ArgumentCounter(variable, variable1, variable2, variable3)];
	unsigned int __PP_Offset_Shift_Vector_Array_[__PP_ArgumentCounter(variable, variable1, variable2, variable3)]={3,4,1,2};
	unsigned int __PP_Current_Offset_Shift_ = 0;
	unsigned int __PP_2nd_index_;
	unsigned int __PP_2nd_Max_ = 3;//__PP_StepCalculation
	//Calculate_Order
	for (__PP_2nd_index_ = 0, __PP_Current_Offset_Shift_ = 0; __PP_2nd_index_ <= __PP_2nd_Max_; __PP_Current_Offset_Shift_++,__PP_2nd_index_++)
		for (
			__PP_Index_ = 0,
			PPLoopPair_T0_PPCallVariableArgument((__PP_Init,variable, variable1, variable2, variable3));
			__PP_Index_< __PP_Max_;
			IncreaseUntilMaxAndLoop(variable, variable1, variable2, variable3), 
			__PP_Index_++) 
		{
		}
}*/
void testGeneratedTable(void) {
/*Insert Next Code From Here:*/
PPTable(
/*Table Name*/ testData,
/*Param Name*/ {int Param0; int Param1; int Param2; int Param3; },
/*        0:*/ {1, 3, 7, 10},
/*        1:*/ {2, 3, 8, 11},
/*        2:*/ {2, 4, 9, 10},
/*        3:*/ {1, 5, 9, 11},
/*        4:*/ {2, 6, 7, 11},
/*        5:*/ {1, 4, 8, 10},
/*        6:*/ {2, 5, 7, 10},
/*        7:*/ {1, 6, 8, 10},
/*        8:*/ {1, 3, 9, 10},
/*        9:*/ {1, 4, 7, 11},
/*       10:*/ {1, 5, 8, 10},
/*       11:*/ {1, 6, 9, 10}
);
/*Insert Next Code To Here:*/
}

void testExternListPPLoopAll(void) {
	int sum=0;
	PPLoopAll(externList) {
		sum+=a_(externList);
	}
	PPAssert(5, sum);
}
void testExternListPPLoopOnce(void) {
	int sum=0;
	PPLoopOnce(externList) {
		sum+=a_(externList);
	}
	PPAssert(5, sum);
}
void testExternSetPPLoopAll(void) {
	int sum=0;
	PPLoopAll(externSet) {
		sum+=a_(externSet);
	}
	PPAssert(6, sum);
}
void testExternSetPPLoopOnce(void) {
	int sum=0;
	PPLoopOnce(externSet) {
		sum+=a_(externSet);
	}
	PPAssert(6, sum);
}
void testExternTablePPLoopAll(void) {
	int i=0;
	PPLoopAll(externTable) {
		i++;
		PPAssert(i, externTable->b);
		externTable;
	}
	PPAssert(3, i);
}
void testExternTablePPLoopOnce(void) {
	int i=0;
	PPLoopOnce(externTable) {
		i++;
		PPAssert(i, externTable->b);
		externTable;
	}
	PPAssert(3, i);
}
void testExternRandomPPLoopAll(void) {
	int expectedValue[] = {0,0,1,1};
	int i = 0;
	PPLoopAll(externRandom, LoopOnceVariable1) {
		PPAssert(PP_RANDOM_SEED+expectedValue[i++], PPA(externRandom));
	}
}

void testExternRandomPPLoopOnce(void) {
	int expectedValue[] = {0,1};
	int i = 0;
	PPLoopOnce(externRandom, LoopOnceVariable1) {
		PPAssert(PP_RANDOM_SEED+expectedValue[i++], PPA(externRandom));
	}
}

void runParameterizedTests(void) {
	testPPListBy();
	testPPList();
	testPPListBy2LoopAll();
	testPPListLoopAll();
	testPPListLoopAllVariableAccess();
	testArgumentCounter();
	testArgumentCounterWithCall();
	testArgumentCounterWithCall3Parameter();
	testPPSet();
	testPPSetLoopAll();
	testPPSetLoopAllVariableAccess(); 
	testPPSetLoopAllMutilple();
	testPPSetLoopAllMutilpleVariableAccess();
	testPPSetLoopAllTriple();
	testPPSetLoopAllMoreThanTriple();
	testPPSetStruct();
	testPPSetEmbeddedStruct();
	testPPSetCharType();
	testPPLoopCombi();
	testPPMax2();
	testPPMax3();
	testPPMax10();
	testPPMax();
	testNameCompose();
	testInitMultipleVariable();
	testIncreaseUntilMaxAndLoop();
	testMaxFromNameList();
	testLoopOnce1() ;
	testLoopOnce2() ;
	testPPLoopOnceSet10() ;
	testPPTable();
	testPPTableStruct();
	testPPTableChar();
	testRandom_JustSeedReturnRandomGenerator_LoopAll();
	testRandom_JustSeedReturnRandomGenerator_LoopOnce();
	testRandom_JustSeedReturnRandomGenerator_LoopAll_2times();
	testRandom_JustSeedReturnRandomGenerator_LoopOnce_2times();
	testGeneratedTable();

	testExternListPPLoopAll();
	testExternListPPLoopOnce();
	testExternSetPPLoopAll() ;
	testExternSetPPLoopOnce() ;
	testExternTablePPLoopAll() ;
	testExternTablePPLoopOnce() ;
	testExternRandomPPLoopAll() ;
	testExternRandomPPLoopOnce();
}

void main(void) {
	runParameterizedTests();
}
