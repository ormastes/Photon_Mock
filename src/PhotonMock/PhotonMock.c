#include "PhotonMock.h"
#ifdef X86
#include <Windows.h>
#endif

int __PM_Assert_Or_Set_Flag_stop_mode;
int __PM_Assert_Or_Set_Flag_success;

void __PM_Check_To_Pause_Or_Set_Flag(int boolean_value) {
	if (!boolean_value) {
		if (__PM_Assert_Or_Set_Flag_stop_mode) {
			while(1);
		} else {
			__PM_Assert_Or_Set_Flag_success = __PM_FAIL;
		}
	}
}

void (*PM_AssertFunction)(int boolean_value) = &__PM_Check_To_Pause_Or_Set_Flag;

void __PM_Assert(int boolean_value) {
	(*PM_AssertFunction)(boolean_value) ;
}

void __Assert_Init(void) {
	__PM_Assert_Or_Set_Flag_stop_mode = 1;
	__PM_Assert_Or_Set_Flag_success = __PM_SUCCESS;
}


void __PM_Dummy_Operation(int i) {
	
}
void _PMClean(void) {
	__PM_Instrument_clean();
	__PM_Stack_clean();
	PM_Link_clean();
	__Assert_Init();
}
void _PMInit(void) {
	_PMClean();
}
void _PMVerify(void) {
	 __PM_UniveralMock_check_consume();
	 _PMClean();
}

byte* __PM_Node_get_data(__PM_Meta* node) {
	return ((byte*)node) - node->size + sizeof(__PM_Meta);
}

static __PM_Stack __pm_stack = {0, 0};
__PM_Stack* __PM_Stack_get_instance(void) {
	if (__pm_stack.current_location == 0) __pm_stack.current_location = __pm_stack.data;
	return & __pm_stack;
}

void __PM_Stack_clean(void) {
	 __pm_stack.current_location = __pm_stack.data;
}
__PM_Meta* __PM_Node_get_child(__PM_Meta* parent) {
	if (parent->child_count == 0) return 0;
	return (__PM_Meta*) (((byte*)parent) - parent->size);
}
__PM_Meta* __PM_Node_get_sible(__PM_Meta* target) {
	__PM_Meta* new_target;
	new_target = (__PM_Meta*) (((byte*)target) - target->size_include_children);
	if ((int)new_target < (int)__pm_stack.data) return 0;
	return new_target;
}

__PM_Meta* __PM_Node_new_(int node_size, int node_type, int child_count) {
	__PM_Meta* meta;
	byte* added_data;
	__PM_Meta* child_meta;
	__PM_Stack* stack;
	int i ;

	stack  = __PM_Stack_get_instance();

	added_data = stack->current_location;

	meta = (__PM_Meta*) (((int)stack->current_location) +node_size- sizeof(__PM_Meta));
	meta->child_count = child_count;
	meta->size = node_size;
	meta->size_include_children  = node_size;
	child_meta = __PM_Node_get_child(meta);
	for (i = 0; i < child_count; i++) {
		 meta->size_include_children  += child_meta->size_include_children;
		 child_meta = __PM_Node_get_sible(child_meta);// could cause danger
	}
	meta->type = node_type;

	stack->current_location += node_size;

	return  meta;
}



byte* __PM_Stack_add_(__PM_Stack* stack, byte* node, int node_size, int node_type, int child_count) {
	int i;
	__PM_Meta *added_node;
	int data_size;
	byte *data, *data_to_be_written, *added_data;

	data = node;// node start with data
	added_node =  __PM_Node_new_(node_size, node_type, child_count);
	added_data= __PM_Node_get_data(added_node);
	data_to_be_written = added_data;
	data_size = node_size - sizeof(__PM_Meta);
	for (i = 0; i < data_size; i++) {
		*((data_to_be_written)++) =  *(data++);
	}

	return added_data;
		
}
__PM_Meta* __PM_Stack_get_last_meta(__PM_Stack* stack) {
	if (stack->current_location == stack->data) {
		return 0;
	}
	return (__PM_Meta*) (((int)stack->current_location) - sizeof(__PM_Meta));
}


__PM_MockRecord* __PM_MockRecord_new(void* from, void* to, int min_times, int max_times, int child_count, int is_resturn_set, int is_forward) {
	__PM_MockRecord *new_mock_reocord;
	__PM_MockRecord *mock_record;
	__PM_Meta * mock;

	if (is_forward == __PM_CALL_MODE_Forward) {
		mock = __PM_Stack_get_last_meta(__PM_Stack_get_instance());
		while (mock != 0) {
			mock_record = (__PM_MockRecord*)__PM_Node_get_data(mock);
			if (mock_record->from == from) {
				__PM_Check_To_Pause_Or_Set_Flag(0);
				return 0;
			}
			mock = __PM_Node_get_sible(mock);
		}
	}

	new_mock_reocord = (__PM_MockRecord*)__PM_Node_get_data(__PM_Node_new(__PM_MockRecord, child_count));
	new_mock_reocord->from = from;
	new_mock_reocord->to = to;
	new_mock_reocord->min_times = min_times;
	new_mock_reocord->max_times = max_times;
	new_mock_reocord->called = 0;
	new_mock_reocord->is_return_set = is_resturn_set;
	new_mock_reocord->is_forward = is_forward;

	return new_mock_reocord;
}

static int __PM_Link_list[20];
static int __PM_Link_index = 0;
void PM_Link_push(int link) {
	__PM_Link_list[__PM_Link_index++]= link;
}
int PM_Link_pop(void) {
	return __PM_Link_list[--__PM_Link_index];
}
void PM_Link_clean(void) {
	__PM_Link_index = 0;
}

static __PM_Instrument instrument;
static __PM_Instrument *instrument_reference = 0;
int __PMRemoveHook_local;

__PM_Instrument* __PM_Instrument_get_instance(void) { 
#ifdef X86
	static byte jump[] = {0x55, 0x5D, 0xE9};
	static byte address_mask[] = {0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};

	if (instrument_reference != 0) return instrument_reference;
	
	instrument_reference = &instrument;
	instrument_reference->originally_little_endian = 0;
	instrument_reference->little_endian = 0;
	instrument_reference->instruction_include_address_size = __PM_INSTRUMENT_WHOLE_INSTRUCTION_SIZE;
	instrument_reference->instruction_address_size = 4;
	instrument_reference->instruction_size = 3;
	instrument_reference->address_mask = address_mask;
	instrument_reference->address_shift_right = 0;
	instrument_reference->pc_and_current_difference = 7;
	instrument_reference->is_64bit = 0;
	instrument_reference->instruction = jump;
	instrument_reference->address_location = 3;
	instrument_reference->from_to_current = 0;
#endif
#ifdef ARM
	static byte jump[] = {0x00,0x00,0x00,0xEA};
	static byte address_mask[] = {0xFF,0xFF,0xFF,0x00};

	if (instrument_reference != 0) return instrument_reference;

	instrument_reference = &instrument;
	instrument_reference->originally_little_endian = 1;
	instrument_reference->little_endian = 1;
	instrument_reference->instruction_include_address_size = __PM_INSTRUMENT_WHOLE_INSTRUCTION_SIZE;
	instrument_reference->instruction_address_size = 4;
	instrument_reference->instruction_size = 4;
	instrument_reference->address_mask = address_mask;
	instrument_reference->address_shift_right = 2;
	instrument_reference->pc_and_current_difference = 8;
	instrument_reference->is_64bit = 0;
	instrument_reference->instruction = jump;
	instrument_reference->address_location = 0;
	instrument_reference->from_to_current = 0;
#endif
#ifdef ARM_THUMB2
	static byte jump[] = {0xFF,0xB5, //push all+l 2 >> B4FF
						0x08,0x98, //loadstack (r0)2  >>9808
						0x00,0xE0,0x00,0xF0, //call pushlink4
						0xFF,0xBC, //pop all2 >> b0FF
						0x01,0xB0, //stackadd +1 2 b001
						0x00,0xE0,0x00,0xF0, //call target 4
						0x01,0xB4, //push(0)
						0x01,0xB4, //push(0)
						0x00,0xE0,0x00,0xF0, //poplink 
						0x01,0x90, //str (ro, 1) 9001
						0x01,0xBC, //pop(r0) BC01
						0x00,0xBD}; //pop(PC)
	static byte address_mask[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	if (instrument_reference != 0) return instrument_reference;

	instrument_reference = &instrument;
	instrument_reference->originally_little_endian = 1;
	instrument_reference->little_endian = 1;
	instrument_reference->instruction_include_address_size = __PM_INSTRUMENT_WHOLE_INSTRUCTION_SIZE;
	instrument_reference->instruction_address_size = 1; 
	instrument_reference->instruction_size = 30;
	instrument_reference->address_mask = address_mask;
	instrument_reference->address_shift_right = 1;
	instrument_reference->pc_and_current_difference = 4 + 12 ;
	instrument_reference->is_64bit = 0;
	instrument_reference->instruction = jump;
	instrument_reference->address_location = 12;
	instrument_reference->from_to_current = 0;
#endif

	return instrument_reference;
}
static void __PM_Instrument_undo_strict(void* from);
void __PM_Instrument_clean(void) {
	__PM_Instrument* instrument;
	int i;
	instrument = __PM_Instrument_get_instance();
	for (i = instrument->from_to_current-1; i>=0; i--) {
		__PM_Instrument_undo_strict(instrument->from[i]);
	}
	
	instrument->from_to_current = 0;
	
}


static long __PM_Instrument_getRealFunctionAddress(void* pointerVoid2) {
#ifdef X86
	unsigned char* jmpAddress = (unsigned char*)(pointerVoid2);
	long realFunctionAddress = (long)(pointerVoid2)
		+ *(jmpAddress+1) + (*(jmpAddress+2))*256 + (*(jmpAddress+3))*256*256 + (*(jmpAddress+4))*256*256*256 +5;
	return realFunctionAddress;
#endif
#ifdef ARM
	return (long)pointerVoid2;
#endif
#ifdef ARM_THUMB2
	return (long)pointerVoid2;
#endif
}

int __PM_Instrument_examing_same_target(void* to, __PM_Instrument* instrument, int index) {
	if (to != instrument->to[index]) {
		return __PM_INSTRUMENT_DUPLICATE_ERROR;
	} else {
		return __PM_INSTRUMENT_OK;// already instrument done;
	}
}
void* __PM_Instrument_get_address(int is64bit, void* from, void* to, int pc_and_current_difference, int address_shift_right) {
	void* instructino_address_part;
	if (is64bit) {		
		instructino_address_part = (void*)(((((unsigned long)to)- ((unsigned long)from) - pc_and_current_difference) >> address_shift_right) );
	} else {
		instructino_address_part = (void*)(((((unsigned int)to)- ((unsigned int)from) - pc_and_current_difference) >> address_shift_right) );
	}
	return instructino_address_part;
}
int __PM_Instrument_do(void* from , void* to) {
	__PM_Instrument* instrument;
	int i, backup_index, address_index;
	#ifdef ARM_THUMB2
	int j;
	unsigned int temp_address, temp_address2;
	#endif
	byte *from_byte, *to_byte;
	void* instructino_address_part;
	byte* instructino_address_part_reference;
	#ifdef X86
	DWORD temp;
	#endif
	instrument = __PM_Instrument_get_instance();
	#ifdef X86
	from = (void*)__PM_Instrument_getRealFunctionAddress(from);
	to = (void*)__PM_Instrument_getRealFunctionAddress(to);

	#endif
	from_byte = (byte*)from;
	to_byte = (byte*)to;

	instructino_address_part_reference = (byte*)&instructino_address_part;

	#ifdef X86
	VirtualProtect(from_byte, __PM_INSTRUMENT_WHOLE_INSTRUCTION_SIZE, PAGE_EXECUTE_READWRITE, &temp);
	#endif
	#ifdef ARM_THUMB2
	from_byte -= 1;
	//from = (void*)(((unsigned int)from/2)*2);
	#endif
	for (backup_index = 0; backup_index < instrument->from_to_current; backup_index++) {
		if (from == instrument->from[backup_index]) {
			return __PM_Instrument_examing_same_target(to, instrument, backup_index);
		}
	}
	
	instrument->from[instrument->from_to_current] = from;
	instrument->to[instrument->from_to_current] = to;
	
	instructino_address_part = __PM_Instrument_get_address(instrument->is_64bit, from, to, instrument->pc_and_current_difference, instrument->address_shift_right);
	
	for (i = 0; i < instrument->instruction_include_address_size; i ++) {
		instrument->from_backup[instrument->from_to_current][i] = from_byte[i];
	}
	instrument->from_to_current++;

	for (i = 0; i < instrument->instruction_include_address_size; i ++) {
			from_byte[i] = 0x00;
	}

	for (i = 0; i < instrument->instruction_size; i ++) {
			from_byte[i] |= instrument->instruction[i];
	} 
	for (i = 0; i < instrument->instruction_address_size; i ++) {
#ifdef X86
		address_index = i;
		from_byte[i+instrument->address_location] |= instrument->address_mask[i+instrument->address_location] & instructino_address_part_reference[i];
#endif
#ifdef ARM
		address_index = instrument->instruction_address_size -1 -i;
		from_byte[i+instrument->address_location] |= instrument->address_mask[i+instrument->address_location] & instructino_address_part_reference[i+instrument->address_location];
#endif
#ifdef ARM_THUMB2
		temp_address2 = (unsigned int)__PM_Instrument_get_address(instrument->is_64bit, from, PM_Link_push, 4+4, instrument->address_shift_right);
		temp_address = 0xF800F000;
		temp_address +=  (0x7FF & ((unsigned int)(temp_address2)>>11)) ;
		temp_address +=  (0x7FF & (unsigned int)(temp_address2))<<16  ;
		for (j = 0 ; j < 4; j++) from_byte[j+4] = ((byte*)&temp_address)[j];
		
		temp_address = 0xF800F000;
		temp_address +=  (0x7FF & ((unsigned int)(instructino_address_part)>>11)) ;
		temp_address +=  (0x7FF & (unsigned int)(instructino_address_part))<<16  ;
		for (j = 0 ; j < 4; j++) from_byte[j+instrument->address_location] = ((byte*)&temp_address)[j];

		temp_address2 = (unsigned int)__PM_Instrument_get_address(instrument->is_64bit, from, PM_Link_pop, 4+20, instrument->address_shift_right);
		temp_address = 0xF800F000;
		temp_address +=  (0x7FF & ((unsigned int)(temp_address2)>>11)) ;
		temp_address +=  (0x7FF & (unsigned int)(temp_address2))<<16  ;
		for (j = 0 ; j < 4; j++) from_byte[j+20] = ((byte*)&temp_address)[j];		
#endif	
	}
	return __PM_INSTRUMENT_OK;
}

void __PM_Common_copy(byte* to, byte* from, int size) {
	int byte_index;
	for (byte_index = 0; byte_index < size; byte_index++) {
		to[byte_index] = from[byte_index];
	}
}

static void __PM_Instrument_undo_strict(void* from) {
	__PM_Instrument* instrument;
	int backup_index;
	byte *from_byte;
	from_byte = (byte*)from;
#ifdef ARM_THUMB2
from_byte -= 1;
#endif
	instrument = __PM_Instrument_get_instance();

	for (backup_index = 0; backup_index < instrument->from_to_current; backup_index++) {
		if (from == instrument->from[backup_index]) {
			__PM_Common_copy(instrument->from_backup_for_redo[backup_index], from_byte, instrument->instruction_include_address_size);
			__PM_Common_copy(from_byte, instrument->from_backup[backup_index], instrument->instruction_include_address_size);

		}
	}
	
}
void __PM_Instrument_undo(void* from) {
#ifdef X86
	from = (void*)__PM_Instrument_getRealFunctionAddress(from);
#endif
	__PM_Instrument_undo_strict(from);	
}
void __PM_Instrument_redo(void* from) {
	__PM_Instrument* _instrument;
	int backup_index;
	byte *from_byte;
#ifdef X86
	from = (void*)__PM_Instrument_getRealFunctionAddress(from);
#endif
	from_byte = (byte*)from;
#ifdef ARM_THUMB2
from_byte -= 1;
#endif
	_instrument = __PM_Instrument_get_instance();

	for (backup_index = 0; backup_index < _instrument->from_to_current; backup_index++) {
		if (from == _instrument->from[backup_index]) {
			__PM_Common_copy(from_byte, _instrument->from_backup_for_redo[backup_index], _instrument->instruction_include_address_size);
		}
	}
}











__PM_Parameter_header* __PM_Parameter_new(int parameter_size, __PM_Parameter_consume consume, __PM_Parameter_operate operate, int child_count) {
	__PM_Parameter_header* parameter_header;
	parameter_header = (__PM_Parameter_header*) __PM_Node_get_data(__PM_Node_new_(parameter_size, __PM_Parameter_Type, child_count));
	parameter_header->consume = consume;
	parameter_header->operate = operate;
	parameter_header->child_count = child_count;

	return parameter_header;
}


int __PM_ParameterSet_consume(void* parameter, void* input) {
	return __PM_SAME;
}
int __PM_ParameterSet_operate(void* parameter, void* input) {
	__PM_Parameter_header* header;
	__PM_Meta* meta;
	int size,i;
	byte** byte_input;
	byte* data;

	byte_input = (byte**)input;

	meta = (__PM_Meta*) parameter;
	header = (__PM_Parameter_header*)__PM_Node_get_data(meta);
	data = (byte*)(((byte*)header) + sizeof(__PM_Parameter_header));
	size = meta->size - sizeof(__PM_Parameter_header) - sizeof(__PM_Meta);

	for (i = 0; i < size; i++) {
		(*byte_input)[i] = (data)[i];
	}
	return __PM_SUCCESS;
}

int __PM_ParameterReturn_consume(void* parameter, void* input) {
	return __PM_SAME;
}
int __PM_ParameterReturn_operate(void* parameter, void* input) {
	__PM_Parameter_header* header;
	__PM_Meta* meta;
	int size,i;
	byte* byte_input;
	byte* data;

	byte_input = (byte*) input;

	meta = (__PM_Meta*) parameter;
	header = (__PM_Parameter_header*)__PM_Node_get_data(meta);
	data = ((byte*)header) + sizeof(__PM_Parameter_header);
	size = meta->size - sizeof(__PM_Parameter_header) - sizeof(__PM_Meta);

	for (i = 0; i < size; i++) {
		*(byte_input++) = *(data++);
	}
	return __PM_SUCCESS;
}
byte __PM_any_dummy[__PM_ANY_DUMMY_SIZE];
int __PM_ParameterAny_consume(void* parameter, void* input) {
	return __PM_SAME;
}
int __PM_ParameterAny_operate(void* parameter, void* input) {
	return __PM_SUCCESS;
}

int __PM_ParameterEq_consume(void* parameter, void* input) {
	__PM_Parameter_header* header;
	__PM_Meta* meta;
	int size,i;
	byte* data;
	meta = (__PM_Meta*) parameter;
	header = (__PM_Parameter_header*)__PM_Node_get_data(meta);
	data = ((byte*)header) + sizeof(__PM_Parameter_header);
	size = meta->size - sizeof(__PM_Parameter_header) - sizeof(__PM_Meta);

	for (i = 0; i < size; i++) {
		if (data[i] != ((byte*)input)[i]) {
			return ! __PM_SAME;
		}
	}
	return __PM_SAME;
}



int __PM_ParameterEq_operate(void* parameter, void* input) {
	return __PM_SUCCESS;
}
__PM_Parameter_header* __PM_Parameter_new_(int parameter_size, __PM_Parameter_consume consume, __PM_Parameter_operate operate, void* input,int input_size, int child_count) {
	__PM_Parameter_header *parameter_header; 
	byte* data;
	byte* byte_input;
	int i; 

	byte_input = (byte*) input;

	parameter_header = __PM_Parameter_new(parameter_size, consume, operate, child_count);
	data = ((byte*)parameter_header) + sizeof(__PM_Parameter_header);

	for (i = 0; i < input_size; i++) {
		*(data++) = *(byte_input++);
	}

	return parameter_header; 
}


void _PMWillCallWithoutInstrument(void* called_object, void* original_function, void* forward_function,int defined_parameter_count, int parameter_count, int from_times, int to_times, int is_forward, ...)  {
	int is_return_set;

	if (defined_parameter_count == parameter_count) {
		is_return_set = 0;
	} else {
		__PM_Assert(defined_parameter_count+1 == parameter_count);
		is_return_set = 1;
	}
	__PM_MockRecord_new(original_function, forward_function, from_times, to_times, parameter_count, is_return_set, is_forward);
}




void _PMWillCall(void* called_object, void* original_function, void* forward_function,int defined_parameter_count, int parameter_count, int from_times, int to_times, int is_forward, ...)  {
	__PM_Instrument_do(original_function, forward_function);
	_PMWillCallWithoutInstrument(called_object,  original_function,  forward_function,defined_parameter_count, parameter_count, from_times, to_times, is_forward);
}
void __PMTimes_(int min, int max) {
	__PM_MockRecord* mock_record;
	__PM_Meta* mock;

	mock = __PM_Stack_get_last_meta(__PM_Stack_get_instance());
	mock_record = (__PM_MockRecord*)__PM_Node_get_data(mock);
	mock_record->min_times = min;
	mock_record->max_times = max;

}


//void testUniversalMock_get_instance(void) {} UniveralMock does not have state

static int __PM_UniveralMock_check_all_parameter_match(__PM_Meta *mock, __PM_Meta *parameter, _mock_function_paremeter_header_type_template* header) {
	int i;
	int all_success;
	void* input;
	__PM_Parameter_header* parameter_header;

	all_success = __PM_SUCCESS;
	for (i =0; i < mock->child_count; i++) {
		parameter_header = (__PM_Parameter_header*)__PM_Node_get_data(parameter);
		input = header->field_reference[i];
		if (parameter_header->consume(parameter, input) !=__PM_SAME) {
			all_success = __PM_FAIL;
		}
		parameter = __PM_Node_get_sible(parameter);
	}
	return all_success;
}
void __PM_UniveralMock_process_matched_mock(__PM_MockRecord* mock_record, __PM_Meta *mock, _mock_function_paremeter_header_type_template* header) {
	__PM_Meta *parameter;
	__PM_Parameter_header* parameter_header;
	void* input;
	int i;
	
	mock_record->called++;
	parameter = __PM_Node_get_child(mock);
	for (i =0; i < mock->child_count; i++) {
		parameter_header = (__PM_Parameter_header*)__PM_Node_get_data(parameter);
		input = header->field_reference[i];
		__PM_Assert(parameter_header->operate(parameter, input) ==__PM_SUCCESS);
		parameter = __PM_Node_get_sible(parameter);
	}
}
int __PM_UniveralMock_process_matched_mock_with_times_check(__PM_MockRecord* mock_record, __PM_Meta *mock, _mock_function_paremeter_header_type_template* header) {
	__PM_Assert(mock_record->max_times != 0);
	if (mock_record->called < mock_record->max_times) {
			__PM_UniveralMock_process_matched_mock(mock_record, mock, header);
			return __PM_SUCCESS;
	} 
	return __PM_FAIL;
}
int __PM_UniveralMock_check_mock_record_and_called_function_match(__PM_MockRecord* mock_record, _mock_function_paremeter_header_type_template* called_function_header) {
	return mock_record->to == called_function_header->function;
}
int __PM_UniveralMock_process_mocks(__PM_Meta *mock, _mock_function_paremeter_header_type_template* input_parameter) {
	__PM_Meta *mock_sible, *parameter;
	__PM_MockRecord* mock_record;

	if (mock == 0) {
		return __PM_FAIL;
	}
	mock_sible = __PM_Node_get_sible(mock);
	if (__PM_UniveralMock_process_mocks(mock_sible, input_parameter) == __PM_SUCCESS) {
		return __PM_SUCCESS;
	} 

	parameter = __PM_Node_get_child(mock);
	mock_record = (__PM_MockRecord*)__PM_Node_get_data(mock);
	if (__PM_UniveralMock_check_mock_record_and_called_function_match(mock_record, input_parameter) == __PM_SUCCESS 
		&& __PM_UniveralMock_check_all_parameter_match(mock, parameter,  input_parameter) == __PM_SUCCESS ) {
			if (__PM_UniveralMock_process_matched_mock_with_times_check(mock_record, mock, input_parameter) ==__PM_SUCCESS) {
				return __PM_SUCCESS;
			}
	}
	return __PM_FAIL;
}
void __PM_UniveralMock_process(void* parameter_data) {
	__PM_Meta *mock;
	_mock_function_paremeter_header_type_template* input_parameter_header;

	input_parameter_header = (_mock_function_paremeter_header_type_template*)parameter_data;
	mock = __PM_Stack_get_last_meta(__PM_Stack_get_instance());

	if (__PM_UniveralMock_process_mocks(mock, input_parameter_header) ==__PM_SUCCESS) {
		return;
	}
	__PM_Check_To_Pause_Or_Set_Flag(__PM_FAIL);
}



int __PM_UniveralMock_check_consume_(void) {
	__PM_Meta *mock;
	__PM_MockRecord* mock_record;
	mock = __PM_Stack_get_last_meta(__PM_Stack_get_instance());
	if (mock == 0) {
		return 	__PM_SUCCESS;	
	}
	do {
		mock_record = (__PM_MockRecord*)__PM_Node_get_data(mock);
		if (mock_record == 0) {
			continue;
		}
		if ((mock_record->called < mock_record->min_times)
			|| (mock_record->called > mock_record->max_times)) {
				return __PM_FAIL;
		}
	} while((mock = __PM_Node_get_sible(mock)) != 0);
	return __PM_SUCCESS;
}



