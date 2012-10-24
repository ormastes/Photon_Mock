#ifndef _PhotonParameterizedTest_h_
#define _PhotonParameterizedTest_h_

#define PPListKind 1
#define PPSetKind 2
#define PPTableKind 3
#define PPRandomKind 4
#define PPLoopKind 4


#define PPDefineList(Type, Name) \
	extern Type __PP_##Name##_Name_Original;\
	extern Type Name;\
	typedef Type __PP_##Name##_Type;\
	extern int __PP_##Name##_Kind;\
	extern int __PP_##Name##_Count;\
	extern int __PP_##Name##_From;\
	extern int __PP_##Name##_To; /*Exclusive*/\
	extern int __PP_##Name##_By

#define PPListBy(Type, Name, From, Dummy, To, By) \
	Type __PP_##Name##_Name_Original = From;\
	Type Name;\
	typedef Type __PP_##Name##_Type;\
	int __PP_##Name##_Kind= PPListKind;\
	int __PP_##Name##_Count = (To-From)/By*By +1;\
	int __PP_##Name##_From = From;\
	int __PP_##Name##_To = To+1; /*Exclusive*/\
	int __PP_##Name##_By = By

#define PPList(Type, Name, From, Dummy, To) PPListBy(Type, Name, From, Dummy, To, 1)



/*
#define PPSet(Type, ...) __PP_PPSet__((Type, __VA_ARGS__, 0))
#define __PP_PPSet__(Parameter) __PP_PPSet_ Parameter
#define __PP_PPSet_(Type, Name, ...) \
	Type __PP_##Name##_Name_Original_[] = {__VA_ARGS__};\
	Type* __PP_##Name##_Name_Original = __PP_##Name##_Name_Original_;\
	Type* Name;\
	typedef Type __PP_##Name##_Type;\
	int __PP_##Name##_Kind= PPSetKind;\
	int __PP_##Name##_Count = (__PP_ArgumentCounter_Min2(__VA_ARGS__)-1);\
	Type*  __PP_##Name##_From;\
	Type*  __PP_##Name##_To;\
	int __PP_##Name##_By = 1;
*/
#define PPDefineSet(Type, Name)\
	typedef Type __PP_##Name##_Type;\
	extern __PP_##Name##_Type __PP_##Name##_Name_Original_[];\
	extern __PP_##Name##_Type* __PP_##Name##_Name_Original;\
	extern __PP_##Name##_Type* Name;\
	extern int __PP_##Name##_Kind;\
	extern int __PP_##Name##_Count;\
	extern __PP_##Name##_Type*  __PP_##Name##_From;\
	extern __PP_##Name##_Type*  __PP_##Name##_To;\
	extern int __PP_##Name##_By

#define PPSet(...) __PPSet((__VA_ARGS__ , 0))
#define __PPSet(Parameter) ___PPSet Parameter
#define ___PPSet(Type, Name, ...)\
	typedef Type __PP_##Name##_Type;\
	__PP_##Name##_Type __PP_##Name##_Name_Original_[] = {__VA_ARGS__};\
	__PP_##Name##_Type* __PP_##Name##_Name_Original = __PP_##Name##_Name_Original_;\
	__PP_##Name##_Type* Name;\
	int __PP_##Name##_Kind= PPSetKind;\
	int __PP_##Name##_Count = (sizeof(__PP_##Name##_Name_Original_)/sizeof(__PP_##Name##_Type)-1);\
	__PP_##Name##_Type*  __PP_##Name##_From;\
	__PP_##Name##_Type*  __PP_##Name##_To;\
	int __PP_##Name##_By = 1

#define PPDefineTable(Name, Type)\
	typedef struct Type __PP_##Name##_Type;\
	extern __PP_##Name##_Type __PP_##Name##_Name_Original[];\
	extern __PP_##Name##_Type* Name;\
	extern int __PP_##Name##_Kind;\
	extern int __PP_##Name##_Count;\
	extern __PP_##Name##_Type*  __PP_##Name##_From;\
	extern __PP_##Name##_Type*  __PP_##Name##_To;\
	extern int __PP_##Name##_By

#define PPTable(Name, Type, ...)\
	typedef struct Type __PP_##Name##_Type;\
	__PP_##Name##_Type __PP_##Name##_Name_Original[] = {__VA_ARGS__};\
	__PP_##Name##_Type* Name;\
	int __PP_##Name##_Kind= PPTableKind;\
	int __PP_##Name##_Count = (sizeof(__PP_##Name##_Name_Original)/sizeof(__PP_##Name##_Type));\
	__PP_##Name##_Type*  __PP_##Name##_From;\
	__PP_##Name##_Type*  __PP_##Name##_To;\
	int __PP_##Name##_By = 1

#define __PP_PPTable_OnlyDeclare(Name, Type)\
	typedef struct Type __PP_##Name##_Type;\
	__PP_##Name##_Type* __PP_##Name##_Name_Original_=0;\
	__PP_##Name##_Type* __PP_##Name##_Name_Original=0;\
	__PP_##Name##_Type* Name;\
	int __PP_##Name##_Kind= PPTableKind;\
	int __PP_##Name##_Count = 1;\
	__PP_##Name##_Type*  __PP_##Name##_From;\
	__PP_##Name##_Type*  __PP_##Name##_To;\
	int __PP_##Name##_By = 1

extern long PP_RANDOM_SEED;

#define PPDefineRandom(Type, Name) \
	Type __PP_##Name##_Name_Original;\
	Type Name;\
	typedef Type __PP_##Name##_Type;\
	extern int __PP_##Name##_Kind;\
	extern int __PP_##Name##_Count;\
	extern int __PP_##Name##_From;\
	extern int __PP_##Name##_To; /*Exclusive*/\
	extern int __PP_##Name##_By

#define PPRandom(Type, Name, From, Dummy, To, Times) \
	Type __PP_##Name##_Name_Original = 0;\
	Type Name;\
	typedef Type __PP_##Name##_Type;\
	int __PP_##Name##_Kind= PPRandomKind;\
	int __PP_##Name##_Count = Times;\
	int __PP_##Name##_From = From;\
	int __PP_##Name##_To = To+1; /*Exclusive*/\
	int __PP_##Name##_By = 1

long __PP_Random_Value(long from_inclusive, long to_exclusive, long random_seed);

#define PPA(Name) ((__PP_##Name##_Kind == PPListKind)?((__PP_##Name##_Type)Name):\
					((__PP_##Name##_Kind == PPRandomKind)?((__PP_##Name##_Type)__PP_Random_Value((__PP_##Name##_Type)__PP_##Name##_From, (__PP_##Name##_Type)__PP_##Name##_To, (__PP_##Name##_Type)Name)):\
						((__PP_##Name##_Type)(*(__PP_##Name##_Type*)Name))))

#define PPRow(Name) (*(__PP_##Name##_Type*)Name)


#define PPLoopAll1(Name, ...)\
	for (Name=__PP_##Name##_Name_Original,\
	__PP_##Name##_From = __PP_##Name##_Name_Original,\
	__PP_##Name##_To = __PP_##Name##_Name_Original+__PP_##Name##_Count; \
	Name<__PP_##Name##_Name_Original+__PP_##Name##_Count;\
	Name+= __PP_##Name##_By)



//_Name, _SetSameValueAsNameToStop, _From, _To, _CountDown)

#define PPLoopAll2(v1,v2, ...) PPLoopAll1(v1) PPLoopAll1(v2)
#define PPLoopAll3(v1,v2,v3, ...) PPLoopAll2(v1, v2) PPLoopAll1(v3)
#define PPLoopAll4(v1,v2,v3,v4, ...) PPLoopAll3(v1,v2,v3) PPLoopAll1(v4)
#define PPLoopAll5(v1,v2,v3,v4,v5, ...) PPLoopAll4(v1,v2,v3,v4) PPLoopAll1(v5)
#define PPLoopAll6(v1,v2,v3,v4,v5,v6, ...) PPLoopAll5(v1,v2,v3,v4,v5) PPLoopAll1(v6)
#define PPLoopAll7(v1,v2,v3,v4,v5,v6,v7, ...) PPLoopAll6(v1,v2,v3,v4,v5,v6) PPLoopAll1(v7)
#define PPLoopAll8(v1,v2,v3,v4,v5,v6,v7,v8, ...) PPLoopAll7(v1,v2,v3,v4,v5,v6,v7) PPLoopAll1(v8)
#define PPLoopAll9(v1,v2,v3,v4,v5,v6,v7,v8,v9, ...) PPLoopAll8(v1,v2,v3,v4,v5,v6,v7,v8) PPLoopAll1(v9)
#define PPLoopAll10(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10, ...) PPLoopAll9(v1,v2,v3,v4,v5,v6,v7,v8,v9) PPLoopAll1(v10)

#define PPLoopAll(...)\
	__PP_ArgumentCounterWithCall(PPLoopAll, __VA_ARGS__)

#define PPLoopAllCount(Count,Var,...) PPLoopAll##Count ( Var,__VA_ARGS__)

#define PPLoopOnce_T0_PPCallVariableArgument(Param) AppplyCallWithInput Param
#define PPLoopOnce(...) \
	unsigned int PPCallVariableArgument(__PP_NameCompose, (__PP_Index_,__VA_ARGS__)) = 0;\
	unsigned int PPCallVariableArgument(__PP_NameCompose, (__PP_Max_,__VA_ARGS__)) = __PP_MAX_WithCount(__VA_ARGS__);\
	for (\
		PPLoopOnce_T0_PPCallVariableArgument((__PP_Init,__VA_ARGS__)); \
		PPCallVariableArgument(__PP_NameCompose,(__PP_Index_,__VA_ARGS__))< PPCallVariableArgument(__PP_NameCompose,(__PP_Max_,__VA_ARGS__));\
		PPLoopOnce_T0_PPCallVariableArgument((IncreaseUntilMaxAndLoop,__VA_ARGS__)), \
		PPCallVariableArgument(__PP_NameCompose,(__PP_Index_,__VA_ARGS__)	)++)

#define PPLoopPair_T0_PPCallVariableArgument(Param) AppplyCallWithInput Param
/*
#define PPLoopPair(...)\
	unsigned int PPCallVariableArgument(__PP_NameCompose, (__PP_Index_,__VA_ARGS__));\
	unsigned int PPCallVariableArgument(__PP_NameCompose, (__PP_Max_,__VA_ARGS__)) = __PP_MAX_WithCount(__VA_ARGS__);\
	unsigned int __PP_Index_Array_[__PP_ArgumentCounter(__VA_ARGS__)];\
	unsigned int __PP_Offset_Shift_Vector_Array_[__PP_ArgumentCounter(__VA_ARGS__)];\
	unsigned int __PP_Current_Offset_Shift_ = 0;\
	unsigned int __PP_2nd_index_;\
	unsigned int __PP_2nd_Max_;\
	for (__PP_2nd_index_ = 0; __PP_2nd_index_ <= __PP_2nd_Max_; __PP_2nd_index_++)
	for (\
		PPCallVariableArgument(__PP_NameCompose, (__PP_Index_,__VA_ARGS__)) = 0;\
		PPLoopPair_T0_PPCallVariableArgument((__PP_Init,__VA_ARGS__)); \
		PPCallVariableArgument(__PP_NameCompose,(__PP_Index_,__VA_ARGS__))< PPCallVariableArgument(__PP_NameCompose,(__PP_Max_,__VA_ARGS__));\
		PPLoopOnce_T0_PPCallVariableArgument((IncreaseUntilMaxAndLoop,__VA_ARGS__)), \
		PPCallVariableArgument(__PP_NameCompose,(__PP_Index_,__VA_ARGS__)	)++)*/

#define PPLoopCombi(...) PPLoopAll(__VA_ARGS__)
#define PPLoopLeastOnce(...) PPLoopOnce(__VA_ARGS__)

#define PPLoop(Mode, ...) PPLoop##Mode##(__VA_ARGS__)


#define __PP_ArgumentCounter(...) __PP__ArgumentCounter_merge((__VA_ARGS__, 20, 19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))
#define __PP__ArgumentCounter_merge(VariableWithCount) __PP__ArgumentCounter_count VariableWithCount
#define __PP__ArgumentCounter_count(_1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, Count, ...) Count

#define __PP_ArgumentCounter_Min2(...) __PP__ArgumentCounter_merge((__VA_ARGS__, 20, 19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,2))



#define __PP_ArgumentCounterWithCall(Call, ...) __PP__ArgumentCounterWithCall_merge((Call, __VA_ARGS__, 20, 19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))
#define __PP__ArgumentCounterWithCall_merge(VariableWithCount) __PP__ArgumentCounterWithCall_count VariableWithCount
#define __PP__ArgumentCounterWithCall_count(Call, _1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, Count, ...) \
	Call##Count(_1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20)

//There is 2calls before parameter AppplyCallWithInput and Call so it start from 2
#define AppplyCallWithInput2(Call, v1, ...) Call##(v1)
#define AppplyCallWithInput3(Call, v1, v2, ...) AppplyCallWithInput2(Call, v1), AppplyCallWithInput2(Call, v2)
#define AppplyCallWithInput4(Call,v1,v2,v3, ...) AppplyCallWithInput3(Call,v1, v2), AppplyCallWithInput2(Call,v3)
#define AppplyCallWithInput5(Call,v1,v2,v3,v4, ...) AppplyCallWithInput4(Call,v1,v2,v3), AppplyCallWithInput2(Call,v4)
#define AppplyCallWithInput6(Call,v1,v2,v3,v4,v5, ...) AppplyCallWithInput5(Call,v1,v2,v3,v4), AppplyCallWithInput2(Call,v5)
#define AppplyCallWithInput7(Call,v1,v2,v3,v4,v5,v6, ...) AppplyCallWithInput6(Call,v1,v2,v3,v4,v5), AppplyCallWithInput2(Call,v6)
#define AppplyCallWithInput8(Call,v1,v2,v3,v4,v5,v6,v7, ...) AppplyCallWithInput7(Call,v1,v2,v3,v4,v5,v6), AppplyCallWithInput2(Call,v7)
#define AppplyCallWithInput9(Call,v1,v2,v3,v4,v5,v6,v7,v8, ...) AppplyCallWithInput8(Call,v1,v2,v3,v4,v5,v6,v7), AppplyCallWithInput2(Call,v8)
#define AppplyCallWithInput10(Call,v1,v2,v3,v4,v5,v6,v7,v8,v9, ...) AppplyCallWithInput9(Call,v1,v2,v3,v4,v5,v6,v7,v8), AppplyCallWithInput2(Call,v9)
#define AppplyCallWithInput11(Call,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10, ...) AppplyCallWithInput10(Call,v1,v2,v3,v4,v5,v6,v7,v8,v9), AppplyCallWithInput2(Call,v10)

#define AppplyCallWithInput(Call, ...)\
	AppplyCallWithInputProxy((AppplyCallWithInput, Call, __VA_ARGS__))
#define AppplyCallWithInputProxy(Parameter)	__PP_ArgumentCounterWithCall Parameter

#define __PP_MAX1(v1, ...) (v1)
#define __PP_MAX2(v1,v2, ...) ((v1>v2)?v1:v2)
#define __PP_MAX3(v1,v2,v3, ...) __PP_MAX2(__PP_MAX2(v1,v2),v3)
#define __PP_MAX4(v1,v2,v3,v4, ...) __PP_MAX2(__PP_MAX3(v1,v2,v3),v4)
#define __PP_MAX5(v1,v2,v3,v4,v5, ...) __PP_MAX2(__PP_MAX4(v1,v2,v3,v4),v5)
#define __PP_MAX6(v1,v2,v3,v4,v5,v6, ...) __PP_MAX2(__PP_MAX5(v1,v2,v3,v4,v5),v6)
#define __PP_MAX7(v1,v2,v3,v4,v5,v6,v7, ...) __PP_MAX2(__PP_MAX6(v1,v2,v3,v4,v5,v6),v7)
#define __PP_MAX8(v1,v2,v3,v4,v5,v6,v7,v8, ...) __PP_MAX2(__PP_MAX7(v1,v2,v3,v4,v5,v6,v7),v8)
#define __PP_MAX9(v1,v2,v3,v4,v5,v6,v7,v8,v9, ...) __PP_MAX2(__PP_MAX8(v1,v2,v3,v4,v5,v6,v7,v8),v9)
#define __PP_MAX10(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10, ...) __PP_MAX2(__PP_MAX9(v1,v2,v3,v4,v5,v6,v7,v8,v9),v10)
#define __PP_MAX(...)\
	__PP_ArgumentCounterWithCall(__PP_MAX, __VA_ARGS__)

#define __PP_NameCompose(...) __PP_NameCompose_ArgumentProxy((__VA_ARGS__, 20, 19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))
#define __PP_NameCompose_ArgumentProxy(VariableWithCount) __PP_NameCompose_Impl VariableWithCount
#define __PP_NameCompose_Impl(_1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, Count, ...) _1##_s_##_2##_s_##_3##_s_##_4##_s_##_5##_s_##_6##_s_##_7##_s_##_8##_s_##_9##_s_##_10##_s_##_11##_s_##_12##_s_##_13##_s_##_14##_s_##_15##_s_##_16##_s_##_17##_s_##_18##_s_##_19##_s_##_20


#define __PP_Init(Name) \
	Name=__PP_##Name##_Name_Original,\
	__PP_##Name##_From = __PP_##Name##_Name_Original,\
	__PP_##Name##_To = __PP_##Name##_Name_Original+__PP_##Name##_Count 

#define __PP_Init_With_Vector(Name, Initial_Vector) \
	Name=__PP_##Name##_Name_Original,\
	__PP_##Name##_From = __PP_##Name##_Name_Original+(Initial_Vector%__PP_StepCalculation(Name))*__PP_##Name##_By),\
	__PP_##Name##_To = __PP_##Name##_Name_Original+__PP_##Name##_Count 

#define IncreaseUntilMaxAndLoop(Name) \
	Name= \
	(((Name+=__PP_##Name##_By)>=__PP_##Name##_To)? __PP_##Name##_From:Name)


#define PPCallVariableArgument(Call, Argument) Call Argument
#define PPGetVariable(Name) (Name)

#define __PP_StepCalculation(v1) ((__PP_##v1##_Count+(__PP_##v1##_By-1))/__PP_##v1##_By)
#define __PP_MAX_WithCount1(v1, ...) __PP_StepCalculation(v1)
#define __PP_MAX_WithCount2(v1,v2, ...) ((__PP_StepCalculation(v1)>__PP_StepCalculation(v2))\
	? __PP_StepCalculation(v1) : __PP_StepCalculation(v2))
#define __PP_MAX_WithCount3(v1,v2,v3, ...) __PP_MAX2(__PP_MAX_WithCount2(v1,v2),__PP_StepCalculation(v3))
#define __PP_MAX_WithCount4(v1,v2,v3,v4, ...) __PP_MAX2(__PP_MAX_WithCount3(v1,v2,v3),__PP_StepCalculation(v4))
#define __PP_MAX_WithCount5(v1,v2,v3,v4,v5, ...) __PP_MAX2(__PP_MAX_WithCount4(v1,v2,v3,v4),__PP_StepCalculation(v5))
#define __PP_MAX_WithCount6(v1,v2,v3,v4,v5,v6, ...) __PP_MAX2(__PP_MAX_WithCount5(v1,v2,v3,v4,v5),__PP_StepCalculation(v6))
#define __PP_MAX_WithCount7(v1,v2,v3,v4,v5,v6,v7, ...) __PP_MAX2(__PP_MAX_WithCount6(v1,v2,v3,v4,v5,v6),__PP_StepCalculation(v7))
#define __PP_MAX_WithCount8(v1,v2,v3,v4,v5,v6,v7,v8, ...) __PP_MAX2(__PP_MAX_WithCount7(v1,v2,v3,v4,v5,v6,v7),__PP_StepCalculation(v8))
#define __PP_MAX_WithCount9(v1,v2,v3,v4,v5,v6,v7,v8,v9, ...) __PP_MAX2(__PP_MAX_WithCount8(v1,v2,v3,v4,v5,v6,v7,v8),__PP_StepCalculation(v9))
#define __PP_MAX_WithCount10(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10, ...) __PP_MAX2(__PP_MAX_WithCount9(v1,v2,v3,v4,v5,v6,v7,v8,v9),__PP_StepCalculation(v10))
#define __PP_MAX_WithCount(...)\
	__PP_ArgumentCounterWithCall(__PP_MAX_WithCount, __VA_ARGS__)



/*



#define PPRule(name, function_name, ...) \
function_name##_type name_rule[] = {{function_name, __VA_ARGS__}};
#define PPRuleTable(name, ...) \
rule_type name_rule_table_type[] = {__VA_ARGS__} \
*/

#endif //_PhotonParameterizedTest_h_
