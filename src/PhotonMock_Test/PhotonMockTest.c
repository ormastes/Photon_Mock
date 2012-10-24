#include "..\PhotonMock\PhotonMock.h"
//#include "PhotonMock.h"

#define PTAssert(Expected, Actual) if (Expected != Actual) while(1);
#define PTAssertTrue(Expression) if (!(Expression)) while(1);

extern int __PM_Assert_Or_Set_Flag_stop_mode;

__PM_Parameter(int);
__PM_ParameterDeclare(int);

/*
#define It_can_be_asked_to_3(function, T1, V1) \
	typedef struct {\
		int total_siz0e;\
		int field_size;\
		T1 V1##field;\
	}_mock_function_paremeter_type_##function##T1;\
	void _mock_function##function##T1##(T1 V1) {\
		_mock_function_paremeter_type_ parameter ={\
			totalSize;\
			field1_size=sizeof(T1);\
			V1##field=V1; \ 
			return_field \
		};\
		_mock((void*)&parameter);\
	}

#define It_can_be_asked_to_4(function, T1, V1, return_type) \
	typedef struct {\
		int total_size;\
		int field_size;\
		T1 V1##field;\
		return_type return_field\
	}_mock_function_paremeter_type_##function##T1;\
	return_type _mock_function##function##T1##(T1 V1) {\
		_mock_function_paremeter_type_ parameter ={\
			totalSize;\
			field1_size=sizeof(T1);\
			V1##field=V1 \
			return_field \
		};\
		_mock((void*)&parameter);\
		return parameter.return_field;\
	}
*/

//change_(from, to)
//change_to_(to) 

//greater_then_unsigned_integer(x)
//greater_then_or_equal_to_unsigned_integer(x)
//greater_then_uint(x)
//ge_uint(x)
//less_then_or_equal_to_unsigned_integer_(x)
//equal_to_unsigned_integer_(x)

/*
typedef struct {
	int size;
	void* operation;
}*/


//value1, operation1, size1, value2, operation2, size2, operation3, size3, paremterOperation, parametereOperationSize

/*when_it_(xx) it_should_return(xx) {
	it_ask_to_(fly, change_(greater_then_integer_(10 km), 3 km)) and_return_(integer, 3 km)
	it_ask_(bird, fly, change_(......
	it_ask_to_(fly) which_cause_to_(fly_slow)
	it_ask_(bird, fly) which_cause_(bird, fly_slow)
	it_specifically_ask_to_(fly, int, 3)
}*/
// mock_record
// mock_heap
/*
struct {
original_function_pointer
forward_function_pointer
parameter_struct
check_operation_function_list_pointer
modify_operation_function_list_pointer
return_value
*/
// #define it_ask_to() setupInit() { setcurrentheap, setnextheapAddress} 
// setupForEachParmeter(){setup(check_modify)} ParmeterLocation, parameterOperation
// void it_ask_to() {assign_variable}
//}


/*
typedef struct {
	void* current_location;
	int data[__PM_STACK_SIZE];
} __PM_MockStack;
static __PM_MockStack __pm_mock_stack = {0, 0};
__PM_MockStack* __PM_MockStack_get_instance() {
	if (__pm_mock_stack.current_location == 0) __pm_mock_stack.current_location = __pm_mock_stack.data;
	return & __pm_mock_stack;
}



void testMockStack_get_instance(void) {
	__PM_MockStack* stack = __PM_MockStack_get_instance();
	PTAssert(stack->data, stack->current_location);
}
*/ 



void testNode_get_data(void) {
	typedef struct {
		int data;
		__PM_Meta meta;
	} AData;
	AData data, *data_reference;
	data.data = 1;
	data.meta.child_count = 0;
	data.meta.size = sizeof(AData);
	data.meta.size_include_children = sizeof(AData);
	data.meta.type = -1;
	data_reference = (AData*)__PM_Node_get_data((__PM_Meta*)&data.meta);
	PTAssert(data.data, data_reference->data);
	PTAssert(data.meta.child_count, data_reference->meta.child_count);
}




void testStack_get_last_meta(void) {
	typedef struct {
		int data;
		__PM_Meta meta;
	} AData;
	AData data, *result_data;
	__PM_Stack* stack;
	__PM_Meta* meta;
	int data_type = 1, child_count=0;

	__PM_Stack_clean();

	stack = __PM_Stack_get_instance();
	result_data = (AData*) __PM_Stack_add( stack,  &data, data_type, child_count);

	meta = __PM_Stack_get_last_meta(stack);

	PTAssert( (__PM_Meta*)&result_data->meta, meta);

	__PM_Stack_clean();
}

void testStack_get_instance(void) {
	__PM_Stack* stack = __PM_Stack_get_instance();
	PTAssert(stack->data, stack->current_location);

	__PM_Stack_clean();
}

void testStack_add(void) {
	typedef struct {
		int data;
		__PM_Meta meta;
	} AData;
	AData data, *result_data;
	__PM_Stack* stack;
	int data_type = 1, child_count=0;

	stack = __PM_Stack_get_instance();
	result_data = (AData*)__PM_Stack_add( stack,  &data, data_type, child_count);

	PTAssert(data.data, result_data->data);
	PTAssert(child_count,  result_data->meta.child_count);
	PTAssert(data_type,  result_data->meta.type);
	PTAssert(sizeof(AData),  result_data->meta.size);
	PTAssert(sizeof(AData),  result_data->meta.size_include_children);

	__PM_Stack_clean();
}




void testMockRecord_new(void) {
	__PM_Stack* stack;
	__PM_MockRecord* mock;

	int from = 1, to = 2, min_times =3, max_times =3, child_count = 0, no_return_set = 0;
	stack = __PM_Stack_get_instance();

	mock = (__PM_MockRecord*)__PM_MockRecord_new( &from, &to, min_times, max_times, child_count, no_return_set, __PM_CALL_MODE_WillCall); 

	PTAssertTrue((byte*)mock == stack->data);
	PTAssertTrue((int)stack->current_location - (int)sizeof(__PM_MockRecord) == (int)stack->data);
	PTAssert(mock->from, &from);
	PTAssert(mock->to, &to);
	PTAssert(mock->min_times, min_times);
	PTAssert(mock->max_times, max_times);
	PTAssert(mock->meta.child_count, child_count);

	__PM_Stack_clean();
}
void testMockRecord_new_with_child(void) {
	__PM_Stack* stack;
	__PM_MockRecord* mock;

	int from = 1, to = 2, min_times =3,max_times =4, child_count = 2, no_return_set = 0;
	stack = __PM_Stack_get_instance();


	__PM_MockRecord_new( &from, &to, min_times, max_times, 0, no_return_set, __PM_CALL_MODE_WillCall);//should use real child but mockrecord can be used for test as a child
	__PM_MockRecord_new( &from, &to, min_times, max_times, 0, no_return_set, __PM_CALL_MODE_WillCall);
	mock = (__PM_MockRecord*)__PM_MockRecord_new( &from, &to, min_times, max_times, child_count, no_return_set, __PM_CALL_MODE_WillCall); 

	PTAssert(sizeof(__PM_MockRecord)*3, mock->meta.size_include_children);

	__PM_Stack_clean();
}


int instrument_mock_called = 0;

void __PM_Instrumented_Original(void) {__PM_MAKE_FUNCTION_MOCKABLE instrument_mock_called=0;}
void __PM_Instrumented_Forwareded(void) {instrument_mock_called=1;}
void testInstrument_do(void) {
	__PM_Instrument* Instrument;

	Instrument = __PM_Instrument_get_instance(); 
	__PM_Instrument_clean();
	__PM_Stack_clean();	

	__PM_Instrument_do(__PM_Instrumented_Original, __PM_Instrumented_Forwareded);
	__PM_Instrumented_Original();

	PTAssert(1, instrument_mock_called);

	__PM_Instrument_clean();
	__PM_Stack_clean();	
}
void __PM_Instrumented_Original2(void) {__PM_MAKE_FUNCTION_MOCKABLE instrument_mock_called=0;}
void __PM_Instrumented_Forwareded2(void) {instrument_mock_called=1;}
void testInstrument_undo(void) {
	__PM_Instrument* Instrument;

	Instrument = __PM_Instrument_get_instance(); 
	__PM_Instrument_clean();
	__PM_Stack_clean();	

	__PM_Instrument_do(__PM_Instrumented_Original2, __PM_Instrumented_Forwareded2);
	__PM_Instrument_undo(__PM_Instrumented_Original2);
	__PM_Instrumented_Original2();

	PTAssert(0, instrument_mock_called);

	__PM_Instrument_clean();
	__PM_Stack_clean();	
}
void __PM_Instrumented_Original2_1(void) {__PM_MAKE_FUNCTION_MOCKABLE instrument_mock_called=0;}
void __PM_Instrumented_Forwareded2_1(void) {instrument_mock_called=1;}
void testInstrument_redo(void) {
	__PM_Instrument* Instrument;

	Instrument = __PM_Instrument_get_instance(); 
	__PM_Instrument_clean();
	__PM_Stack_clean();	

	__PM_Instrument_do(__PM_Instrumented_Original2, __PM_Instrumented_Forwareded2);
	__PM_Instrument_undo(__PM_Instrumented_Original2);
	__PM_Instrument_redo(__PM_Instrumented_Original2);
	__PM_Instrumented_Original2();

	PTAssert(1, instrument_mock_called);

	__PM_Instrument_clean();
	__PM_Stack_clean();	
}
void __PM_Instrumented_Original3(void) { __PM_MAKE_FUNCTION_MOCKABLE instrument_mock_called=0;}
void __PM_Instrumented_Forwareded3(void) {instrument_mock_called=1;}
void __PM_Instrumented_Original4(void) {__PM_MAKE_FUNCTION_MOCKABLE instrument_mock_called=2;}
void __PM_Instrumented_Forwareded4(void) {instrument_mock_called=3;}
void testInstrument_clean(void) {
	__PM_Instrument* Instrument;

	Instrument = __PM_Instrument_get_instance(); 
	__PM_Instrument_clean();
	__PM_Stack_clean();	

	__PM_Instrument_do(__PM_Instrumented_Original3, __PM_Instrumented_Forwareded3);
	__PM_Instrument_do(__PM_Instrumented_Original3, __PM_Instrumented_Forwareded3);
	__PM_Instrument_do(__PM_Instrumented_Original4, __PM_Instrumented_Forwareded4);
	
	__PM_Instrument_clean();
	
	__PM_Instrumented_Original3();	
	PTAssert(0, instrument_mock_called);
	__PM_Instrumented_Original4();	
	PTAssert(2, instrument_mock_called);

	__PM_Instrument_clean();
	__PM_Stack_clean();	
}
void testPMWillForward(void) {
	PMInit();

	PMWillForward(__PM_Instrumented_Original, __PM_Instrumented_Forwareded);
	__PM_Instrumented_Original();

	PTAssert(1, instrument_mock_called);

	PMVerify();
}
void testInstrumnet_new(void) {
	__PM_Stack* stack;
	__PM_Instrument* instruction;

	stack = __PM_Stack_get_instance();

	instruction = __PM_Instrument_get_instance(); 

	PTAssertTrue((int)instruction != 0);

	__PM_Stack_clean();
}


void testParameter_new(void) {
	__PM_Stack* stack;
	__PM_Parameter_header* parameter_header;
	__PM_Parameter_consume consume = 0;
	__PM_Parameter_operate operate = 0;
	int size;
	int input = 1;
	int child_count = 0;
	size = sizeof(__PM_Parameter_int);
	stack = __PM_Stack_get_instance();
	
	__PM_Stack_clean();

	parameter_header = (__PM_Parameter_header*)__PM_Parameter_new(size, consume, operate, child_count);

	PTAssertTrue((int)parameter_header == (int)stack->data);
	PTAssertTrue((int)stack->current_location - (int)size == (int)stack->data);
	PTAssert(parameter_header->consume, consume);
	PTAssert(parameter_header->operate, operate);
	PTAssert(parameter_header->child_count, child_count);

	
	__PM_Stack_clean();
}

void testParameterEq_new(void) {
	__PM_Parameter_int *parameter;
	int child_count = 0;

	__PM_Stack_clean();
	
	PMEq(int, 12);
	parameter = (__PM_Parameter_int*)__PM_Stack_get_instance()->data;

	PTAssert(__PM_ParameterEq_consume, parameter->header.consume);
	PTAssert(__PM_ParameterEq_operate, parameter->header.operate);
	PTAssert(child_count, parameter->header.child_count);
	PTAssert(12, (int)parameter->data);
	PTAssert(0, parameter->meta.child_count);
	PTAssert(sizeof(__PM_Parameter_int), parameter->meta.size);
	
	__PM_Stack_clean();
}

/*
#define It_can_be_asked_to_3(function, T1, V1) \
	typedef struct {\
		int total_size;\
		int field_size;\
		T1 V1##field;\
	}_mock_function_paremeter_type_##function##T1;\
	void _mock_function##function##T1##(T1 V1) {\
		_mock_function_paremeter_type_ parameter ={\
			totalSize;\
			field1_size=sizeof(T1);\
			V1##field=V1; \ 
			return_field \
		};\
		_mock((void*)&parameter);\
	}

#define It_can_be_asked_strictly_to_4(function, T1, V1, return_type) \
	typedef struct {\
		int total_size;\
		int field_size;\
		T1 V1##field;\
		return_type return_field\
	}_mock_function_paremeter_type_##function##T1;\
	return_type _mock_function##function##T1##(T1 V1) {\
		_mock_function_paremeter_type_ parameter ={\
			totalSize;\
			field1_size=sizeof(T1);\
			V1##field=V1 \
			return_field \
		};\
		_mock((void*)&parameter);\
		return parameter.return_field;\
	}
*/




int simple_function(int input1, int input2) {
	__PM_MAKE_FUNCTION_MOCKABLE
	return input2;
}


PMMock(simple_function, int, input1, int, input2, int);

void testPMReturn(void) {
	int return_value;
	PMInit();

	PMWillCall(simple_function, PMEq(int, 5), PMEq(int, 6), PMReturn(int, 7));
	return_value = simple_function(5, 6);

	PTAssert(7, return_value);

	PMVerify();
}

int simple_pointer_function(int* input1, int input2) {
	__PM_MAKE_FUNCTION_MOCKABLE
	return input2;
}
typedef int* intp;
__PM_ParameterDeclare(intp);
__PM_Parameter(intp);
PMMock6(simple_pointer_function, int*, input1, int, input2, int);


void testPMSet(void) {
	int return_value, output, setup_output;
	PMInit();
	output = 1;
	setup_output = 5;
	PMWillCall(simple_pointer_function, PMSet(int, setup_output), PMEq(int, 6), PMReturn(int, 7));
	return_value = simple_pointer_function(&output, 6);

	PTAssert(5, output);

	PMVerify();
}
typedef struct small_struct {
	int a;
	byte b;
}small_struct;
typedef struct {
	byte a;
	small_struct b;
	byte c;
}embedded_struct;
void sample_testPMSetStruct(small_struct* a_struct) {
	__PM_MAKE_FUNCTION_MOCKABLE
}
typedef small_struct* small_struct_p;
__PM_Parameter(small_struct);
__PM_ParameterDeclare(small_struct);
PMMock3(sample_testPMSetStruct, small_struct_p, a_struct);
void testPMSet_struct(void) {
	embedded_struct a_struct, struct_result;

	a_struct.a = 1;
	a_struct.b.a = 2;
	a_struct.b.b = 3;
	a_struct.c = 4;
	struct_result.a = 5;
	struct_result.b.a = 6;
	struct_result.b.b = 7;
	struct_result.c = 8;

	PMWillCall(sample_testPMSetStruct, PMSet(small_struct, a_struct.b));
	sample_testPMSetStruct(&(struct_result.b));

	PTAssert(5, struct_result.a);
	PTAssert(2, struct_result.b.a);
	PTAssert(3, struct_result.b.b);
	PTAssert(8, struct_result.c);

}
int sample_testPMCallOriginal_original() {
	__PM_MAKE_FUNCTION_MOCKABLE
	return 1;
}
int sample_testPMCallOriginal_forwarded() {
	int result;
	PMRemoveHook(sample_testPMCallOriginal_original) {
		result = sample_testPMCallOriginal_original();
	}
	return result+1;
}
void testPMCallOriginal(void) {
	int return_value;
	PMInit();
	

	PMWillForward(sample_testPMCallOriginal_original, sample_testPMCallOriginal_forwarded);
	return_value = sample_testPMCallOriginal_original();

	PTAssert(2, return_value);

	PMVerify();
}
int sample_testPMCallOriginal_original2(int i) {
	__PM_MAKE_FUNCTION_MOCKABLE
	return i;
}
int sample_testPMCallOriginal_forwarded2(int i) {
	int result;
	PMRemoveHook(sample_testPMCallOriginal_original2) {
		// do not return inside block;
		result = sample_testPMCallOriginal_original2(i);
	}
	return result+1;
}
void testPMCallOriginal_with_paramter(void) {
	int return_value;
	PMInit();
	

	PMWillForward(sample_testPMCallOriginal_original2, sample_testPMCallOriginal_forwarded2);
	return_value = sample_testPMCallOriginal_original2(2);

	PTAssert(3, return_value);

	PMVerify();
}
//void test_record_macro_compile_error_check(void) {//do not call it
	//PMWillCall(simple_function);
//}

void test_record_macro(void) {
	__PM_Meta *meta, *child;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function, PMEq(int, 10), PMEq(int, 11));
	
	meta = __PM_Stack_get_last_meta(__PM_Stack_get_instance());

	PTAssert(__PM_MockRecord_Type, meta->type);
	PTAssert(2, meta->child_count);

	child = __PM_Node_get_child(meta);
	PTAssert(__PM_Parameter_Type, child->type);
	PTAssert(0, child->child_count);

	child = __PM_Node_get_sible(child);
	PTAssert(__PM_Parameter_Type, child->type);
	PTAssert(0, child->child_count);

	__PM_Stack_clean();
	__PM_Instrument_clean();

}



void testUniveralMock_process_without_intercept(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function, PMEq(int, 5), PMEq(int, 6));
	_mock_function__simple_function(5, 6);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}

void testUniveralMock_process(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function, PMEq(int, 5), PMEq(int, 6));
	simple_function(5, 6);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}

void testUniveralMock_process_not_called(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function, PMEq(int, 5), PMEq(int, 6));
	//simple_function(5, 6);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));



	__PM_Assert( ! __PM_UniveralMock_check_consume_());

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}

void testUniveralMock_process_different_argument(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	__PM_Assert_Or_Set_Flag_stop_mode = 0;

	PMWillCall(simple_function, PMEq(int, 5), PMEq(int, 6));
	simple_function(5, 7);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));



	__PM_Assert( ! __PM_UniveralMock_check_consume_());

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}


void test_mock_process(void) {
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function, PMEq(int, 10), PMEq(int, 11));

	simple_function(10,11);
	
	__PM_Stack_clean();
	__PM_Instrument_clean();
}

void testMockOrder() {
	int return_value;
	PMInit();

	PMWillCall(simple_function, PMAny(int), PMAny(int), PMReturn(int, 1));
	PMWillCall(simple_function, PMAny(int), PMAny(int), PMReturn(int, 2));
	return_value = simple_function(8, 9);
	PTAssert(1, return_value);
	return_value = simple_function(10, 11);
	PTAssert(2, return_value);
	__PM_UniveralMock_check_consume();

	PMVerify();	
}
void testTimes_min(void) {
	__PM_MockRecord* mock;
	PMInit();

	PMWillCall(simple_function, PMEq(int, 5), PMEq(int, 6));PMTimes(2,3);
	simple_function(5, 6);
	simple_function(5, 6);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(2, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();
}
void testTimes_max(void) {
	__PM_MockRecord* mock;
	PMInit();

	PMWillCall(simple_function, PMEq(int, 5), PMEq(int, 6));PMTimes(2,3);
	simple_function(5, 6);
	simple_function(5, 6);
	simple_function(5, 6);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(3, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();
}
void testTimes_less(void) {

}
void testTimes_more(void) {

}
void testTimes_one_parameter(void) {

}
void testAnyTimes_no_call(void) {

}
void testAnyTimes_x_times(void) {

}

void testPMVerify_empty_stack(void) {
	PMInit();
	PMVerify();	
}
void testPMAny(void) {
	int return_value;
	PMInit();

	PMWillCall(simple_function, PMAny(int), PMAny(int), PMReturn(int, 7));
	return_value = simple_function(8, 10);

	PTAssert(7, return_value);
	__PM_UniveralMock_check_consume();

	PMVerify();	
}

int simple_function_0paramter_return(void) {
	__PM_MAKE_FUNCTION_MOCKABLE
	return 1;
}  
PMMockDeclare(simple_function_0paramter_return, int);
void testWillCall_0paramter_return(void) {
	__PM_MockRecord* mock;
	int return_value;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_0paramter_return, PMReturn(int, 11));
	return_value = simple_function_0paramter_return();

	PTAssert(11, return_value);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
int simple_function_1paramter_return(int input1) {
	__PM_MAKE_FUNCTION_MOCKABLE
	return input1;
}
PMMockDeclare(simple_function_1paramter_return, int, input1, int);
void testWillCall_1paramter_return(void) {
	__PM_MockRecord* mock;
	int return_value;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_1paramter_return, PMEq(int, 1),PMReturn(int, 11));
	return_value = simple_function_1paramter_return(1);

	PTAssert(11, return_value);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
int simple_function_3paramter_return(int input1, int input2, int input3) {
	__PM_MAKE_FUNCTION_MOCKABLE
	return input1;
}
PMMockDeclare(simple_function_3paramter_return, int, input1, int, input2, int, input3,  int);
void testWillCall_3paramter_return(void) {
	__PM_MockRecord* mock;
	int return_value;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_3paramter_return, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMReturn(int, 11));
	return_value = simple_function_3paramter_return(1,2,3);

	PTAssert(11, return_value);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
int simple_function_4paramter_return(int input1, int input2, int input3, int input4) {
	__PM_MAKE_FUNCTION_MOCKABLE
	return input1;
}
PMMockDeclare(simple_function_4paramter_return, int, input1, int, input2, int, input3, int, input4,  int);
void testWillCall_4paramter_return(void) {
	__PM_MockRecord* mock;
	int return_value;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_4paramter_return, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMReturn(int, 11));
	return_value = simple_function_4paramter_return(1,2,3,4);

	PTAssert(11, return_value);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
int simple_function_5paramter_return(int input1, int input2, int input3, int input4, int input5) {
	__PM_MAKE_FUNCTION_MOCKABLE
	return input1;
}
PMMockDeclare(simple_function_5paramter_return, int, input1, int, input2, int, input3, int, input4, int, input5,  int);

/*
static int _mock_function_paremeter_count_simple_function_5paramter_return = 5;
typedef struct {
	int total_size;
	int field_count;
	void* function_reference;
	void* field_reference[5+1];
}_mock_function_paremeter_header_type_simple_function_5paramter_return;
typedef struct {
	_mock_function_paremeter_header_type_simple_function_5paramter_return header;
}_mock_function_paremeter_type_simple_function_5paramter_return ;
int _mock_function__simple_function_5paramter_return__(int input1, int input2, int input3, int input4, int input5) {
	_mock_function_paremeter_type_simple_function_5paramter_return parameter;
	int return_value;
	parameter.header.total_size = sizeof(_mock_function_paremeter_type_simple_function_5paramter_return);
	parameter.header.field_count = _mock_function_paremeter_count_simple_function_5paramter_return;
	parameter.header.function_reference = _mock_function__simple_function_5paramter_return__;
	parameter.header.field_reference[0] = &input1;
	parameter.header.field_reference[1] = &input2;
	parameter.header.field_reference[2] = &input3;
	parameter.header.field_reference[3] = &input4;
	parameter.header.field_reference[4] = &input5;
	parameter.header.field_reference[5] = &return_value;
	__PM_UniveralMock_process((void*)&parameter);
	return return_value;
}*/

void testWillCall_5paramter_return(void) {
	__PM_MockRecord* mock;
	int return_value;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_5paramter_return, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMReturn(int, 11));
	return_value = simple_function_5paramter_return(1,2,3,4,5);

	PTAssert(11, return_value);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}

int simple_function_6paramter_return(int input1, int input2, int input3, int input4, int input5, int input6) {
	__PM_MAKE_FUNCTION_MOCKABLE
	return input1;
}
PMMockDeclare(simple_function_6paramter_return, int, input1, int, input2, int, input3, int, input4, int, input5, int, input6, int);
void testWillCall_6paramter_return(void) {
	__PM_MockRecord* mock;
	int return_value;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_6paramter_return, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMReturn(int, 11));
	return_value = simple_function_6paramter_return(1,2,3,4,5,6);

	PTAssert(11, return_value);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
int simple_function_7paramter_return(int input1, int input2, int input3, int input4, int input5, int input6, int input7) {
	__PM_MAKE_FUNCTION_MOCKABLE
	return input1;
}
PMMockDeclare(simple_function_7paramter_return, int, input1, int, input2, int, input3, int, input4, int, input5, int, input6, int, input7, int);
void testWillCall_7paramter_return(void) {
	__PM_MockRecord* mock;
	int return_value;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_7paramter_return, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7),PMReturn(int, 11));
	return_value = simple_function_7paramter_return(1,2,3,4,5,6,7);

	PTAssert(11, return_value);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}

int simple_function_8paramter_return(int input1, int input2, int input3, int input4, int input5, int input6, int input7, int input8) {
	__PM_MAKE_FUNCTION_MOCKABLE
	return input1;
}
PMMockDeclare(simple_function_8paramter_return, int, input1, int, input2, int, input3, int, input4, int, input5, int, input6, int, input7, int, input8, int);
void testWillCall_8paramter_return(void) {
	__PM_MockRecord* mock;
	int return_value;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_8paramter_return, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7),PMEq(int, 8),PMReturn(int, 11));
	return_value = simple_function_8paramter_return(1,2,3,4,5,6,7,8);

	PTAssert(11, return_value);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}

int simple_function_9paramter_return(int input1, int input2, int input3, int input4, int input5, int input6, int input7, int input8, int input9) {
	__PM_MAKE_FUNCTION_MOCKABLE
	return input1;
}
PMMockDeclare(simple_function_9paramter_return, int, input1, int, input2, int, input3, int, input4, int, input5, int, input6, int, input7, int, input8, int, input9, int);
void testWillCall_9paramter_return(void) {
	__PM_MockRecord* mock;
	int return_value;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_9paramter_return, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7),PMEq(int, 8),PMEq(int, 9),PMReturn(int, 11));
	return_value = simple_function_9paramter_return(1,2,3,4,5,6,7,8,9);

	PTAssert(11, return_value);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}

int simple_function_10paramter_return(int input1, int input2, int input3, int input4, int input5, int input6, int input7, int input8, int input9, int input10) {
	__PM_MAKE_FUNCTION_MOCKABLE
	return input1;
}
PMMockDeclare(simple_function_10paramter_return, int, input1, int, input2, int, input3, int, input4, int, input5, int, input6, int, input7, int, input8, int, input9, int, input10, int);
void testWillCall_10paramter_return(void) {
	__PM_MockRecord* mock;
	int return_value;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_10paramter_return, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7),PMEq(int, 8),PMEq(int, 9),PMEq(int, 10),PMReturn(int, 11));
	return_value = simple_function_10paramter_return(1,2,3,4,5,6,7,8,9,10);

	PTAssert(11, return_value);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
void simple_function_0paramter(void){
	__PM_MAKE_FUNCTION_MOCKABLE
}
PMMockDeclare(simple_function_0paramter);
void testWillCall_0paramter(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_0paramter);
	//PMWillCall_(&simple_function_0paramter, &_mock_function__simple_function_0paramter__, _mock_function_paremeter_count_simple_function_0paramter , 1-1,1 );
	simple_function_0paramter();

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
void simple_function_1paramter(int input1){__PM_MAKE_FUNCTION_MOCKABLE}
PMMockDeclare(simple_function_1paramter, int, input1);
void testWillCall_1paramter(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_1paramter, PMEq(int, 1));
	simple_function_1paramter(1);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
void simple_function_2paramter(int input1, int input2){__PM_MAKE_FUNCTION_MOCKABLE}
PMMockDeclare(simple_function_2paramter, int, input1, int, input2);
void testWillCall_2paramter(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_2paramter, PMEq(int, 1),PMEq(int, 2));
	simple_function_2paramter(1,2);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
void simple_function_3paramter(int input1, int input2, int input3){__PM_MAKE_FUNCTION_MOCKABLE}
PMMockDeclare(simple_function_3paramter, int, input1, int, input2, int, input3);
void testWillCall_3paramter(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_3paramter, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3));
	simple_function_3paramter(1,2,3);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
void simple_function_4paramter(int input1, int input2, int input3, int input4){__PM_MAKE_FUNCTION_MOCKABLE}
PMMockDeclare(simple_function_4paramter, int, input1, int, input2, int, input3, int, input4);
void testWillCall_4paramter(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_4paramter, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4));
	simple_function_4paramter(1,2,3,4);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
void simple_function_5paramter(int input1, int input2, int input3, int input4, int input5) {__PM_MAKE_FUNCTION_MOCKABLE}
PMMockDeclare(simple_function_5paramter, int, input1, int, input2, int, input3, int, input4, int, input5);
void testWillCall_5paramter(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_5paramter, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5));
	simple_function_5paramter(1,2,3,4,5);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
void simple_function_6paramter(int input1, int input2, int input3, int input4, int input5, int input6) {
	__PM_MAKE_FUNCTION_MOCKABLE
}
PMMockDeclare(simple_function_6paramter, int, input1, int, input2, int, input3, int, input4, int, input5, int, input6);
void testWillCall_6paramter(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_6paramter, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6));
	simple_function_6paramter(1,2,3,4,5,6);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
void simple_function_7paramter(int input1, int input2, int input3, int input4, int input5, int input6, int input7) {__PM_MAKE_FUNCTION_MOCKABLE}
PMMockDeclare(simple_function_7paramter, int, input1, int, input2, int, input3, int, input4, int, input5, int, input6, int, input7);
void testWillCall_7paramter(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_7paramter, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7));
	simple_function_7paramter(1,2,3,4,5,6,7);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}

void simple_function_8paramter(int input1, int input2, int input3, int input4, int input5, int input6, int input7, int input8) {__PM_MAKE_FUNCTION_MOCKABLE}
PMMockDeclare(simple_function_8paramter, int, input1, int, input2, int, input3, int, input4, int, input5, int, input6, int, input7, int, input8);
void testWillCall_8paramter(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_8paramter, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7),PMEq(int, 8));
	simple_function_8paramter(1,2,3,4,5,6,7,8);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}

void simple_function_9paramter(int input1, int input2, int input3, int input4, int input5, int input6, int input7, int input8, int input9) {__PM_MAKE_FUNCTION_MOCKABLE}
PMMockDeclare(simple_function_9paramter, int, input1, int, input2, int, input3, int, input4, int, input5, int, input6, int, input7, int, input8, int, input9);
void testWillCall_9paramter(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_9paramter, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7),PMEq(int, 8),PMEq(int, 9));
	simple_function_9paramter(1,2,3,4,5,6,7,8,9);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}

void simple_function_10paramter(int input1, int input2, int input3, int input4, int input5, int input6, int input7, int input8, int input9, int input10) {__PM_MAKE_FUNCTION_MOCKABLE}
PMMockDeclare(simple_function_10paramter, int, input1, int, input2, int, input3, int, input4, int, input5, int, input6, int, input7, int, input8, int, input9, int, input10);
void testWillCall_10paramter(void) {
	__PM_MockRecord* mock;
	__PM_Stack_clean();
	__PM_Instrument_clean();

	PMWillCall(simple_function_10paramter, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7),PMEq(int, 8),PMEq(int, 9),PMEq(int, 10));
	simple_function_10paramter(1,2,3,4,5,6,7,8,9,10);

	mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	PTAssert(1, mock->called);

	__PM_UniveralMock_check_consume();

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}
void runPhotonMockTests(void) {
	testNode_get_data();
	
	testStack_get_instance();
	testStack_add();
	testStack_get_last_meta();
	//testStack_clean();tested indirectly
		
	testMockRecord_new();
	testMockRecord_new_with_child();

	testParameter_new();
	testParameterEq_new();

	testInstrumnet_new();
	testInstrument_do();
	testInstrument_undo();
	testInstrument_clean();

	test_record_macro();

	//testUniversalMock_get_instance();
	test_mock_process();// not yet implemented
	testUniveralMock_process_without_intercept();
	testUniveralMock_process();// not yet implemented
	testUniveralMock_process_not_called();
	testUniveralMock_process_different_argument();

	testMockOrder();

	testTimes_min();
	testTimes_max();
	testTimes_less();
	testTimes_more();
	testTimes_one_parameter();
	testAnyTimes_no_call();
	testAnyTimes_x_times();

	testPMVerify_empty_stack();
	testPMWillForward();
	testPMReturn();
	testPMAny();
	testPMSet();
	testPMSet_struct();
	testPMCallOriginal();
	testPMCallOriginal_with_paramter();

	testWillCall_0paramter_return();
	testWillCall_1paramter_return();
	//testWillCall_2paramter_return(); Default test 
	testWillCall_3paramter_return();
	testWillCall_4paramter_return();
	testWillCall_5paramter_return();
	testWillCall_6paramter_return();
	testWillCall_7paramter_return();
	testWillCall_8paramter_return();
	testWillCall_9paramter_return();
	testWillCall_10paramter_return();

	testWillCall_0paramter();
	testWillCall_1paramter();
	testWillCall_2paramter();
	testWillCall_3paramter();
	testWillCall_4paramter();
	testWillCall_5paramter();
	testWillCall_6paramter();
	testWillCall_7paramter();
	testWillCall_8paramter();
	testWillCall_9paramter();
	testWillCall_10paramter();

}
/*
void main(void) {
	runPhotonMockTests();

}
*/


