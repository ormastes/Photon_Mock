#include "PhotonSelfDocumentationTest.h"
#ifdef WITH_DOC_GENERATION_CODE
#include <stdio.h>
#include <string.h>
#endif

int stringCompare(char* source, char* target){ 
	int i;
	for (i=0; source[i] == target[i]; i++) {
		if (source[i] == '\0') {
			return 0;
		}
	}
	return source[i] - target[i];
}


int _BDD_scenario_preprocessor(int scenario_mode, int* scenario_current_index, int* scenario_target_index, int* scenario_target_size,
		char** scenario_target_names, int* scenario_target_name_remain, char* scenario_current_name) {
	(*scenario_current_index)++;
	if (scenario_mode == _BDD_GET_SIZE) {
		(*scenario_target_size) ++;
		return 0;
	}
	if (scenario_mode == _BDD_GET_INDEX) {
		if (stringCompare(scenario_current_name, scenario_target_names[0])==0) {
			*scenario_target_index = *scenario_current_index;
		}
		return 0;
	}
	
	if (scenario_mode == _BDD_EXECUTE_SELECTED) {
		if (scenario_target_names == 0) {
			if (*scenario_current_index == *scenario_target_index || *scenario_target_index == 0) {
				return 1;
			} else {
				return 0;
			}
		} else {
			if (stringCompare(scenario_current_name, scenario_target_names[0])==0) {
				return 1;
			} else {
				return 0;
			}
		}
	}
	return 1;
}

int _BDD_group_preprocessor(int scenario_mode, int* scenario_current_index, int* scenario_target_index, int* scenario_target_size,
		char** scenario_target_names, int* scenario_target_name_remain, char* scenario_current_name) {
	(*scenario_current_index)++;
	if (scenario_mode == _BDD_GET_SIZE) {
		(*scenario_target_size) ++;
		return 0;
	}
	if (scenario_mode == _BDD_GET_INDEX) {
		if (stringCompare(scenario_current_name, scenario_target_names[0])==0) {
			*scenario_target_index = *scenario_current_index;
			return 1;
		} else {
			return 0;
		}
	}
	if (scenario_mode == _BDD_EXECUTE_SELECTED) {
		if (scenario_target_names == 0) {
			if (*scenario_current_index == *scenario_target_index) {
				return 1;
			} else {
				return 0;
			}
		} else {
			if (stringCompare(scenario_current_name, scenario_target_names[0])==0) {
				return 1;
			} else {
				return 0;
			}
		}
	}
	return 1;
}

void _BDD_assert(int expression) {
	while (! expression);
}

void_function __BDD_When_Before; 
void_function __BDD_When_After;


void _BDD_init() {
	__BDD_When_Before = _PMInit;
	__BDD_When_After = _PMVerify;
}

unsigned int __BDD_Index_ = 0;
unsigned int __BDD_Max_ = 0;
static int __BDD_group_currentID = 0;

__BDD_new_group_(Feature);
__BDD_new_group_(Component);
void __BDD_Global_Init(void) {
	__BDD_init_group_(Feature);
	__BDD_init_group_(Component);
}
#ifdef WITH_DOC_GENERATION_CODE
static char log_buffer[1000];
int buffer_index;
void __BDD_Append_log(int type, char* one, char* two) {
	char* text = "ddd" "fff";
		Description(xxxxx
				YYYY)
	switch(type) {
		case TYPE_It_return_:
			buffer_index = 0; 
			strcpy(log_buffer, two);
		case TYPE_when_it_:
			printf(text);
			printf(__BDD_description);
			printf("어플리케이션이 (%s)를 가지고 %s 할 때 %s를 리턴한다.\n",two, one, log_buffer);
	}
}

void __BDD_Documentation_log(char* log) {
	printf(log);
}
#endif
