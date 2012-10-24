
#ifndef __PHOTON_MOCK_H__
#define __PHOTON_MOCK_H__
 
///////////////////////////////////////////////////////////////
// Variable Defines
#define X86
//#define ARM_THUMB2

extern void (*PM_AssertFunction)(int boolean_value);

void __PM_Assert(int boolean_value);
void __PM_Check_To_Pause_Or_Set_Flag(int boolean_value);

#define __PM_STACK_SIZE 1024
#define __PM_INSTRUMENT_REPOSITORY_SIZE 20
#define __PM_INSTRUMENT_SIZE 20
#ifdef X86
#define __PM_INSTRUMENT_WHOLE_INSTRUCTION_SIZE 7
#endif
#ifdef  ARM
#define __PM_INSTRUMENT_WHOLE_INSTRUCTION_SIZE 4
#endif
#ifdef  ARM_THUMB2
#define __PM_INSTRUMENT_WHOLE_INSTRUCTION_SIZE 30
#endif
#define __PM_ANY_DUMMY_SIZE 8

#define __PM_Parameter_Type 1
#define __PM_MockRecord_Type 2
#define __PM_UniversalMock_Type 3
#define __PM_Instrument_Type 4

#define __PM_INSTRUMENT_DUPLICATE_ERROR 1
#define __PM_INSTRUMENT_OK 0


#define __PM_SAME 0
#define __PM_SUCCESS 1
#define __PM_FAIL 0

#define __PM_MAX_INT 2147483648-1

typedef unsigned char byte;

#define __PM_MAKE_FUNCTION_MOCKABLE __PM_Dummy_Operation(1);__PM_Dummy_Operation(1);__PM_Dummy_Operation(1);__PM_Dummy_Operation(1);
void __PM_Dummy_Operation(int i);



///////////////////////////////////////////////////////////////
// PM_Node
typedef struct {
	int child_count;
	int type;
	int size_include_children;
	int size;
}__PM_Meta;
#define __PM_Node_new(node_type, child_count) __PM_Node_new_(sizeof(node_type), node_type##_Type, child_count)
__PM_Meta* __PM_Node_new_(int node_size, int node_type, int child_count) ;
byte* __PM_Node_get_data(__PM_Meta* node);
__PM_Meta* __PM_Node_get_child(__PM_Meta* parent);
__PM_Meta* __PM_Node_get_sible(__PM_Meta* target); 



///////////////////////////////////////////////////////////////
// PM_Stack
typedef struct __PM_Stack {
	byte* current_location;
	byte data[__PM_STACK_SIZE];
} __PM_Stack;
__PM_Stack* __PM_Stack_get_instance(void);
void __PM_Stack_clean(void);
#define __PM_Stack_add(stack, data, data_type, child_count)  __PM_Stack_add_(stack, (byte*)data, sizeof(*data), data_type, child_count)
byte* __PM_Stack_add_(__PM_Stack* stack, byte* node, int node_size, int node_type, int child_count);
__PM_Meta* __PM_Stack_get_last_meta(__PM_Stack* stack);



///////////////////////////////////////////////////////////////
// PM_MockRecord
typedef struct __PM_MockRecord {
	void* from;
	void* to;
	int min_times;
	int max_times;
	int called;
	int is_return_set;
	int is_forward;
	__PM_Meta meta;
} __PM_MockRecord;
__PM_MockRecord* __PM_MockRecord_new(void* from, void* to, int min_times, int max_times, int child_count, int is_resturn_set, int is_forward) ;



///////////////////////////////////////////////////////////////
// PM_Link
void PM_Link_push(int link) ;
int PM_Link_pop(void) ;
void PM_Link_clean(void);

///////////////////////////////////////////////////////////////
// PM_Instrument
typedef struct __PM_Instrument {
	int originally_little_endian;
	int little_endian;
	int instruction_include_address_size;
	int instruction_address_size;
	int instruction_size;
	int address_location;
	byte* address_mask;
	int address_shift_right;
	int pc_and_current_difference;
	int is_64bit;
	byte* instruction;
	void* from[__PM_INSTRUMENT_SIZE];
	void* to[__PM_INSTRUMENT_SIZE];
	byte from_backup[__PM_INSTRUMENT_SIZE][__PM_INSTRUMENT_WHOLE_INSTRUCTION_SIZE];
	byte from_backup_for_redo[__PM_INSTRUMENT_SIZE][__PM_INSTRUMENT_WHOLE_INSTRUCTION_SIZE];
	int from_to_current;
	__PM_Meta meta;
} __PM_Instrument;
__PM_Instrument* __PM_Instrument_get_instance(void);
void __PM_Instrument_clean(void);
int __PM_Instrument_do(void* from , void* to) ;
void __PM_Instrument_undo(void* from);
void __PM_Instrument_redo(void* from);

///////////////////////////////////////////////////////////////
// Argument counting macro
#define __PM_First(f, ...) f
#define __PM_NotFirst(f, ...) __VA_ARGS__
#define __PM_ArgumentCounter(...) __PM__ArgumentCounter_merge((__VA_ARGS__, 23, 22, 21, 20, 19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))
#define __PM__ArgumentCounter_merge(VariableWithCount) __PM__ArgumentCounter_count VariableWithCount
#define __PM__ArgumentCounter_count(_1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23, Count, ...) Count

#define __PM_ArgumentCounterWithCall( ...) __PM__ArgumentCounterWithCall_merge(( __VA_ARGS__, 23,22,21,20, 19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))
#define __PM__ArgumentCounterWithCall_merge(VariableWithCount) __PM__ArgumentCounterWithCall_count VariableWithCount
#define __PM__ArgumentCounterWithCall_count(Call, _1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23, Count, ...) \
	Call##Count(_1, _2, _3, _4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23)

///////////////////////////////////////////////////////////////
// PM_Parameter_header
typedef int (*__PM_Parameter_consume)(void* parameter, void* input);
typedef int (*__PM_Parameter_operate)(void* parameter, void* input);
typedef struct __PM_Parameter_header {
	int child_count;\
	__PM_Parameter_consume consume;\
	__PM_Parameter_operate operate;\
} __PM_Parameter_header;

__PM_Parameter_header* __PM_Parameter_new(int parameter_size, __PM_Parameter_consume consume, __PM_Parameter_operate operate, int child_count);
__PM_Parameter_header* __PM_Parameter_new_(int parameter_size, __PM_Parameter_consume consume, __PM_Parameter_operate operate, void* input,int input_size, int child_count) ;


///////////////////////////////////////////////////////////////
// Parameter
extern byte __PM_any_dummy[__PM_ANY_DUMMY_SIZE];
#define __PM_ParameterAny_new(type, input)  __PM_Parameter_new_##type(sizeof(__PM_Parameter_##type), &__PM_ParameterAny_consume, &__PM_ParameterAny_operate, input, sizeof(type), 0)
int __PM_ParameterAny_consume(void* parameter, void* input);
int __PM_ParameterAny_operate(void* parameter, void* input);

#define __PM_ParameterSet_new(type, input)  (&input,__PM_Parameter_new_##type(sizeof(__PM_Parameter_##type), &__PM_ParameterSet_consume, &__PM_ParameterSet_operate, input, sizeof(type), 0))
int __PM_ParameterSet_consume(void* parameter, void* input);
int __PM_ParameterSet_operate(void* parameter, void* input);

#define __PM_ParameterReturn_new(type, input)  __PM_Parameter_new_##type(sizeof(__PM_Parameter_##type), &__PM_ParameterReturn_consume, &__PM_ParameterReturn_operate, input, sizeof(type), 0)
int __PM_ParameterReturn_consume(void* parameter, void* input);
int __PM_ParameterReturn_operate(void* parameter, void* input);

#define __PM_ParameterEq_new(type, input)  __PM_Parameter_new_##type(sizeof(__PM_Parameter_##type), &__PM_ParameterEq_consume, &__PM_ParameterEq_operate, input, sizeof(type), 0)
int __PM_ParameterEq_consume(void* parameter, void* input);
int __PM_ParameterEq_operate(void* parameter, void* input);

///////////////////////////////////////////////////////////////
// mocking function
void _PMWillCall(void* called_object, void* original_function, void* forward_function,int defined_parameter_count, int count, ...)  ;
void _PMWillCallWithoutInstrument(void* called_object, void* original_function, void* forward_function,int defined_parameter_count, int count, ...)  ;
void __PMTimes_(int min, int max);

///////////////////////////////////////////////////////////////
// PM_UniveralMock
void __PM_UniveralMock_process(void* parameter_data) ;

#define __PM_UniveralMock_check_consume() __PM_Assert(__PM_UniveralMock_check_consume_())
int __PM_UniveralMock_check_consume_(void) ;

typedef struct _mock_function_paremeter_header_type_template {
	int total_size;
	int field_count;
	void* called_object;
	void* function;
	void* field_reference[11];
}_mock_function_paremeter_header_type_template;

#define __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE 0

///////////////////////////////////////////////////////////////
// private function for public interface
void _PMInit(void);
void _PMVerify(void);
///////////////////////////////////////////////////////////////
// Public Interface
#define __PM_Parameter(type) \
type __PM_Parameter_new_##type(int parameter_size, __PM_Parameter_consume consume, __PM_Parameter_operate operate, type input,int input_size, int child_count) {\
	__PM_Parameter_new_(parameter_size,consume,operate, (void*)&input, input_size, child_count); \
	return input;\
}

#define __PM_ParameterDeclare(type) \
typedef struct __PM_Parameter_##type{ \
	__PM_Parameter_header header;\
	type data;\
	__PM_Meta meta;\
} __PM_Parameter_##type;\
type __PM_Parameter_new_##type(int parameter_size, __PM_Parameter_consume consume, __PM_Parameter_operate operate, type input,int input_size, int child_count);\

#define PMAny(type) __PM_ParameterAny_new(type, *(type*)__PM_any_dummy)

#define PMSet(type, input) __PM_ParameterSet_new(type, input)

#define PMReturn(type, input) __PM_ParameterReturn_new(type, input)

#define PMEq(type, input) __PM_ParameterEq_new(type, input)


//#define PMWillCall(function, ...) PMWillCall_(&function, &_mock_function__##function, _mock_function_paremeter_count_##function , __PM_ArgumentCounter(__VA_ARGS__), __VA_ARGS__)
#define __PM_CALL_MODE_Forward 1
#define __PM_CALL_MODE_WillCall 0
#define PMWillCall(...) PMWillCall_((__VA_ARGS__ ,1))
#define PMWillCall_(variables) PMWillCall__ variables
#define PMWillCall__(function_name, ...) _PMWillCall(__PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE, (void*)&function_name, (void*)&_mock_function__##function_name , _mock_function_paremeter_count_##function_name , __PM_ArgumentCounter(__VA_ARGS__)-1, 1 , 1, __PM_CALL_MODE_WillCall, __VA_ARGS__)

#define PMTimes(...) __PM_ArgumentCounterWithCall(PMTimes, __VA_ARGS__)
#define PMTimes1(times, ...) __PMTimes_(times,times)
#define PMTimes2(from, to, ...) __PMTimes_(from,to)
#define PMAnyTimes() __PMTimes(0,__PM_MAX_INT)


//#define PMWillCall(...) PMWillCall__( __PM_ArgumentCounter(__VA_ARGS__) , __VA_ARGS__, __PM_ArgumentCounter(__VA_ARGS__))
//#define PMWillCall__(count, function_name, ...) PMWillCall_(&function_name, &_mock_function__##function_name, _mock_function_paremeter_count_##function_name , count-1, __VA_ARGS__)

#define PMWillForward(from, to) _PMWillCall(__PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE, (void*)&from, (void*)&to , -1 ,-1, 0 , __PM_MAX_INT, __PM_CALL_MODE_Forward)

#define PMVerify() _PMVerify()

#define PMClean() _PMClean()

#define PMInit() _PMInit()

extern int __PMRemoveHook_local;
#define PMRemoveHook(method) for (__PMRemoveHook_local=0,__PM_Instrument_undo(method);__PMRemoveHook_local<1;__PMRemoveHook_local++,__PM_Instrument_redo(method))

#define PMMock(...) __PM_ArgumentCounterWithCall(PMMock, __VA_ARGS__)
#define PMMockDeclare(...) __PM_ArgumentCounterWithCall(PMMockDeclare, __VA_ARGS__)

#define PMMockDeclare2(function_name, return_type, ...)  PMMockDeclare2_(function_name, return_type)
#define PMMockDeclare2_(function_name, return_type) \
	extern int _mock_function_paremeter_count_##function_name;\
	return_type _mock_function__##function_name(void) ;

#define PMMock2(function_name, return_type, ...)  PMMock2_(function_name, return_type)
#define PMMock2_(function_name, return_type) \
	int _mock_function_paremeter_count_##function_name = 0;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[0+1];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	return_type _mock_function__##function_name(void) {\
		_mock_function_paremeter_type_##function_name parameter;\
		return_type return_value;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &return_value;\
		__PM_UniveralMock_process((void*)&parameter);\
		return return_value;\
	}

#define PMMockDeclare4(function_name, T1, V1, return_type, ...)  PMMockDeclare4_(function_name, T1, V1, return_type)
#define PMMockDeclare4_(function_name, T1, V1,return_type) \
	extern int _mock_function_paremeter_count_##function_name;\
	return_type _mock_function__##function_name(T1 V1);

#define PMMock4(function_name, T1, V1, return_type, ...)  PMMock4_(function_name, T1, V1, return_type)
#define PMMock4_(function_name, T1, V1,return_type) \
	int _mock_function_paremeter_count_##function_name = 1;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[1+1];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	return_type _mock_function__##function_name(T1 V1) {\
		_mock_function_paremeter_type_##function_name parameter;\
		return_type return_value;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &return_value;\
		__PM_UniveralMock_process((void*)&parameter);\
		return return_value;\
	}

#define PMMockDeclare6(function_name, T1, V1, T2, V2, return_type, ...)  PMMockDeclare6_(function_name, T1, V1, T2, V2, return_type)
#define PMMockDeclare6_(function_name, T1, V1, T2, V2, return_type) \
	extern int _mock_function_paremeter_count_##function_name;\
	return_type _mock_function__##function_name(T1 V1, T2 V2);

#define PMMock6(function_name, T1, V1, T2, V2, return_type, ...)  PMMock6_(function_name, T1, V1, T2, V2, return_type)
#define PMMock6_(function_name, T1, V1, T2, V2, return_type) \
	int _mock_function_paremeter_count_##function_name = 2;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[2+1];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	return_type _mock_function__##function_name(T1 V1, T2 V2) {\
		_mock_function_paremeter_type_##function_name parameter;\
		return_type return_value;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &return_value;\
		__PM_UniveralMock_process((void*)&parameter);\
		return return_value;\
	}
#define PMMockDeclare8(function_name, T1, V1, T2, V2, T3, V3, return_type, ...)  PMMockDeclare8_(function_name, T1, V1, T2, V2,T3, V3, return_type)
#define PMMockDeclare8_(function_name, T1, V1, T2, V2, T3, V3, return_type) \
	extern int _mock_function_paremeter_count_##function_name ;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3);
#define PMMock8(function_name, T1, V1, T2, V2, T3, V3, return_type, ...)  PMMock8_(function_name, T1, V1, T2, V2,T3, V3, return_type)
#define PMMock8_(function_name, T1, V1, T2, V2, T3, V3, return_type) \
	int _mock_function_paremeter_count_##function_name = 3;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[3+1];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3) {\
		_mock_function_paremeter_type_##function_name parameter;\
		return_type return_value;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &return_value;\
		__PM_UniveralMock_process((void*)&parameter);\
		return return_value;\
	}
#define PMMockDeclare10(function_name, T1, V1, T2, V2, T3, V3, T4, V4, return_type, ...)  PMMockDeclare10_(function_name, T1, V1, T2, V2,T3, V3, T4, V4,return_type)
#define PMMockDeclare10_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, return_type) \
	extern int _mock_function_paremeter_count_##function_name ;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4);
#define PMMock10(function_name, T1, V1, T2, V2, T3, V3, T4, V4, return_type, ...)  PMMock10_(function_name, T1, V1, T2, V2,T3, V3, T4, V4,return_type)
#define PMMock10_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, return_type) \
	int _mock_function_paremeter_count_##function_name = 4;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[4+1];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4) {\
		_mock_function_paremeter_type_##function_name parameter;\
		return_type return_value;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		parameter.header.field_reference[4] = &return_value;\
		__PM_UniveralMock_process((void*)&parameter);\
		return return_value;\
	}

#define PMMockDeclare12(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, return_type, ...)  PMMockDeclare12_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5,return_type)
#define PMMockDeclare12_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5,  return_type) \
	extern int _mock_function_paremeter_count_##function_name;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5) ;

#define PMMock12(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, return_type, ...)  PMMock12_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5,return_type)
#define PMMock12_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5,  return_type) \
	int _mock_function_paremeter_count_##function_name = 5;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[5+1];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5) {\
		_mock_function_paremeter_type_##function_name parameter;\
		return_type return_value;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		parameter.header.field_reference[4] = &V5;\
		parameter.header.field_reference[5] = &return_value;\
		__PM_UniveralMock_process((void*)&parameter);\
		return return_value;\
	}

#define PMMockDeclare14(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, return_type, ...)  PMMockDeclare14_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, return_type)
#define PMMockDeclare14_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, return_type) \
	extern int _mock_function_paremeter_count_##function_name;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6) ;
#define PMMock14(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, return_type, ...)  PMMock14_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, return_type)
#define PMMock14_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, return_type) \
	int _mock_function_paremeter_count_##function_name = 6;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[6+1];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6) {\
		_mock_function_paremeter_type_##function_name parameter;\
		return_type return_value;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		parameter.header.field_reference[4] = &V5;\
		parameter.header.field_reference[5] = &V6;\
		parameter.header.field_reference[6] = &return_value;\
		__PM_UniveralMock_process((void*)&parameter);\
		return return_value;\
	}

#define PMMockDeclare16(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, return_type, ...)  PMMockDeclare16_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, return_type)
#define PMMockDeclare16_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, return_type) \
	extern int _mock_function_paremeter_count_##function_name;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7) ;

#define PMMock16(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, return_type, ...)  PMMock16_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, return_type)
#define PMMock16_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, return_type) \
	int _mock_function_paremeter_count_##function_name = 7;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[7+1];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7) {\
		_mock_function_paremeter_type_##function_name parameter;\
		return_type return_value;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		parameter.header.field_reference[4] = &V5;\
		parameter.header.field_reference[5] = &V6;\
		parameter.header.field_reference[6] = &V7;\
		parameter.header.field_reference[7] = &return_value;\
		__PM_UniveralMock_process((void*)&parameter);\
		return return_value;\
	}

#define PMMockDeclare18(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, return_type, ...)  PMMockDeclare18_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, return_type)
#define PMMockDeclare18_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, return_type) \
	extern int _mock_function_paremeter_count_##function_name;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8);

#define PMMock18(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, return_type, ...)  PMMock18_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, return_type)
#define PMMock18_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, return_type) \
	int _mock_function_paremeter_count_##function_name = 8;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[8+1];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8) {\
		_mock_function_paremeter_type_##function_name parameter;\
		return_type return_value;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		parameter.header.field_reference[4] = &V5;\
		parameter.header.field_reference[5] = &V6;\
		parameter.header.field_reference[6] = &V7;\
		parameter.header.field_reference[7] = &V8;\
		parameter.header.field_reference[8] = &return_value;\
		__PM_UniveralMock_process((void*)&parameter);\
		return return_value;\
	}

#define PMMockDeclare20(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, return_type, ...)  PMMockDeclare20_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, return_type)
#define PMMockDeclare20_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, return_type) \
	extern int _mock_function_paremeter_count_##function_name  ;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9) ;

#define PMMock20(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, return_type, ...)  PMMock20_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, return_type)
#define PMMock20_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, return_type) \
	int _mock_function_paremeter_count_##function_name = 9;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[9+1];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9) {\
		_mock_function_paremeter_type_##function_name parameter;\
		return_type return_value;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		parameter.header.field_reference[4] = &V5;\
		parameter.header.field_reference[5] = &V6;\
		parameter.header.field_reference[6] = &V7;\
		parameter.header.field_reference[7] = &V8;\
		parameter.header.field_reference[8] = &V9;\
		parameter.header.field_reference[9] = &return_value;\
		__PM_UniveralMock_process((void*)&parameter);\
		return return_value;\
	}

#define PMMockDeclare22(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type, ...)  PMMockDeclare22_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type)
#define PMMockDeclare22_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type) \
	extern int _mock_function_paremeter_count_##function_name;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10) ;

#define PMMock22(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type, ...)  PMMock22_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type)
#define PMMock22_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type) \
	int _mock_function_paremeter_count_##function_name = 10;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[10+1];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	return_type _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10) {\
		_mock_function_paremeter_type_##function_name parameter;\
		return_type return_value;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		parameter.header.field_reference[4] = &V5;\
		parameter.header.field_reference[5] = &V6;\
		parameter.header.field_reference[6] = &V7;\
		parameter.header.field_reference[7] = &V8;\
		parameter.header.field_reference[8] = &V9;\
		parameter.header.field_reference[9] = &V10;\
		parameter.header.field_reference[10] = &return_value;\
		__PM_UniveralMock_process((void*)&parameter);\
		return return_value;\
	}

#define PMMockDeclare1(function_name, ...)  PMMockDeclare1_(function_name)
#define PMMockDeclare1_(function_name) \
	extern int _mock_function_paremeter_count_##function_name  ;\
	void _mock_function__##function_name(void);

#define PMMock1(function_name, ...)  PMMock1_(function_name)
#define PMMock1_(function_name) \
	int _mock_function_paremeter_count_##function_name = 0;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[1];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	void _mock_function__##function_name(void) {\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		__PM_UniveralMock_process((void*)&parameter);\
	}

#define PMMockDeclare3(function_name, T1, V1, ...)  PMMockDeclare3_(function_name, T1, V1)
#define PMMockDeclare3_(function_name, T1, V1) \
	extern int _mock_function_paremeter_count_##function_name ;\
	void _mock_function__##function_name(T1 V1);

#define PMMock3(function_name, T1, V1, ...)  PMMock3_(function_name, T1, V1)
#define PMMock3_(function_name, T1, V1) \
	int _mock_function_paremeter_count_##function_name = 1;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[1];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	void _mock_function__##function_name(T1 V1) {\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		__PM_UniveralMock_process((void*)&parameter);\
	}

#define PMMockDeclare5(function_name, T1, V1, T2, V2, ...)  PMMockDeclare5_(function_name, T1, V1, T2, V2)
#define PMMockDeclare5_(function_name, T1, V1, T2, V2) \
	extern int _mock_function_paremeter_count_##function_name  ;\
	void _mock_function__##function_name(T1 V1, T2 V2);

#define PMMock5(function_name, T1, V1, T2, V2, ...)  PMMock5_(function_name, T1, V1, T2, V2)
#define PMMock5_(function_name, T1, V1, T2, V2) \
	int _mock_function_paremeter_count_##function_name = 2;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[2];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	void _mock_function__##function_name(T1 V1, T2 V2) {\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		__PM_UniveralMock_process((void*)&parameter);\
	}

#define PMMockDeclare7(function_name, T1, V1, T2, V2, T3, V3, ...)  PMMockDeclare7_(function_name, T1, V1, T2, V2,T3, V3)
#define PMMockDeclare7_(function_name, T1, V1, T2, V2, T3, V3) \
	extern int _mock_function_paremeter_count_##function_name  ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3);

#define PMMock7(function_name, T1, V1, T2, V2, T3, V3, ...)  PMMock7_(function_name, T1, V1, T2, V2,T3, V3)
#define PMMock7_(function_name, T1, V1, T2, V2, T3, V3) \
	int _mock_function_paremeter_count_##function_name = 3;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[3];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3) {\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		__PM_UniveralMock_process((void*)&parameter);\
	}

#define PMMockDeclare9(function_name, T1, V1, T2, V2, T3, V3, T4, V4, ...)  PMMockDeclare9_(function_name, T1, V1, T2, V2,T3, V3, T4, V4)
#define PMMockDeclare9_(function_name, T1, V1, T2, V2, T3, V3, T4, V4) \
	extern int _mock_function_paremeter_count_##function_name  ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4);

#define PMMock9(function_name, T1, V1, T2, V2, T3, V3, T4, V4, ...)  PMMock9_(function_name, T1, V1, T2, V2,T3, V3, T4, V4)
#define PMMock9_(function_name, T1, V1, T2, V2, T3, V3, T4, V4) \
	int _mock_function_paremeter_count_##function_name = 4;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[4];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4) {\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		__PM_UniveralMock_process((void*)&parameter);\
	}

#define PMMockDeclare11(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, ...)  PMMockDeclare11_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5)
#define PMMockDeclare11_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5) \
	extern int _mock_function_paremeter_count_##function_name ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5) ;

#define PMMock11(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, ...)  PMMock11_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5)
#define PMMock11_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5) \
	int _mock_function_paremeter_count_##function_name = 5;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[5];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5) {\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		parameter.header.field_reference[4] = &V5;\
		__PM_UniveralMock_process((void*)&parameter);\
	}

#define PMMockDeclare13(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, ...)  PMMockDeclare13_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6)
#define PMMockDeclare13_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6) \
	extern int _mock_function_paremeter_count_##function_name;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6);

#define PMMock13(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, ...)  PMMock13_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6)
#define PMMock13_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6) \
	int _mock_function_paremeter_count_##function_name = 6;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[6];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6) {\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		parameter.header.field_reference[4] = &V5;\
		parameter.header.field_reference[5] = &V6;\
		__PM_UniveralMock_process((void*)&parameter);\
	}

#define PMMockDeclare15(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, ...)  PMMockDeclare15_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7)
#define PMMockDeclare15_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7) \
	extern int _mock_function_paremeter_count_##function_name ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7);

#define PMMock15(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, ...)  PMMock15_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7)
#define PMMock15_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7) \
	int _mock_function_paremeter_count_##function_name = 7;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[7];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7) {\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		parameter.header.field_reference[4] = &V5;\
		parameter.header.field_reference[5] = &V6;\
		parameter.header.field_reference[6] = &V7;\
		__PM_UniveralMock_process((void*)&parameter);\
	}

#define PMMockDeclare17(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, ...)  PMMockDeclare17_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8)
#define PMMockDeclare17_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8) \
	extern int _mock_function_paremeter_count_##function_name ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8);

#define PMMock17(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, ...)  PMMock17_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8)
#define PMMock17_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8) \
	int _mock_function_paremeter_count_##function_name = 8;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[8];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8) {\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		parameter.header.field_reference[4] = &V5;\
		parameter.header.field_reference[5] = &V6;\
		parameter.header.field_reference[6] = &V7;\
		parameter.header.field_reference[7] = &V8;\
		__PM_UniveralMock_process((void*)&parameter);\
	}

#define PMMockDeclare19(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, ...)  PMMockDeclare19_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9)
#define PMMockDeclare19_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9) \
	extern int _mock_function_paremeter_count_##function_name  ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9);

#define PMMock19(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, ...)  PMMock19_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9)
#define PMMock19_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9) \
	int _mock_function_paremeter_count_##function_name = 9;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[9];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9) {\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		parameter.header.field_reference[4] = &V5;\
		parameter.header.field_reference[5] = &V6;\
		parameter.header.field_reference[6] = &V7;\
		parameter.header.field_reference[7] = &V8;\
		parameter.header.field_reference[8] = &V9;\
		__PM_UniveralMock_process((void*)&parameter);\
	}

#define PMMockDeclare21(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, ...)  PMMockDeclare21_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10)
#define PMMockDeclare21_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10) \
	extern int _mock_function_paremeter_count_##function_name ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10);

#define PMMock21(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, ...)  PMMock21_(function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10)
#define PMMock21_(function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10) \
	int _mock_function_paremeter_count_##function_name = 10;\
	typedef struct {\
		int total_size;\
		int field_count;\
		void* called_object;\
		void* function_reference;\
		void* field_reference[10];\
	}_mock_function_paremeter_header_type_##function_name;\
	typedef struct {\
		_mock_function_paremeter_header_type_##function_name header;\
	}_mock_function_paremeter_type_##function_name ;\
	void _mock_function__##function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10) {\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = __PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE;\
		parameter.header.function_reference = _mock_function__##function_name;\
		parameter.header.field_reference[0] = &V1;\
		parameter.header.field_reference[1] = &V2;\
		parameter.header.field_reference[2] = &V3;\
		parameter.header.field_reference[3] = &V4;\
		parameter.header.field_reference[4] = &V5;\
		parameter.header.field_reference[5] = &V6;\
		parameter.header.field_reference[6] = &V7;\
		parameter.header.field_reference[7] = &V8;\
		parameter.header.field_reference[8] = &V9;\
		parameter.header.field_reference[9] = &V10;\
		__PM_UniveralMock_process((void*)&parameter);\
	}




#endif
