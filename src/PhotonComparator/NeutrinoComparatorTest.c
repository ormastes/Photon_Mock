#include "NeutrinoComparator.h"

NCComparator(int);

void testNCComparator(void) {
	int a=1 ,b=1;
	PTAssert(NC_SAME, NCCompareint(&a, &b, 0, 0, 1));
}
void testNCComparator_NotSame(void) {
	int a=1 ,b=2;
	PTAssertTrue(NC_SAME != NCCompareint(&a, &b, 0, 0, 1));
}
int NCComparatorCompareIntCustom(void* expected, void* actual, int size) {
	return NC_SAME;
}
void testNCComparator_NotSame_(void) {
	int a=1 ,b=2;
	__NCComparatorCompare_int = NCComparatorCompareIntCustom;
	PTAssertTrue(NC_SAME == NCCompareint(&a, &b, 0, 0, 1));
}

void loglong(void* toLog) {
	PLLogNumber(*(long*)toLog,10);
}
NCComparator(long,&loglong);
void testNCComparator_NotSame_CustomLog(void) {
	long a=-12 ,b=-23;
	PTAssertTrue(NC_SAME != NCComparelong(&a, &b, 0, 0, 1));
}
void logchar(void* toLog) {
	PLLogNumber(*(char*)toLog,10);
}
NCComparatorEquals(char, logchar);


void testNCComparatorEquals(void) {
	char a=1 ,b=1;
	PTAssert(NC_SAME, NCComparechar(&a, &b, 0, 0, 1));
}
void testNCComparatorEquals_NotSame(void) {
	char a=1 ,b=2;
	PTAssertTrue(NC_SAME != NCComparechar(&a, &b, 0, 0, 1));
}

typedef int* intP;
NCComparatorPointer(int);
	
void testNCComparatorPointer(void) {
	char a=1 ,b=1;
	char* ap = &a;
	char* bp = &b;
	PTAssert(NC_SAME, NCCompareintP(&ap, &bp, 0, 0, 1));
}
void testNCComparatorPointer_NotSame(void){ 
	char a=1 ,b=2;
	char* ap = &a;
	char* bp = &b;
	PTAssertTrue(NC_SAME != NCCompareintP(&ap, &bp, 0, 0, 1));
}

typedef struct {
	int a;
	int b;
} simple;

NCComparatorStruct(simple, int,a , int, b);

//  /P /C
void testNCComparatorStruct(void) {
	simple a,b;
	a.a = 1;
	b.a = 1;
	a.b = 2;
	b.b = 2;
	PTAssert(NC_SAME, NCComparesimple(&a, &b, 0, 0, 1));
}
void testNCComparatorStruct_NotSame(void){ 
	simple a,b;
	a.a = 1;
	b.a = 1;
	a.b = 2;
	b.b = 4;
	PTAssertTrue(NC_SAME != NCComparesimple(&a, &b, 0, 0, 1));
}

void main(void) {
	testNCComparator();
	testNCComparator_NotSame();
	testNCComparator_NotSame_CustomLog();

	testNCComparatorEquals();
	testNCComparatorEquals_NotSame();

	testNCComparatorPointer();
	testNCComparatorPointer_NotSame();

	testNCComparatorStruct();
	testNCComparatorStruct_NotSame();
}