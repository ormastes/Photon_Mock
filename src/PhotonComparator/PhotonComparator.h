#ifndef _PhotonComparator_h_
#define _PhotonComparator_h_

#include "PhotonLog.h"

#define PC_SAME 0
#ifndef byte
#define byte char
#endif //byte

int PCCompare(void* expected, void* actual, int size) ;

#define PTAssert(Expected, Actual) if (Expected != Actual) while(1);
#define PTAssertTrue(Expression) if (!(Expression)) while(1);


#define __PC_ArgumentCounterWithCall( ...) __PC__ArgumentCounterWithCall_merge(( __VA_ARGS__, 23,22,21,20, 19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))
#define __PC__ArgumentCounterWithCall_merge(VariableWithCount) __PC__ArgumentCounterWithCall_count VariableWithCount
#define __PC__ArgumentCounterWithCall_count(Call, _1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23, Count, ...) \
	Call##Count(_1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23)



typedef struct PCNode {
	void* data;
	struct PCNode* prev;
} PCNode;

typedef int (*__PCComparatorCompareType)(void* expected, void* actual, int size);
typedef void (*__PCComparatorLogType)(void* toLog);

#define PCComparator(...) __PC_ArgumentCounterWithCall(PCComparator, __VA_ARGS__)
#define PCComparator1(Type, ...) \
	extern __PCComparatorCompareType __PCComparatorCompare_##Type;\
	extern __PCComparatorLogType __PCComparatorLog_##Type;\
	int PCCompare##Type(void* expected, void* actual, int depth, PCNode* prevNode, int log) {\
		int i;\
		int result = (__PCComparatorCompare_##Type) ? __PCComparatorCompare_##Type(expected, actual, sizeof(Type)):PCCompare(expected, actual, sizeof(Type)); \
		if (result != PC_SAME) {\
			for (i=0; i < depth;i++) PLLogChar(' ');\
			PLLog(Expected_);\
			if(__PCComparatorLog_##Type == 0) {PLLog(d__,*(unsigned int*)expected);}else{__PCComparatorLog_##Type(expected);}\
			PLLog(_But_Actual_);\
			if(__PCComparatorLog_##Type == 0) {PLLog(d__,*(unsigned int*)actual);}else{__PCComparatorLog_##Type(actual);}\
			PLLogChar('\n');\
		}\
		return result;\
	}\
	__PCComparatorCompareType __PCComparatorCompare_##Type = 0;\
	__PCComparatorLogType __PCComparatorLog_##Type
#define PCComparator2(Type, TypeLog,...) PCComparator1(Type, TypeLog) = TypeLog\

#define PCComparatorEquals(...) __PC_ArgumentCounterWithCall(PCComparatorEquals, __VA_ARGS__)
#define PCComparatorEquals1(Type, ...) \
	extern __PCComparatorCompareType __PCComparatorCompare_##Type;\
	extern __PCComparatorLogType __PCComparatorLog_##Type;\
	int PCCompare##Type(void* expected, void* actual, int depth, PCNode* prevNode, int log) {\
		int i;\
		int result = (__PCComparatorCompare_##Type) ? __PCComparatorCompare_##Type(expected, actual, sizeof(Type)):((*(Type*)expected) == (*(Type*)actual))?PC_SAME:-1; \
		if (result != PC_SAME) {\
			for (i=0; i < depth;i++) PLLogChar(' ');\
			PLLog(Expected_);\
			if(__PCComparatorLog_##Type == 0) {PLLog(d__,*(unsigned int*)expected);}else{__PCComparatorLog_##Type(expected);}\
			PLLog(_But_Actual_);\
			if(__PCComparatorLog_##Type == 0) {PLLog(d__,*(unsigned int*)actual);}else{__PCComparatorLog_##Type(actual);}\
			PLLogChar('\n');\
		}\
		return result;\
	}\
	__PCComparatorCompareType __PCComparatorCompare_##Type = 0;\
	__PCComparatorLogType __PCComparatorLog_##Type
#define PCComparatorEquals2(Type, TypeLog,...) PCComparatorEquals1(Type, TypeLog) = TypeLog\

#define PCComparatorPointer(...) __PC_ArgumentCounterWithCall(PCComparatorPointer, __VA_ARGS__)
#define PCComparatorPointer1(Type, ...) PCComparatorPointer2(Type,Type##P, __VA_ARGS__)
#define PCComparatorPointer2(Type, SpecifiedName, ...) \
	extern __PCComparatorCompareType __PCComparatorCompare_##SpecifiedName;\
	int PCCompare##SpecifiedName(void* expected, void* actual, int depth, PCNode* prevNode, int log) {\
		int i;\
		PCNode node;\
		int result;\
		PCNode* currentNode;\
		currentNode = prevNode;\
		while (currentNode != 0) {\
			if (actual == currentNode->data) return PC_SAME;\
			currentNode = currentNode->prev;\
		}\
		node.prev = prevNode;\
		node.data = actual;\
		if (__PCComparatorCompare_##SpecifiedName){\
			result = __PCComparatorCompare_##SpecifiedName(expected, actual, sizeof(SpecifiedName)) ;\
			if (result != PC_SAME) {\
				for (i=0; i < depth+1;i++) PLLogChar(' ');\
				PLLog(Expected_);\
				PLLog(d__,*(unsigned int*)expected);\
				PLLog(_But_Actual_);\
				PLLog(d__,*(unsigned int*)actual);\
				PLLogChar('\n');\
				for (i=0; i < depth;i++) PLLogChar(' ');\
				PLLog(Which_is_Pointer);\
				PLLogChar('\n');\
			}\
		}else { \
			result = (PCCompare##Type)(*(void**)expected, *(void**)actual, depth+1, &node, log);\
			if (result != PC_SAME) {\
				for (i=0; i < depth;i++) PLLogChar(' ');\
				PLLog(Which_is_Pointer);\
				PLLogChar('\n');\
			}\
		}\
		return result;\
	}\
	__PCComparatorCompareType __PCComparatorCompare_##SpecifiedName

#define PCComparatorStruct(Type, ...) \
	extern __PCComparatorCompareType __PCComparatorCompare_##Type;\
	int PCCompare##Type(void* expected, void* actual, int depth, PCNode* prevNode, int log) {\
		Type* _expected = (Type*)expected;\
		Type* _actual = (Type*)actual;\
		char* typeName = #Type;\
		if (__PCComparatorCompare_##Type != 0) {\
			if(__PCComparatorCompare_##Type(expected, actual, sizeof(Type)) == PC_SAME) {\
				return PC_SAME;\
			} else {\
				return !PC_SAME;\
			}\
		}\
		PCComparatorCompare(__VA_ARGS__)\
		return PC_SAME;\
	}\
	__PCComparatorCompareType __PCComparatorCompare_##Type = 0;\



#define PCComparatorCompare(args) _PCComparatorCompare((args))
#define _PCComparatorCompare(args) __PCComparatorCompare args
#define __PCComparatorCompare(...) __PC_ArgumentCounterWithCall(PCComparatorCompare, __VA_ARGS__)

#define PCComparatorCompare2(t1, n1, ...) \
	if ((PCCompare##t1)((void*)&_expected->n1, (void*)&_actual->n1,depth+1, prevNode, log) != 0) {\
		if (log)PLLog(Which_is_struct_s___##n1, (unsigned int)typeName);\
		return !PC_SAME;\
	}\
	 
#define PCComparatorCompare4(t1, n1, t2, n2, ...) \
	if ((PCCompare##t1)((void*)&_expected->n1, (void*)&_actual->n1,depth+1, prevNode, log) != 0) {\
		if (log)PLLog(Which_is_struct_s___##n1, (unsigned int)typeName);\
		return !PC_SAME;\
	}\
	PCComparatorCompare2(t2, n2) 

#define PCComparatorCompare6(t1, n1, t2, n2, t3, n3, ...) \
	if ((PCCompare##t1)((void*)&_expected->n1, (void*)&_actual->n1,depth+1, prevNode, log) != 0) {\
		if (log)PLLog(Which_is_struct_s___##n1, (unsigned int)typeName);\
		return !PC_SAME;\
	}\
	PCComparatorCompare4(t2, n2, t3, n3) 
	
#define PCComparatorCompare8(t1, n1, t2, n2, t3, n3, t4, n4, ...) \
	if ((PCCompare##t1)((void*)&_expected->n1, (void*)&_actual->n1,depth+1, prevNode, log) != 0) {\
		if (log)PLLog(Which_is_struct_s___##n1, (unsigned int)typeName);\
		return !PC_SAME;\
	}\
	PCComparatorCompare6(t2, n2, t3, n3, t4, n4) 

#define PCComparatorCompare10(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, ...) \
	if ((PCCompare##t1)((void*)&_expected->n1, (void*)&_actual->n1,depth+1, prevNode, log) != 0) {\
		if (log)PLLog(Which_is_struct_s___##n1, (unsigned int)typeName);\
		return !PC_SAME;\
	}\
	PCComparatorCompare8(t2, n2, t3, n3, t4, n4, t5, n5) 

#define PCComparatorCompare12(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, ...) \
	if ((PCCompare##t1)((void*)&_expected->n1, (void*)&_actual->n1,depth+1, prevNode, log) != 0) {\
		if (log)PLLog(Which_is_struct_s___##n1, (unsigned int)typeName);\
		return !PC_SAME;\
	}\
	PCComparatorCompare10(t2, n2, t3, n3, t4, n4, t5, n5, t6, n6) 

#define PCComparatorCompare14(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7, ...) \
	if ((PCCompare##t1)((void*)&_expected->n1, (void*)&_actual->n1,depth+1, prevNode, log) != 0) {\
		if (log)PLLog(Which_is_struct_s___##n1, (unsigned int)typeName);\
		return !PC_SAME;\
	}\
	PCComparatorCompare12(t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7) 


#define PCComparatorCompare16(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7, t8, n8, ...) \
	if ((PCCompare##t1)((void*)&_expected->n1, (void*)&_actual->n1,depth+1, prevNode, log) != 0) {\
		if (log)PLLog(Which_is_struct_s___##n1, (unsigned int)typeName);\
		return !PC_SAME;\
	}\
	PCComparatorCompare14(t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7, t8, n8) 

#define PCComparatorCompare18(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7, t8, n8, t9, n9, ...) \
	if ((PCCompare##t1)((void*)&_expected->n1, (void*)&_actual->n1,depth+1, prevNode, log) != 0) {\
		if (log)PLLog(Which_is_struct_s___##n1, (unsigned int)typeName);\
		return !PC_SAME;\
	}\
	PCComparatorCompare16(t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7, t8, n8, t9, n9) 

#define PCComparatorCompare20(t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7, t8, n8, t9, n9, t10, n10, ...) \
	if ((PCCompare##t1)((void*)&_expected->n1, (void*)&_actual->n1,depth+1, prevNode, log) != 0) {\
		if (log)PLLog(Which_is_struct_s___##n1, (unsigned int)typeName);\
		return !PC_SAME;\
	}\
	PCComparatorCompare18(t2, n2, t3, n3, t4, n4, t5, n5, t6, n6, t7, n7, t8, n8, t9, n9, t10, n10) 


#endif //_PhotonComparator_h_