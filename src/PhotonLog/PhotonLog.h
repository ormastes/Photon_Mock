#ifndef __PhotonLog_h__
#define __PhotonLog_h__
#include "PhotonConfig.h"

#ifdef PLQueueLogMode
#define PLLog(Message, ...) __PL_ArgumentCounterWithCall(__PLLog, (void*)&Message, __VA_ARGS__)
#else
#include <stdio.h>
#define PLLog(Message, ...) __PL_ArgumentCounterWithCall(__PLLog, #Message, __VA_ARGS__)
#endif

#define __PL_ArgumentCounterWithCall(Call, ...) __PL__ArgumentCounterWithCall_merge((Call, __VA_ARGS__, 20, 19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))
#define __PL__ArgumentCounterWithCall_merge(VariableWithCount) __PL__ArgumentCounterWithCall_count VariableWithCount
#define __PL__ArgumentCounterWithCall_count(Call, _1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, Count, ...) \
	Call##Count(_1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20)


#define __PLLog1(Message, ...) _PLLog(Message,0,0,0,0,0)
#define __PLLog2(Message, _1, ...) _PLLog(Message,1,_1,0,0,0)
#define __PLLog3(Message, _1, _2, ...) _PLLog(Message,2,_1, _2,0,0)
#define __PLLog4(Message, ...) _PLLog(Message,3,__VA_ARGS__,0)
#define __PLLog5(Message, ...) _PLLog(Message,4,__VA_ARGS__)

void PLLogNumber(long toChage, int radix);

typedef unsigned int default_type;

#ifdef PLQueueLogMode

#ifndef FILE
#define FILE void
#endif

#define PLM void* Message
#define PLMessage(message) \
struct message##Type;\
struct message##Type *message;\
struct message##Type

#define PLMaxMessageSize 10

struct PLMessagetType{
	void* message;
	default_type _1;
	default_type _2;
	default_type _3;
	default_type _4;
};

extern struct PLMessagetType PLMessage[];
extern unsigned int PLCurrentIndex;

void _PLLog(void* message, default_type parameterCount, default_type _1, default_type _2, default_type _3, default_type _4);

void PLLogChar(char aChar) ;
void PLLogString(void* aString);
void PLLogSetFile(File* file);

#else

#ifdef X86
#include <stdio.h>
void PLLogChar(char aChar);
void PLLogString(char* aString);
void PLLogSetFile(FILE* file);
#endif
#ifdef ARM
#ifndef FILE
#define FILE void
#endif
void PLLogChar(char aChar);
void PLLogString(char* aString) ;
void PLLogSetFile(FILE* file);
#endif

extern char* _PLMessage;
extern char* _PLMessageChar;
extern char* _PLMessageStr;
extern unsigned int _PL_1, _PL_2, _PL_3, _PL_4;
extern unsigned int _PLParameterCount;
extern unsigned int _PLWasMinus;

void _PLLog(char* message, default_type parameterCount, default_type _1, default_type _2, default_type _3, default_type _4);

#endif



#endif //__PhotonLog_h__
