#include "..\PhotonMock\PhotonMockPP.h"

#define PTAssert(Expected, Actual) if (Expected != Actual) while(1);
#define PTAssertTrue(Expression) if (!(Expression)) while(1);

extern "C" void runPhotonMockTests(void);

#define PMMockClassDeclare(class_name) class PMMock##class_name : public class_name 
#define PMMockClass(class_name) PMMock##class_name 

#define PMMOCK_USE_INSTANCE_ID 0
#define PMMOCK_USE_STATIC_ID 1


//WillCall... Interface functions

#define PMWillCallVirtualInstance(...) PMWillCallVirtualInstance_((__VA_ARGS__ ,1))
#define PMWillCallVirtualInstance_(variables) PMWillCallVirtualInstance__ variables
//_mock_function_paremeter_count_##function_name's address is used instead virtual function address because it can be bigger than void*
//It is unique for each virtual function mock. So it wouldn't make any problem.
#define PMWillCallVirtualInstance__(object_pointer, function_name, ...) _PMWillCall(\
	(void*)(object_pointer),\
	(void*)&(object_pointer->_mock_virtual_function_id_##function_name),\
	(void*)&(object_pointer->_mock_virtual_function_id_##function_name),\
	_mock_function_paremeter_count_##function_name , __PM_ArgumentCounter(__VA_ARGS__)-1, 1 , 1, __PM_CALL_MODE_WillCall, __VA_ARGS__)


#define PMWillCallVirtual(...) PMWillCallVirtual_((__VA_ARGS__ ,1))
#define PMWillCallVirtual_(variables) PMWillCallVirtual__ variables
//_mock_function_paremeter_count_##function_name's address is used instead virtual function address because it can be bigger than void*
//It is unique for each virtual function mock. So it wouldn't make any problem.
#define PMWillCallVirtual__(class_name, function_name, ...) PMMock##class_name::_mock_virtual_function_id_selector_##function_name=PMMOCK_USE_STATIC_ID;_PMWillCallWithoutInstrument(\
	(void*)(__PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE),\
	(void*)&(PMMock##class_name::_mock_virtual_function_static_id_##function_name),\
	(void*)&(PMMock##class_name::_mock_virtual_function_static_id_##function_name),\
	PMMock##class_name::_mock_function_paremeter_count_##function_name , __PM_ArgumentCounter(__VA_ARGS__)-1, 1 , 1, __PM_CALL_MODE_WillCall, __VA_ARGS__)

#define PMWillCallMemberInstance(...) PMWillCallMemberInstance_((__VA_ARGS__ ,1))
#define PMWillCallMemberInstance_(variables) PMWillCallMemberInstance__ variables
#define PMWillCallMemberInstance__(class_name, function_name, ...) _PMWillCallMemberInstance(\
	(void*)(object_pointer),\
	object_pointer->_mock_get_target_function_pointer_##class_name##function_name(),\
	object_pointer->_mock_get_mock_function_pointer_##class_name##function_name(),\
	_mock_function_paremeter_count_##function_name , __PM_ArgumentCounter(__VA_ARGS__)-1, 1 , 1, __PM_CALL_MODE_WillCall, __VA_ARGS__)

#define PMWillCallMember(...) PMWillCallMember_((__VA_ARGS__ ,1))
#define PMWillCallMember_(variables) PMWillCallMember__ variables
#define PMWillCallMember__(class_name, function_name, ...) _PMWillCall(\
	(void*)(__PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE),\
	PMMock##class_name::_mock_get_target_function_pointer_##class_name##function_name(),\
	PMMock##class_name::_mock_get_mock_function_pointer_##class_name##function_name(),\
	PMMock##class_name::_mock_function_paremeter_count_##function_name , __PM_ArgumentCounter(__VA_ARGS__)-1, 1 , 1, __PM_CALL_MODE_WillCall, __VA_ARGS__)

#define PMWillForwardMember(class_name, from_function, to_function) \
	PMMock##class_name::_mock_get_target_function_pointer_##class_name##to_function = PMMock##class_name::_mock_function_pointer_to_void##class_name##to_function(&class_name::from_function);\
	PMMock##class_name::_mock_get_mock_function_pointer_##class_name##to_function = PMMock##class_name::_mock_function_pointer_to_void##class_name##to_function((PMMock##class_name::_mock_function_pointer##class_name##to_function)&PMMock##class_name::to_function);\
	_PMWillCall(__PM_UniveralMock_CALLED_OBJECT_DOES_NOT_CARE, PMMock##class_name::_mock_get_target_function_pointer_##class_name##to_function, PMMock##class_name::_mock_get_mock_function_pointer_##class_name##to_function , -1 ,-1, 0 , __PM_MAX_INT, __PM_CALL_MODE_Forward)	
//PMWillForward(PMMock##class_name::_mock_get_target_function_pointer_##class_name##to_function, PMMock##class_name::_mock_get_mock_function_pointer_##class_name##to_function)


//PMMockMemberForward

#define PMMockMemberForward(...) __PM_ArgumentCounterWithCall(PMMockMemberForward, __VA_ARGS__)
#define PMMockMemberForwardDeclare(...) __PM_ArgumentCounterWithCall(PMMockMemberForwardDeclare, __VA_ARGS__)

#define PMMockMemberForwardDeclare23(class_name,function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type,...)  PMMockMemberForwardDeclare23_(class_name,function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type)
#define PMMockMemberForwardDeclare23_(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type) \
	static int _mock_function_paremeter_count_##function_name ;\
	static void* _mock_function_pointer_to_void##class_name##function_name(\
		return_type (class_name::*function_pointer)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10));\
	static void* _mock_get_target_function_pointer_##class_name##function_name;\
	static void* _mock_get_mock_function_pointer_##class_name##function_name;\
	typedef return_type (class_name::*_mock_function_pointer##class_name##function_name)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10);\
	return_type function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10);

#define PMMockMemberForward23(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type, ...)  PMMockMemberForward23_(class_name,function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type)
#define PMMockMemberForward23_(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type) \
	int PMMock##class_name::_mock_function_paremeter_count_##function_name = 10;\
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
	union {\
		PMMock##class_name::_mock_function_pointer##class_name##function_name function_pointer; \
		void* void_pointer; \
	}_mock_temp_function_pointer##class_name##function_name;\
	void* PMMock##class_name::_mock_function_pointer_to_void##class_name##function_name(\
			return_type (class_name::*function_pointer)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10)) {\
		_mock_temp_function_pointer##class_name##function_name.function_pointer = function_pointer;\
		return _mock_temp_function_pointer##class_name##function_name.void_pointer;\
	}\
	void* PMMock##class_name::_mock_get_target_function_pointer_##class_name##function_name;\
	void* PMMock##class_name::_mock_get_mock_function_pointer_##class_name##function_name;\
	return_type PMMock##class_name::function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10)


#define PMMockMemberForwardDeclare22(class_name,function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, ...)  PMMockMemberForwardDeclare22_(class_name,function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10)
#define PMMockMemberForwardDeclare22_(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10) \
	static int _mock_function_paremeter_count_##function_name ;\
	static void* _mock_function_pointer_to_void##class_name##function_name(\
		void (class_name::*function_pointer)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10));\
	static void* _mock_get_target_function_pointer_##class_name##function_name;\
	static void* _mock_get_mock_function_pointer_##class_name##function_name;\
	typedef void (class_name::*_mock_function_pointer##class_name##function_name)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10);\
	void function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10);

#define PMMockMemberForward22(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, ...)  PMMockMemberForward22_(class_name,function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10)
#define PMMockMemberForward22_(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10) \
	int PMMock##class_name::_mock_function_paremeter_count_##function_name = 10;\
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
	union {\
		PMMock##class_name::_mock_function_pointer##class_name##function_name function_pointer; \
		void* void_pointer; \
	}_mock_temp_function_pointer##class_name##function_name;\
	void* PMMock##class_name::_mock_function_pointer_to_void##class_name##function_name(\
			void (class_name::*function_pointer)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10)) {\
		_mock_temp_function_pointer##class_name##function_name.function_pointer = function_pointer;\
		return _mock_temp_function_pointer##class_name##function_name.void_pointer;\
	}\
	void* PMMock##class_name::_mock_get_target_function_pointer_##class_name##function_name;\
	void* PMMock##class_name::_mock_get_mock_function_pointer_##class_name##function_name;\
	void PMMock##class_name::function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10)

//PMMockMember

#define PMMockMember(...) __PM_ArgumentCounterWithCall(PMMockMember, __VA_ARGS__)
#define PMMockMemberDeclare(...) __PM_ArgumentCounterWithCall(PMMockMemberDeclare, __VA_ARGS__)

#define PMMockMemberDeclare23(class_name,function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type, ...)  PMMockMemberDeclare23_(class_name,function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type)
#define PMMockMemberDeclare23_(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type) \
	static int _mock_function_paremeter_count_##function_name ;\
	static void* _mock_function_pointer_to_void##class_name##function_name(\
		return_type (class_name::*function_pointer)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10));\
	static void* _mock_get_target_function_pointer_##class_name##function_name(void);\
	static void* _mock_get_mock_function_pointer_##class_name##function_name(void) ;\
	return_type function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10);

#define PMMockMember23(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type, ...)  PMMockMember23_(class_name,function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type)
#define PMMockMember23_(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type) \
	int PMMock##class_name::_mock_function_paremeter_count_##function_name = 10;\
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
	typedef return_type (class_name::*_mock_function_pointer##class_name##function_name)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10);\
	union {\
		_mock_function_pointer##class_name##function_name function_pointer; \
		void* void_pointer; \
	}_mock_temp_function_pointer##class_name##function_name;\
	void* PMMock##class_name::_mock_function_pointer_to_void##class_name##function_name(\
			return_type (class_name::*function_pointer)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10)) {\
		_mock_temp_function_pointer##class_name##function_name.function_pointer = function_pointer;\
		return _mock_temp_function_pointer##class_name##function_name.void_pointer;\
	}\
	void* PMMock##class_name::_mock_get_target_function_pointer_##class_name##function_name(void) {\
		return _mock_function_pointer_to_void##class_name##function_name(&class_name::function_name);\
	}\
	void* PMMock##class_name::_mock_get_mock_function_pointer_##class_name##function_name(void) {\
		return _mock_function_pointer_to_void##class_name##function_name((_mock_function_pointer##class_name##function_name)&PMMock##class_name::function_name);\
	}\
	return_type PMMock##class_name::function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10) {\
		return_type return_value;\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = this;\
		parameter.header.function_reference = _mock_function_pointer_to_void##class_name##function_name((_mock_function_pointer##class_name##function_name)&PMMock##class_name::function_name);\
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


#define PMMockMemberDeclare22(class_name,function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, ...)  PMMockMemberDeclare22_(class_name,function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10)
#define PMMockMemberDeclare22_(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10) \
	static int _mock_function_paremeter_count_##function_name ;\
	static void* _mock_function_pointer_to_void##class_name##function_name(\
		void (class_name::*function_pointer)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10));\
	static void* _mock_get_target_function_pointer_##class_name##function_name(void);\
	static void* _mock_get_mock_function_pointer_##class_name##function_name(void) ;\
	void function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10);

#define PMMockMember22(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, ...)  PMMockMember22_(class_name,function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10)
#define PMMockMember22_(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10) \
	int PMMock##class_name::_mock_function_paremeter_count_##function_name = 10;\
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
	typedef void (class_name::*_mock_function_pointer##class_name##function_name)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10);\
	union {\
		_mock_function_pointer##class_name##function_name function_pointer; \
		void* void_pointer; \
	}_mock_temp_function_pointer##class_name##function_name;\
	void* PMMock##class_name::_mock_function_pointer_to_void##class_name##function_name(\
			void (class_name::*function_pointer)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10)) {\
		_mock_temp_function_pointer##class_name##function_name.function_pointer = function_pointer;\
		return _mock_temp_function_pointer##class_name##function_name.void_pointer;\
	}\
	void* PMMock##class_name::_mock_get_target_function_pointer_##class_name##function_name(void) {\
		return _mock_function_pointer_to_void##class_name##function_name(&class_name::function_name);\
	}\
	void* PMMock##class_name::_mock_get_mock_function_pointer_##class_name##function_name(void) {\
		return _mock_function_pointer_to_void##class_name##function_name((_mock_function_pointer##class_name##function_name)&PMMock##class_name::function_name);\
	}\
	void PMMock##class_name::function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10) {\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = this;\
		parameter.header.function_reference = _mock_function_pointer_to_void##class_name##function_name((_mock_function_pointer##class_name##function_name)&PMMock##class_name::function_name);\
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

//PMMockVirtual

#define PMMockVirtual(...) __PM_ArgumentCounterWithCall(PMMockVirtual, __VA_ARGS__)
#define PMMockVirtualDeclare(...) __PM_ArgumentCounterWithCall(PMMockVirtualDeclare, __VA_ARGS__)

//_mock_virtual_function_id_##function_name's address is used instead virtual function address because it can be bigger than void*
//It is unique for each virtual function mock. So it wouldn't make any problem.
#define PMMockVirtualDeclare23(class_name,function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type, ...)  PMMockVirtualDeclare23_(class_name, function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type)
#define PMMockVirtualDeclare23_(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type) \
	int _mock_virtual_function_instance_id_##function_name;\
	static int _mock_function_paremeter_count_##function_name ;\
	static int _mock_virtual_function_static_id_##function_name;\
	static int _mock_virtual_function_id_selector_##function_name;\
	return_type function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10);
	

#define PMMockVirtual23(class_name,function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type, ...)  PMMockVirtual23_(class_name, function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type)
#define PMMockVirtual23_(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, return_type) \
	int PMMock##class_name::_mock_function_paremeter_count_##function_name = 10 ;\
	int PMMock##class_name::_mock_virtual_function_static_id_##function_name;\
	int PMMock##class_name::_mock_virtual_function_id_selector_##function_name;\
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
	typedef return_type (class_name::*_mock_function_pointer##class_name##function_name)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10);\
	return_type PMMock##class_name::function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10) {\
		return_type return_value;\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = this;\
		if (_mock_virtual_function_id_selector_##function_name == PMMOCK_USE_INSTANCE_ID) {\
			parameter.header.function_reference = &_mock_virtual_function_instance_id_##function_name;\
		}else{\
			parameter.header.function_reference = &_mock_virtual_function_static_id_##function_name;\
		}\
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



//_mock_virtual_function_id_##function_name's address is used instead virtual function address because it can be bigger than void*
//It is unique for each virtual function mock. So it wouldn't make any problem.
#define PMMockVirtualDeclare22(class_name,function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, ...)  PMMockVirtualDeclare22_(class_name, function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10)
#define PMMockVirtualDeclare22_(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10) \
	int _mock_virtual_function_instance_id_##function_name;\
	static int _mock_function_paremeter_count_##function_name ;\
	static int _mock_virtual_function_static_id_##function_name;\
	static int _mock_virtual_function_id_selector_##function_name;\
	void function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10);
	

#define PMMockVirtual22(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10, ...)  PMMockVirtual22_(class_name,function_name, T1, V1, T2, V2,T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10)
#define PMMockVirtual22_(class_name, function_name, T1, V1, T2, V2, T3, V3, T4, V4, T5, V5, T6, V6, T7, V7, T8, V8, T9, V9, T10, V10) \
	int PMMock##class_name::_mock_function_paremeter_count_##function_name = 10 ;\
	int PMMock##class_name::_mock_virtual_function_static_id_##function_name;\
	int PMMock##class_name::_mock_virtual_function_id_selector_##function_name;\
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
	typedef void (class_name::*_mock_function_pointer##class_name##function_name)(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10);\
	void PMMock##class_name::function_name(T1 V1, T2 V2, T3 V3, T4 V4, T5 V5, T6 V6, T7 V7, T8 V8, T9 V9, T10 V10) {\
		_mock_function_paremeter_type_##function_name parameter;\
		parameter.header.total_size = sizeof(_mock_function_paremeter_type_##function_name);\
		parameter.header.field_count = _mock_function_paremeter_count_##function_name;\
		parameter.header.called_object = this;\
		if (_mock_virtual_function_id_selector_##function_name == PMMOCK_USE_INSTANCE_ID) {\
			parameter.header.function_reference = &_mock_virtual_function_instance_id_##function_name;\
		}else{\
			parameter.header.function_reference = &_mock_virtual_function_static_id_##function_name;\
		}\
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

//will call member will call virtual
//self doc modification
//Neutrino Normal Type, Pointer, Struct, class
//Neutrino To Photon Mock
//Log semi-host
int OriginalFunctionCalled = 0;
class SampleClass {
public:
	int returnMember10(int _1,int _2, int _3, int _4, int _5, int _6, int _7, int _8, int _9, int _10){OriginalFunctionCalled=1;return 0;}
	int dum(int _1, int _2, int _3, int _4, int _5, int _6, int _7, int _8, int _9, int _10){OriginalFunctionCalled=1;return 0;}
	void voidMember10(int _1,int _2, int _3, int _4, int _5, int _6, int _7, int _8, int _9, int _10){OriginalFunctionCalled=1;}
	virtual int returnVirtual10(int _1,int _2, int _3, int _4, int _5, int _6, int _7, int _8, int _9, int _10){OriginalFunctionCalled=1;return 0;}
	virtual void voidVirtual10(int _1,int _2, int _3, int _4, int _5, int _6, int _7, int _8, int _9, int _10){OriginalFunctionCalled =1;}
};
PMMockClassDeclare(SampleClass) {
public:
	PMMockMemberForwardDeclare(SampleClass, voidMemberForward10, int, _1,int, _2, int, _3, int, _4, int, _5, int, _6, int, _7, int, _8, int, _9, int, _10);
	PMMockMemberForwardDeclare(SampleClass, returnMemberForward10, int, _1,int, _2, int, _3, int, _4, int, _5, int, _6, int, _7, int, _8, int, _9, int, _10, int);
	PMMockMemberDeclare(SampleClass, returnMember10, int, _1,int, _2, int, _3, int, _4, int, _5, int, _6, int, _7, int, _8, int, _9, int, _10, int);
	PMMockMemberDeclare(SampleClass, voidMember10, int, _1,int, _2, int, _3, int, _4, int, _5, int, _6, int, _7, int, _8, int, _9, int, _10);
	PMMockVirtualDeclare(SampleClass, returnVirtual10, int, _1,int, _2, int, _3, int, _4, int, _5, int, _6, int, _7, int, _8, int, _9, int, _10, int);
	PMMockVirtualDeclare(SampleClass, voidVirtual10, int, _1,int, _2, int, _3, int, _4, int, _5, int, _6, int, _7, int, _8, int, _9, int, _10);
};
int forwardCalled = 0;
PMMockMemberForward(SampleClass, voidMemberForward10, int, _1,int, _2, int, _3, int, _4, int, _5, int, _6, int, _7, int, _8, int, _9, int, _10) {forwardCalled = 1;}
PMMockMemberForward(SampleClass, returnMemberForward10, int, _1,int, _2, int, _3, int, _4, int, _5, int, _6, int, _7, int, _8, int, _9, int, _10, int ) {forwardCalled = 1;return 11;}
PMMockMember(SampleClass, returnMember10, int, _1,int, _2, int, _3, int, _4, int, _5, int, _6, int, _7, int, _8, int, _9, int, _10, int);
PMMockMember(SampleClass, voidMember10, int, _1,int, _2, int, _3, int, _4, int, _5, int, _6, int, _7, int, _8, int, _9, int, _10);
PMMockVirtual(SampleClass, returnVirtual10, int, _1,int, _2, int, _3, int, _4, int, _5, int, _6, int, _7, int, _8, int, _9, int, _10, int);
PMMockVirtual(SampleClass, voidVirtual10, int, _1,int, _2, int, _3, int, _4, int, _5, int, _6, int, _7, int, _8, int, _9, int, _10);

__PM_Parameter(int);
__PM_ParameterDeclare(int);

extern "C" int __PM_Assert_Or_Set_Flag_stop_mode;

void testWillCallVirtual_not_called(void) {
	PMInit();
	
	PMMockClass(SampleClass) sample;
	PMWillCallVirtual(SampleClass, voidVirtual10, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7),PMEq(int, 8),PMEq(int, 9),PMEq(int, 10));
	//sample.voidVirtual10(1, 2,3,4,5,6,7,8,9,10);
	
	__PM_MockRecord* mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));
	
	__PM_Assert( ! __PM_UniveralMock_check_consume_());

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}

void testWillCallVirtual_different_argument(void) {
	PMInit();

	__PM_Assert_Or_Set_Flag_stop_mode = 0;
	
	PMMockClass(SampleClass) sample;
	PMWillCallVirtual(SampleClass, voidVirtual10, PMEq(int, 2),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7),PMEq(int, 8),PMEq(int, 9),PMEq(int, 10));
	sample.voidVirtual10(1, 2,3,4,5,6,7,8,9,10);
	
	__PM_MockRecord* mock = (__PM_MockRecord*)__PM_Node_get_data(__PM_Stack_get_last_meta(__PM_Stack_get_instance()));

	__PM_Assert( ! __PM_UniveralMock_check_consume_());

	__PM_Stack_clean();
	__PM_Instrument_clean();	
}

void testWillForwardMember_10paramter_return(void) {
	PMInit();
	SampleClass sample;

	PMWillForwardMember(SampleClass, returnMember10, returnMemberForward10);
	int result = sample.returnMember10(1, 2,3,4,5,6,7,8,9,10);
	
	PTAssert(11, result);
	__PM_Assert(forwardCalled);
	PMVerify();
}

void testWillForwardMember_10paramter_no_return(void) {
	PMInit();
	SampleClass sample;

	PMWillForwardMember(SampleClass, voidMember10, voidMemberForward10);
	sample.voidMember10(1, 2,3,4,5,6,7,8,9,10);
	
	__PM_Assert(forwardCalled);
	PMVerify();
}

void testWillCallMember_10paramter_return(void) {
	PMInit();
	OriginalFunctionCalled = 0;
	SampleClass sample;
	
	PMWillCallMember(SampleClass, returnMember10, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7),PMEq(int, 8),PMEq(int, 9),PMEq(int, 10),PMReturn(int, 11));
	int result = sample.returnMember10(1, 2,3,4,5,6,7,8,9,10);
	
	PTAssert(11, result);
	PTAssert(0, OriginalFunctionCalled);
	PMVerify();
}

void testWillCallMember_10paramter_no_return(void) {
	PMInit();
	OriginalFunctionCalled = 0;
	SampleClass sample;

	PMWillCallMember(SampleClass, voidMember10, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7),PMEq(int, 8),PMEq(int, 9),PMEq(int, 10));
	sample.voidMember10(1, 2,3,4,5,6,7,8,9,10);
	
	PTAssert(0, OriginalFunctionCalled);
	PMVerify();
}

void testWillCallVirtual_10paramter_return(void) {
	PMInit();
	OriginalFunctionCalled = 0;
	PMMockClass(SampleClass) sample;
	
	PMWillCallVirtual(SampleClass, returnVirtual10, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7),PMEq(int, 8),PMEq(int, 9),PMEq(int, 10),PMReturn(int, 11));
	int result = sample.returnVirtual10(1, 2,3,4,5,6,7,8,9,10);
	
	PTAssert(11, result);
	PTAssert(0, OriginalFunctionCalled);
	PMVerify();
}

void testWillCallVirtual_10paramter_no_return(void) {
	PMInit();
	OriginalFunctionCalled = 0;
	PMMockClass(SampleClass) sample;
	
	PMWillCallVirtual(SampleClass, voidVirtual10, PMEq(int, 1),PMEq(int, 2),PMEq(int, 3),PMEq(int, 4),PMEq(int, 5),PMEq(int, 6),PMEq(int, 7),PMEq(int, 8),PMEq(int, 9),PMEq(int, 10));
	sample.voidVirtual10(1, 2,3,4,5,6,7,8,9,10);
	
	PTAssert(0, OriginalFunctionCalled);
	PMVerify();
}




extern "C" void runPhotonMockPPTest() {
	
	testWillCallVirtual_not_called();
	testWillCallVirtual_different_argument();

	testWillForwardMember_10paramter_return();

	testWillForwardMember_10paramter_no_return();

	testWillCallMember_10paramter_return();

	testWillCallMember_10paramter_no_return();

	testWillCallVirtual_10paramter_return();

	testWillCallVirtual_10paramter_no_return();
}
