#ifndef _self_documentation_test_
#define _self_documentation_test_

#include "PP.h"
#include "PhotonMock.h"


#define _BDD_GET_SIZE  0
#define _BDD_GET_INDEX 1
#define _BDD_EXECUTE_SELECTED 2
#define _BDD_EXECUTE_ALL 3

//#define WITH_DOC_GENERATION_CODE


#ifdef WITH_DOC_GENERATION_CODE
enum {
	TYPE_It_return_,
	TYPE_when_it_
};
void __BDD_Append_log(int type, char* one, char* two);
#endif

#define Expect_equal_(Expected, Actual) if (Expected != Actual) while(1);
#define Expect_(Expression) if (!(Expression)) while(1);

#define __BDD_Call(Function, Parameter) Function Parameter

#define __BDD_Append0(...) ""
#define __BDD_Append1(desc, ...) #desc
#define __BDD_Append2(_1, _2, ...) #_1 " " #_2
#define __BDD_Append3(_1, _2, _3, ...) #_1 " " #_2 " " #_3
#define __BDD_Append4(_1, _2, _3, _4, ...) #_1 " " #_2 " " #_3 "" #_4
#define __BDD_Append5(_1, _2, _3, _4, _5, ...) #_1 " " #_2 " " #_3 " " #_4 " " #_5 
#define __BDD_Append6(_1, _2, _3, _4, _5, _6, ...) #_1 " " #_2 " " #_3 " " #_4 " " #_5 " " #_6 
#define __BDD_Append7(_1, _2, _3, _4, _5, _6, _7, ...) #_1 " " #_2 " " #_3 " " #_4 " " #_5 " " #_6 " " #_7 
#define __BDD_Append8(_1, _2, _3, _4, _5, _6, _7, _8, ...) #_1 " " #_2 " " #_3 " " #_4 " " #_5 " " #_6 " " #_7 " " #_8
#define __BDD_Append9(_1, _2, _3, _4, _5, _6, _7, _8, _9, ...) #_1 " " #_2 " " #_3 " " #_4 " " #_5 " " #_6 " " #_7 " " #_8 " " #_9
#define __BDD_Append10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...)  #_1 " " #_2 " " #_3 " " #_4 " " #_5 " " #_6 " " #_7 " " #_8 " " #_9 " " #_10

#define Description(...) char* __BDD_description = __BDD_ArgumentCounterWithCall(__BDD_Append, __VA_ARGS__);
//#define Description(desc) __BDD_Description(desc);
//void __BDD_Description(char* desc) {
//}

#define AppplyCallWithInput(Call, ...)\
	AppplyCallWithInputProxy((AppplyCallWithInput, Call, __VA_ARGS__))
#define AppplyCallWithInputProxy(Parameter)	__PP_ArgumentCounterWithCall Parameter
//char* __BDD_description = desc;

typedef struct {
	int scenario_mode;
	int* scenario_current_index;
	int* scenario_target_index;
	int* scenario_target_size;
	int scenario_current_index_temp;
	int scenario_target_index_temp;
	int scenario_target_size_temp;
	char** scenario_target_names;
	int* scenario_target_name_remain;
}__BDD_Context; 


#define __BDD_group_(__BDD_group_name) void __BDD_group_name(int scenario_mode, int* scenario_current_index, int* scenario_target_index, int* scenario_target_size, int scenario_current_index_temp, int scenario_target_index_temp, int scenario_target_size_temp,\
	char** scenario_target_names, int* scenario_target_name_remain)

/*currently nothing*/
#define __BDD_groups_(__BDD_group_name) if(1) 


#define __BDD_ArgumentCounterWithCall(Call, ...) __BDD_ArgumentCounterWithCall_merge((Call, __VA_ARGS__, 20, 19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
#define __BDD_ArgumentCounterWithCall_merge(VariableWithCount) __BDD_ArgumentCounterWithCall_count VariableWithCount
#define __BDD_ArgumentCounterWithCall_count(Call, _1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, Count, ...) \
	Call##Count(_1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20)




/*
Feature(xxxx) {
	Description(
		"xxxxx",
		"YYYY") 
	
	Given(
		AVariable(int, i), //a_(type, i)
		ASet(int, x)) { //a_set_(

		The_(i is 3);
		The_list_(XX is 1,,2 by 1);//, By(2));
		The_list_(XX is 1,,2);
		//Setup()
	}
	 Pre(1) Post(2) {
	 // Scenario (fly, combination_of, wing, motor) 
		Description(
		"xxxxx",
		"YYYY") 
		 Given() {
		 }
		//When_I_ask_(bird.fly, X, T) exepect_return_(3) {
			//And_it_(fly, ....)
			//And_()
		//end
	 end

}

Feature(xxxx) {
	Description(xxxxx)
	Given(Variable( x, int), int*, y
}

*/


#define __BDD_SeparateStatement1(_1, ...) ,_1
#define __BDD_SeparateStatement2(_1, ...) ,_1 __BDD_SeparateStatement1(__VA_ARGS__)
#define __BDD_SeparateStatement3(_1, ...) ,_1 __BDD_SeparateStatement2(__VA_ARGS__)
#define __BDD_SeparateStatement4(_1, ...) ,_1 __BDD_SeparateStatement3(__VA_ARGS__)
#define __BDD_SeparateStatement5(_1, ...) ,_1 __BDD_SeparateStatement4(__VA_ARGS__)
#define __BDD_SeparateStatement6(_1, ...) ,_1 __BDD_SeparateStatement5(__VA_ARGS__)
#define __BDD_SeparateStatement7(_1, ...) ,_1 __BDD_SeparateStatement6(__VA_ARGS__)
#define __BDD_SeparateStatement8(_1, ...) ,_1 __BDD_SeparateStatement7(__VA_ARGS__)
#define __BDD_SeparateStatement9(_1, ...) ,_1 __BDD_SeparateStatement8(__VA_ARGS__)
#define __BDD_SeparateStatement10(_1, ...) ,_1 __BDD_SeparateStatement9(__VA_ARGS__)
#define __BDD_SeparateStatement11(_1, ...) ,_1 __BDD_SeparateStatement10(__VA_ARGS__)
#define __BDD_SeparateStatement12(_1, ...) ,_1 __BDD_SeparateStatement11(__VA_ARGS__)
#define __BDD_SeparateStatement13(_1, ...) ,_1 __BDD_SeparateStatement12(__VA_ARGS__)
#define __BDD_SeparateStatement14(_1, ...) ,_1 __BDD_SeparateStatement13(__VA_ARGS__)
#define __BDD_SeparateStatement15(_1, ...) ,_1 __BDD_SeparateStatement14(__VA_ARGS__)
#define __BDD_SeparateStatement16(_1, ...) ,_1 __BDD_SeparateStatement15(__VA_ARGS__)
#define __BDD_SeparateStatement17(_1, ...) ,_1 __BDD_SeparateStatement16(__VA_ARGS__)
#define __BDD_SeparateStatement18(_1, ...) ,_1 __BDD_SeparateStatement17(__VA_ARGS__)
#define __BDD_SeparateStatement19(_1, ...) ,_1 __BDD_SeparateStatement18(__VA_ARGS__)
#define __BDD_SeparateStatement20(_1, ...) ,_1 __BDD_SeparateStatement19(__VA_ARGS__)
#define Given() 
#define Setup() if(1)
#define Cleanup() if(1)
#define A_(...) __VA_ARGS__ 
#define An_(...) __VA_ARGS__

#define MAX_INT 0xFFFFFFFF
#define A_list_Parameter2(Type, Name, ...) PPListBy(Type, Name, 1, 1, 1, MAX_INT)
#define A_list_Parameter5(Type, Name, From, Dummy, To, ...) PPList(Type, Name, From, Dummy, To)
#define A_list_Parameter6(Type, Name, From, Dummy, To, By, ...) PPListBy(Type, Name, From, Dummy, To, By)
#define A_list_(...)  __BDD_ArgumentCounterWithCall(A_list_Parameter, __VA_ARGS__)

#define The_list_Parameter1(Name, ...) The_list_Parameter5(Name, 1, 1, 1)
#define The_list_Parameter4(Name, From, Dummy, To, ...) The_list_Parameter5(Name, From, Dummy, To, 1)
#define The_list_Parameter5(Name, From, Dummy, To, By, ...) \
	if (__PP_##Name##_By == MAX_INT) {\
		__PP_##Name##_Name_Original = From;\
		Name = From;\
		__PP_##Name##_Kind= PPListKind;\
		__PP_##Name##_Count = To-From+1;\
		__PP_##Name##_From = From;\
		__PP_##Name##_To = To+1; /*Exclusive*/\
		__PP_##Name##_By = By;\
	}

#define The_list_(...)  __BDD_ArgumentCounterWithCall(The_list_Parameter, __VA_ARGS__)

#define A_set__(parameter) PPSet parameter
#define A_set_(...) A_set__((__VA_ARGS__))


#define The_set_(Type, Name, ...)\
	if (__PP_##Name##_Name_Original == __PP_##Name##_Name_Original_) {\
		__PP_##Name##_Type __PP_##Name##_Name_Original2[] = {__VA_ARGS__};\
		__PP_##Name##_Name_Original = __PP_##Name##_Name_Original2;\
		Name = __PP_##Name##_Name_Original;\
		__PP_##Name##_Count = (__PP_ArgumentCounter(__VA_ARGS__));\
		__PP_##Name##_From = __PP_##Name##_Name_Original,\
		__PP_##Name##_To = __PP_##Name##_Name_Original+__PP_##Name##_Count; \
	}
#define is ,
#define by ,


#define Scenario_Parameter_1(ScenarioName, ...)
// 2paremeter is not exist if it is then it is bug
#define Scenario_Parameter_3(ScenarioName, Mode, v1, ...) __BDD_Loop(Mode, v1)
#define Scenario_Parameter_4(ScenarioName, Mode, v1, v2, ...) __BDD_Loop(Mode, v1, v2)
#define Scenario_Parameter_5(ScenarioName, Mode, v1, v2, v3, ...) __BDD_Loop(Mode, v1, v2, v3)
#define Scenario_Parameter_6(ScenarioName, Mode, v1, v2, v3, v4, ...) __BDD_Loop(Mode, v1, v2, v3, v4)
#define Scenario_Parameter_7(ScenarioName, Mode, v1, v2, v3, v4, v5, ...) __BDD_Loop(Mode, v1, v2, v3, v4, v5)
#define Scenario_Parameter_8(ScenarioName, Mode, v1, v2, v3, v4, v5, v6, ...) __BDD_Loop(Mode,  v1, v2, v3, v4, v5, v6)
#define Scenario_Parameter_9(ScenarioName, Mode, v1, v2, v3, v4, v5, v6, v7, ...) __BDD_Loop(Mode, v1, v2, v3, v4, v5, v6, v7)
#define Scenario_Parameter_10(ScenarioName, Mode, v1, v2, v3, v4, v5, v6, v7, v8, ...) __BDD_Loop(Mode, v1, v2, v3, v4, v5, v6, v7, v8)
#define Scenario_Parameter_11(ScenarioName, Mode, v1, v2, v3, v4, v5, v6, v7, v8, v9, ...) __BDD_Loop(Mode, v1, v2, v3, v4, v5, v6, v7, v8, v9)
#define Scenario_Parameter_12(ScenarioName, Mode, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, ...) __BDD_Loop(Mode,  v1, v2, v3, v4, v5, v6, v7, v8, v9, v10)

#define Scenario(...) if (_BDD_scenario_preprocessor(scenario_mode, scenario_current_index, scenario_target_index, scenario_target_size, \
		scenario_target_names, scenario_target_name_remain, __BDD_ArgumentCounterWithCall(__BDD_Append, __VA_ARGS__))) __BDD_ArgumentCounterWithCall(Scenario_Parameter_, __VA_ARGS__)

#define __BDD_pick_first(first, ...) first

#ifndef WITH_DOC_GENERATION_CODE
#define __BDD_Include_(__BDD_group_name, ...) \
	if (_BDD_group_preprocessor(scenario_mode, scenario_current_index, scenario_target_index, scenario_target_size, \
			scenario_target_names, scenario_target_name_remain, __BDD_ArgumentCounterWithCall(__BDD_Append, __VA_ARGS__))) __BDD_ArgumentCounterWithCall(Scenario_Parameter_, __VA_ARGS__) {\
		if (scenario_mode == _BDD_GET_INDEX) {\
			scenario_target_index_temp=0;\
			if(scenario_target_name_remain)__BDD_pick_first(__VA_ARGS__)(scenario_mode, &scenario_target_index_temp, scenario_target_index+1, scenario_target_size, 0, 0, 0, scenario_target_names+1, scenario_target_name_remain-1);\
		} else {\
			__BDD_pick_first(__VA_ARGS__)(scenario_mode, &scenario_current_index_temp, scenario_target_index+1, scenario_target_size, 0, 0, 0, (scenario_target_name_remain && (scenario_target_names!=0)) ? scenario_target_names+1 : 0,  (scenario_target_name_remain) ? scenario_target_name_remain-1 : 0);\
		}\
	}
#else
#define __BDD_Include_(__BDD_group_name, ...) __BDD_Append_log_##__BDD_group_name(__BDD_ArgumentCounterWithCall(__BDD_Append, __VA_ARGS__));\
	if (_BDD_group_preprocessor(scenario_mode, scenario_current_index, scenario_target_index, scenario_target_size, \
			scenario_target_names, scenario_target_name_remain, __BDD_ArgumentCounterWithCall(__BDD_Append, __VA_ARGS__))) __BDD_ArgumentCounterWithCall(Scenario_Parameter_, __VA_ARGS__) {\
		if (scenario_mode == _BDD_GET_INDEX) {\
			scenario_target_index_temp=0;\
			if(scenario_target_name_remain)__BDD_pick_first(__VA_ARGS__)(scenario_mode, &scenario_target_index_temp, scenario_target_index+1, scenario_target_size, 0, 0, 0, scenario_target_names+1, scenario_target_name_remain-1);\
		} else {\
			__BDD_pick_first(__VA_ARGS__)(scenario_mode, &scenario_current_index_temp, scenario_target_index+1, scenario_target_size, 0, 0, 0, (scenario_target_name_remain && (scenario_target_names!=0)) ? scenario_target_names+1 : 0,  (scenario_target_name_remain) ? scenario_target_name_remain-1 : 0);\
		}\
	}
#endif

#ifndef WITH_DOC_GENERATION_CODE
#define __BDD_new_group_(__BDD_group_name) int __BDD_group_name##id
#else
#define __BDD_new_group_(__BDD_group_name) void __BDD_Append_log_##__BDD_group_name(char* includedFeature){__BDD_Documentation_log(#__BDD_group_name);} int __BDD_group_name##id
#endif

#ifndef WITH_DOC_GENERATION_CODE
#define __BDD_new_group_Declare(__BDD_group_name) extern int __BDD_group_name##id
#else
#define __BDD_new_group_Declare(__BDD_group_name) void __BDD_Append_log_##__BDD_group_name(char* includedFeature); extern int __BDD_group_name##id
#endif

#define __BDD_init_group_(__BDD_group_name) __BDD_group_currentID<<=1;__BDD_group_name##id = __BDD_group_currentID

void __BDD_Global_Init(void);

extern unsigned int __BDD_Index_;
extern unsigned int __BDD_Max_;

#define __BDD_Loop_with_each_of(...) \
	__BDD_Index_ = 0;\
	__BDD_Max_ = __PP_MAX_WithCount(__VA_ARGS__);\
	for (\
		PPLoopOnce_T0_PPCallVariableArgument((__PP_Init,__VA_ARGS__)); \
		__BDD_Index_< __BDD_Max_;\
		PPLoopOnce_T0_PPCallVariableArgument((IncreaseUntilMaxAndLoop,__VA_ARGS__)), \
		__BDD_Index_++)

#define __BDD_Loop(Mode, ...) __BDD_Loop_##Mode(__VA_ARGS__)


#define __BDD_Loop_with_combination_of(...) PPLoopAll(__VA_ARGS__)


//#define PPTable(Name, Type, ...)
//#define __PP_PPTable_OnlyDeclare(Name, Type, ...)

#define A_table_Parameter2(Name, Type, ...) __PP_PPTable_OnlyDeclare(Name, Type)
#define A_table_Parameter3(Name, Type, v1, ...) PPTable(Name, Type, v1)
#define  A_table_Parameter4(Name, Type, v1,v2, ...) \
					PPTable(Name, Type, v1,v2)
#define  A_table_Parameter5(Name, Type, v1,v2, v3, ...) \
					PPTable(Name, Type, v1,v2, v3)
#define  A_table_Parameter6(Name, Type, v1,v2, v3, v4, ...) \
					PPTable(Name, Type, v1,v2, v3, v4)
#define  A_table_Parameter7(Name, Type, v1,v2, v3, v4, v5, ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5)
#define  A_table_Parameter8(Name, Type, v1,v2, v3, v4, v5, v6,  ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6)
#define  A_table_Parameter9(Name, Type, v1,v2, v3, v4, v5, v6, v7,  ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7)
#define A_table_Parameter10(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8,  ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8)
#define A_table_Parameter11(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9,  ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9)
#define A_table_Parameter12(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,  ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10)
#define A_table_Parameter13(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11, ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11)
#define A_table_Parameter14(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12, ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12)
#define A_table_Parameter15(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13, ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13)
#define A_table_Parameter16(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14, ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14)
#define A_table_Parameter17(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15, ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15)
#define A_table_Parameter18(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15,v16, ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15,v16)
#define A_table_Parameter19(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15,v16,v17, ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15,v16,v17)
#define A_table_Parameter20(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15,v16,v17,v18, ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15,v16,v17,v18)
#define A_table_Parameter21(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15,v16,v17,v18,v19, ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15,v16,v17,v18,v19)
#define A_table_Parameter22(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20, ...) \
					PPTable(Name, Type, v1,v2, v3, v4, v5, v6, v7, v8, v9, v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20)

#define A_table_(...)  __BDD_ArgumentCounterWithCall(A_table_Parameter,__VA_ARGS__)



#define The_table_(Name, Type, ...)\
	if (__PP_##Name##_Name_Original == __PP_##Name##_Name_Original_) {\
		__PP_##Name##_Type __PP_##Name##_Name_Original2[] = {__VA_ARGS__};\
		__PP_##Name##_Name_Original = __PP_##Name##_Name_Original2;\
		Name = __PP_##Name##_Name_Original;\
		__PP_##Name##_Count = (sizeof(__PP_##Name##_Name_Original2)/sizeof(__PP_##Name##_Type));\
		__PP_##Name##_From = __PP_##Name##_Name_Original,\
		__PP_##Name##_To = __PP_##Name##_Name_Original+__PP_##Name##_Count; \
	}





int __BDD_When_Counter;

////////////////////////////////////////////////////////
typedef void (*void_function)(void);
extern void_function __BDD_When_Before; 
extern void_function __BDD_When_After;
void _BDD_init(void);
////////////////////////////////////////////////////////

#define __BDD_When_Compare(Result, Comparator, Expected) ()
#define When_it_(Name, ...) for (__BDD_When_Counter=0,__BDD_When_Before();__BDD_When_Counter==0;__BDD_When_Counter++,\
	__BDD_When_After(), Name(__VA_ARGS__), __BDD_When_After())

//#define it_should_return_(Expected) == Expected, __BDD_When_After())
//#define it_should() , __BDD_When_After())

//Result_(is,10,cm,when_it_(jump)) which {
//	May_it_(tired);
//  May_(ground, makeSound);
//}

#ifndef WITH_DOC_GENERATION_CODE
#define It_return_(...) ___It_return_((__VA_ARGS__,3,2,1))
#define ___It_return_(...) __It_return_ __VA_ARGS__
#define __It_return_(_1,_2,_3,count, ...) _It_return_##count##(_1,_2,_3)
#define _It_return_2(value, comparator, _) for (__BDD_When_Counter=0,__BDD_When_Before();__BDD_When_Counter==0;__BDD_When_Counter++,\
	comparator ( value , 
#define _It_return_3(equality, value, comparator) for (__BDD_When_Counter=0,__BDD_When_Before();__BDD_When_Counter==0;__BDD_When_Counter++,\
	equality comparator ( value , 
#define when_it_(Name, ...)  Name(__VA_ARGS__)), __BDD_When_After())
#else 
#define It_return_(...) ___It_return_((__VA_ARGS__,3,2,1))
#define ___It_return_(...) __It_return_ __VA_ARGS__
#define __It_return_(_1,_2,_3,count, ...) _It_return_##count##(_1,_2,_3)
#define _It_return_2(value, comparator, _) __BDD_Append_log(TYPE_It_return_, #comparator, #value); for (__BDD_When_Counter=0,__BDD_When_Before();__BDD_When_Counter==0;__BDD_When_Counter++,\
	comparator ( value , 
#define _It_return_3(equality, value, comparator, _) __BDD_Append_log(TYPE_It_return_, #comparator, #value); for (__BDD_When_Counter=0,__BDD_When_Before();__BDD_When_Counter==0;__BDD_When_Counter++,\
	equality comparator ( value , 
#define when_it_(Name, ...)  Name(__VA_ARGS__)), \
	__BDD_Append_log(TYPE_when_it_, #Name, __BDD_ArgumentCounterWithCall(__BDD_Append, __VA_ARGS__) ), __BDD_When_After())
#endif

#define less_than 0 >
#define less_than_or_equal_to 0 >=
#define greater_than 0 <
#define greater_than_or_equal_to 0 <=

#define which_cause
#define it_cause

#define And_it_(...) PMWillCall(__VA_ARGS__)
#define And_when_it_(requested_function, actually_called_function) PMWillForward(requested_function, actually_called_function)
#define it_(function) function
#define times_(...) PMTimes(__VA_ARGS__)

#define _(value, type) PMEq(type, value)
#define not_(value, type) PMNotEq(type, value)
#define any_(type) PMAny(type, value)
#define return_(value, type) PMSet(type, value)

#define then_return_(value, type) PMReturn(type, value)

#define Application_may_(...) PMMockDeclare(__VA_ARGS__)
#define It_may_(...) PMMock(__VA_ARGS__)
#define There_is_type_(type) __PM_Parameter(type)
#define Used_type_is_(type) __PM_ParameterDeclare(type)
#define and_return_type_of_(type) type
//#define May_(bird, fly,...)

// It_return_(3) when_it_(name,...)
// I_expect_return_(integer, 3) after
// I_expect_return_(integer_less_than, 3) after
/////////////////////////////////////////////////////////

int _BDD_scenario_preprocessor(int scenario_mode, int* scenario_current_index, int* scenario_target_index, int* scenario_target_size,
		char** scenario_target_names, int* scenario_target_name_remain,  char* scenario_current_name);

int _BDD_group_preprocessor(int scenario_mode, int* scenario_current_index, int* scenario_target_index, int* scenario_target_size,
		char** scenario_target_names, int* scenario_target_name_remain, char* scenario_current_name);

int stringCompare(char* source, char* target);

//== Application ==
#define ApplicationDeclare(Name) extern void Name(void);
#define Application(Name) int scenario_mode;\
char* _scenario_target_names[] = {""}; \
int _scenario_current_index=0;\
int _scenario_target_index=0;\
int _scenario_target_size=0;\
int _scenario_target_name_remain=0;\
int* scenario_current_index;\
int* scenario_target_index;\
int* scenario_target_size;\
char** scenario_target_names;\
int* scenario_target_name_remain;\
int scenario_current_index_temp = 0,scenario_target_index_temp = 0, scenario_target_size_temp = 0;\
void _##Name(int scenario_mode, int* scenario_current_index, int* scenario_target_index, int* scenario_target_size, int scenario_current_index_temp, int scenario_target_index_temp, int scenario_target_size_temp,\
		char** scenario_target_names, int* scenario_target_name_remain);\
void Name(void) {\
	scenario_mode = _BDD_EXECUTE_ALL;\
	scenario_current_index= &_scenario_current_index;\
	scenario_target_index= &_scenario_target_index;\
	scenario_target_size= &_scenario_target_size;\
	scenario_target_names= _scenario_target_names;\
	scenario_target_name_remain= &_scenario_target_name_remain;\
	_##Name(scenario_mode, scenario_current_index, scenario_target_index, scenario_target_size, scenario_current_index_temp, scenario_target_index_temp, scenario_target_size_temp, scenario_target_names,  scenario_target_name_remain);\
	__BDD_Global_Init();\
}\
void _##Name(int scenario_mode, int* scenario_current_index, int* scenario_target_index, int* scenario_target_size, int scenario_current_index_temp, int scenario_target_index_temp, int scenario_target_size_temp,\
		char** scenario_target_names, int* scenario_target_name_remain)

//== Documentation ==

void __BDD_Documentation_log(char* log);


//== Feature Group ==
#define Include_feature_(...) __BDD_Include_(Feature, __VA_ARGS__)
#define Feature __BDD_group_
#define Features() __BDD_groups_(Features)
__BDD_new_group_Declare(Feature);

//== Component Group ==
#define Include_component_(...) __BDD_Include_(Component, __VA_ARGS__)
#define Component __BDD_group_
#define Components() __BDD_groups_(Components)
__BDD_new_group_Declare(Component);

/*
Feature(Scenario_two) {
		Description("xxxxx"
					"YYYY")
		Given()
			A_list_(int, tail)
				A_list_(int, leg)
		PPList(int, wing , 2,,3 )
		PPList(int, motor , 2,,3)
		Scenario (fly, with_combination_of, wing, motor, tail) {
			//PPList(int, tail , 2,,3 )
		}
		Scenario (fly, with_combination_of, wing, motor, leg) {
			//PPList(int, leg , 2,,3 )
		}
}

=======================
FeatureSet (Name
	, Feature1
	, Feature2) 
>> 
Feature1();
Feature2();
void Feature_##Name() {
	Feature1();
	Feature2();
}
=======================
*/
		//expect {
		//expect_retur_(odd_and_less_then, 3)>>> call2(target, odd_and_less_then , data)>>odd_and_less_then(target,data)
		//expect_retur_(odd_and_less_then_3)>>> call1(target, odd_and_less_then_3 )>> odd_and_less_then_3(target)
		//exepect_return_less_then_(3)
		//When_I_ask_(bird.fly, X, T) exepect_return_(3) {
		//When_I_ask_kind_of_(bird.fly, X, T) exepect_return_(3) {
		//When_I_ask_it_(fly, X, T) exepect_return_(3) {
			//And_it_(fly, ....)
			//And_()
			//And_kind_of_()
			//And_privately()
		//end

#endif //_self_documentation_test_