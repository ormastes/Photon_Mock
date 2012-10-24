#include "PhotonComparator.h"

PCComparator(int);

void testPCComparator(void) {
	int a=1 ,b=1;
	PTAssert(PC_SAME, PCCompareint(&a, &b, 0, 0, 1));
}
void testPCComparator_NotSame(void) {
	int a=1 ,b=2;
	PTAssertTrue(PC_SAME != PCCompareint(&a, &b, 0, 0, 1));
}
int PCComparatorCompareIntCustom(void* expected, void* actual, int size) {
	return PC_SAME;
}
void testPCComparator_NotSame_(void) {
	int a=1 ,b=2;
	__PCComparatorCompare_int = PCComparatorCompareIntCustom;
	PTAssertTrue(PC_SAME == PCCompareint(&a, &b, 0, 0, 1));
}

void loglong(void* toLog) {
	PLLogNumber(*(long*)toLog,10);
}
PCComparator(long,&loglong);
void testPCComparator_NotSame_CustomLog(void) {
	long a=-12 ,b=-23;
	PTAssertTrue(PC_SAME != PCComparelong(&a, &b, 0, 0, 1));
}
void logchar(void* toLog) {
	PLLogNumber(*(char*)toLog,10);
}
PCComparatorEquals(char, logchar);


void testPCComparatorEquals(void) {
	char a=1 ,b=1;
	PTAssert(PC_SAME, PCComparechar(&a, &b, 0, 0, 1));
}
void testPCComparatorEquals_NotSame(void) {
	char a=1 ,b=2;
	PTAssertTrue(PC_SAME != PCComparechar(&a, &b, 0, 0, 1));
}

typedef int* intP;
PCComparatorPointer(int);
	
void testPCComparatorPointer(void) {
	char a=1 ,b=1;
	char* ap = &a;
	char* bp = &b;
	PTAssert(PC_SAME, PCCompareintP(&ap, &bp, 0, 0, 1));
}
void testPCComparatorPointer_NotSame(void){ 
	char a=1 ,b=2;
	char* ap = &a;
	char* bp = &b;
	PTAssertTrue(PC_SAME != PCCompareintP(&ap, &bp, 0, 0, 1));
}

typedef struct {
	int a;
	int b;
} simple;

PCComparatorStruct(simple, int,a , int, b);

//  /P /C
void testPCComparatorStruct(void) {
	simple a,b;
	a.a = 1;
	b.a = 1;
	a.b = 2;
	b.b = 2;
	PTAssert(PC_SAME, PCComparesimple(&a, &b, 0, 0, 1));
}
void testPCComparatorStruct_NotSame(void){ 
	simple a,b;
	a.a = 1;
	b.a = 1;
	a.b = 2;
	b.b = 4;
	PTAssertTrue(PC_SAME != PCComparesimple(&a, &b, 0, 0, 1));
}

void main(void) {
	testPCComparator();
	testPCComparator_NotSame();
	testPCComparator_NotSame_CustomLog();

	testPCComparatorEquals();
	testPCComparatorEquals_NotSame();

	testPCComparatorPointer();
	testPCComparatorPointer_NotSame();

	testPCComparatorStruct();
	testPCComparatorStruct_NotSame();
}