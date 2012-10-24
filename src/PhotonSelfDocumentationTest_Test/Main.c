#include "PhotonSelfDocumentationTest.h"

Feature(SimpleFeatureDefinition) {

}

Feature(Description_simple) {
		Description("xxxxx"
					"YYYY")
}

typedef struct AA {
	int a;
}DummyStruct;
DummyStruct dummyStruct;
Feature(Given_a_variable) {
		Description("xxxxx"
					"YYYY")
		Given()
		A_(struct AA *dummyStruct2; int j);
		An_(int k);
		j=0;
		k=0;
		dummyStruct2 = &dummyStruct;
}

Feature(Given_a_list) {
		Description("xxxxx"
					"YYYY")
		Given()
		A_(int variable5; struct AA *dummyStruct2) ;
		A_list_(int, variable1, 2,,2);
		A_list_(int, variable2, 2,,2);
		A_set_(int, variable3, 1, 2);
		A_set_(int, variable4, 1, 2);

		variable5=0;
		dummyStruct2 = &dummyStruct;
		variable1=0;
		variable2=0;
		variable3=0; 
		variable4=0;
		__PP_variable3_To=0;
		__PP_variable4_To=0;
		__PP_variable3_From=0;
		__PP_variable4_From=0;

}
Feature(Given_a_set_char) {
	Description("xxxxx"
				"YYYY")
	Given()
	A_set_(struct {int a; int b;}, variable, {1,2}, {2,4});
	A_(int i);
	i=0;

	PPLoopAll1(variable) { // use Scenario instead of PPLoopAll Ex)  Scenario(Scenario name, with_combination_of, variable1, variable1) {
		i++;
		Expect_equal_(i, variable->a);
		Expect_equal_(i*2, variable->b);
	}
	Expect_equal_(2, i);
}
Feature(Given_a_set_struct) {
	Description("xxxxx"
				"YYYY")
	Given()
		A_set_(struct {int a;  struct {int c;int d;}b;}, variable, {1,{2, 4}}, {2,{4, 8}});
		A_(int i);
		i=0;

	PPLoopAll1(variable) { // use Scenario instead of PPLoopAll Ex)  Scenario(Scenario name, with_combination_of, variable1, variable1) {
		i++;
		Expect_equal_(i, variable->a);
		Expect_equal_(i*2, variable->b.c);
		Expect_equal_(i*4, variable->b.d);
	}
	Expect_equal_(2, i);
}





Feature(Given_a_list_is_by) {
		Description("xxxxx"
					"YYYY")
		Given() 
		A_list_(int, variable1 is 2,,2);
		A_list_(int, variable2 is 2,,2 by 1);
		A_set_(int, variable3 is 1, 2);
		A_set_(int, variable4 is 1, 2);

		variable1=0;
		variable2=0;
		variable3=0; 
		variable4=0;
		__PP_variable3_To=0;
		__PP_variable4_To=0;
		__PP_variable3_From=0;
		__PP_variable4_From=0;

}





Feature(ScenarioSimple) {
		Description("xxxxx"
					"YYYY")
		Given()
		An_(int count);
		count = 0;

		Scenario (fly) {
			count = 1;
		}
		Expect_equal_(1, count);
}





Feature(Story_with_each_of) {
	Description("xxxxx"
				"YYYY")
	int i =0;
	int toCompare1[] = {2,3};
	int toCompare2[] = {3,4};
	Given() 
	A_list_(int, wing , 2,,3 );
	A_list_(int, motor , 3,,4);

	Scenario (fly, with_each_of, wing, motor) {
		Expect_equal_(toCompare1[i], a_(wing));
		Expect_equal_(toCompare2[i++], a_(motor));
	}
}




Feature(Story_with_combination_of) {
	Description("xxxxx"
				"YYYY")
	int i =0;
	int toCompare1[] = {2,2,3,3};
	int toCompare2[] = {3,4,3,4};
	Given() 
		A_list_(int, wing , 2,,3 );
		A_list_(int, motor , 3,,4);

	Scenario (fly, with_combination_of, wing, motor) {
		Expect_equal_(toCompare1[i], a_(wing));
		Expect_equal_(toCompare2[i++], a_(motor));
	}
}

Feature(Story_in_out_list_combination) {
	Description("xxxxx"
				"YYYY")
	int i =0;
	int toCompare1[] = {2,2,2,2,2,2,3,3,3,3,3,3};
	int toCompare2[] = {3,3,3,4,4,4,3,3,3,4,4,4};
	int toCompare3[] = {5,6,7,5,6,7,5,6,7,5,6,7};
	Given() 
		A_list_(int, tail);
		A_list_(int, wing , 2,,3 );
		A_list_(int, motor , 3,,4);

	Scenario (fly, with_combination_of, wing, motor, tail) {
		Given() 
			The_list_(tail , 5,,7 )

		Expect_equal_(toCompare1[i], a_(wing));
		Expect_equal_(toCompare2[i], a_(motor));
		Expect_equal_(toCompare3[i++], a_(tail));
	}
}
Feature(Story_in_out_list_each) {
	Description("xxxxx"
				"YYYY")
	int i =0;
	int toCompare1[] = {2,3,2};
	int toCompare2[] = {3,4,3};
	int toCompare3[] = {5,6,7};
	Given() 
		A_list_(int, tail);
		A_list_(int, wing , 2,,3 );
		A_list_(int, motor , 3,,4);

	Scenario (fly, with_each_of, wing, motor, tail) {
		Given() 
			The_list_(tail , 5,,7 )

		Expect_equal_(toCompare1[i], a_(wing));
		Expect_equal_(toCompare2[i], a_(motor));
		Expect_equal_(toCompare3[i++], a_(tail));
	}
}
Feature(Story_in_out_set_each) {
	Description("xxxxx"
				"YYYY")
	int i =0;
	int toCompare1[] = {2,3,2};
	int toCompare2[] = {3,4,3};
	int toCompare3[] = {5,6,7};
	Given() 
	PPSet(int, tail);
	A_list_(int, wing , 2,,3 );
	A_list_(int, motor , 3,,4);

	Scenario (fly, with_each_of, wing, motor, tail) {
		Given() 
		The_set_(int, tail , 5,6,7 )

		Expect_equal_(toCompare1[i], a_(wing));
		Expect_equal_(toCompare2[i], a_(motor));
		Expect_equal_(toCompare3[i++], a_(tail));
	}
}
Feature(Story_in_out_set_combination) {
	Description("xxxxx"
				"YYYY")
	int i =0;
	int toCompare1[] = {2,2,2,2,2,2,3,3,3,3,3,3};
	int toCompare2[] = {3,3,3,4,4,4,3,3,3,4,4,4};
	int toCompare3[] = {5,6,7,5,6,7,5,6,7,5,6,7};
	Given() 
		A_set_(int, tail);
		A_list_(int, wing , 2,,3 );
		A_list_(int, motor , 3,,4);

	Scenario (fly, with_combination_of, wing, motor, tail) {
		Given() 
			The_set_(int, tail , 5,6,7 )

		Expect_equal_(toCompare1[i], a_(wing));
		Expect_equal_(toCompare2[i], a_(motor));
		Expect_equal_(toCompare3[i++], a_(tail));
	}
}

Feature(Story_in_out_table_set_each) {
	Description("xxxxx"
				"YYYY")
	int i =0;
	int toCompare1[] = {2,3,2};
	int toCompare2[] = {3,4,3};
	int toCompare3[] = {5,6,7};
	Given() 
	A_table_(tail, {int a; int b;});
	A_list_(int, wing , 2,,3 );
	A_list_(int, motor , 3,,4);

	Scenario (fly, with_each_of, wing, motor, tail) {
		Given() 
		//The_set_(int, tail , 5,6,7 )
		The_table_(
			tail, 
			{int a; int b;},  
			{1,5},
			{1,6},
			{1,7}
		);

		Expect_equal_(toCompare1[i], a_(wing));
		Expect_equal_(toCompare2[i], a_(motor));
		Expect_equal_(toCompare3[i++], tail->b);
	}
}
Feature(Story_in_out_table_set_combination) {
	Description("xxxxx"
				"YYYY")
	int i =0;
	int toCompare1[] = {2,2,2,2,2,2,3,3,3,3,3,3};
	int toCompare2[] = {3,3,3,4,4,4,3,3,3,4,4,4};
	int toCompare3[] = {5,6,7,5,6,7,5,6,7,5,6,7};
	Given() 
	A_table_(tail, {int a; int b;});
	A_list_(int, wing , 2,,3 );
	A_list_(int, motor , 3,,4);

	Scenario (fly, with_combination_of, wing, motor, tail) {
		Given() 
		//The_set_(int, tail , 5,6,7 )
		The_table_(
			tail, 
			{int a; int b;},  
			{1,5},
			{1,6},
			{1,7}
		);

		Expect_equal_(toCompare1[i], a_(wing));
		Expect_equal_(toCompare2[i], a_(motor));
		Expect_equal_(toCompare3[i++], tail->b);
	}
}
Feature(Story_table_set_combination) {
	Description("xxxxx"
				"YYYY")
	int i =0;
	int toCompare1[] = {2,2,2,2,2,2,3,3,3,3,3,3};
	int toCompare2[] = {3,3,3,4,4,4,3,3,3,4,4,4};
	int toCompare3[] = {5,6,7,5,6,7,5,6,7,5,6,7};
	Given() 
	A_table_(
		tail, 
		{int a; int b;},  
		{1,5},
		{1,6},
		{1,7}
	);
	A_list_(int, wing , 2,,3 );
	A_list_(int, motor , 3,,4);

	Scenario (fly, with_combination_of, wing, motor, tail) {
		Given() 
		
		Expect_equal_(toCompare1[i], a_(wing));
		Expect_equal_(toCompare2[i], a_(motor));
		Expect_equal_(toCompare3[i++], tail->b);
	}
}
Feature(Story_table_set_each) {
	Description(
		"This Test Case test table and list parameterized test."
		"'with_each_of' is used to test all elements of table and list at least once.")
	int i =0;
	int toCompareWing[] = {2,3,2};
	int toCompareMortor[] = {3,4,3};
	int toCompareTailB[] = {5,6,7};
	Given() 
	A_table_(
		tail, 
		{int a; int b;},  
		{1,5},
		{1,6},
		{1,7}
	);
	A_list_(int, wing , 2,,3 );
	A_list_(int, motor , 3,,4);

	Scenario (fly, with_each_of, wing, motor, tail) {
		Given() 
		
		Expect_equal_(toCompareWing[i], a_(wing));
		Expect_equal_(toCompareMortor[i], a_(motor));
		Expect_equal_(toCompareTailB[i++], tail->b);
	}
}


int isFlyDone = 0;
int fly(int wing, int motor, int tail) {
	isFlyDone =1;
	return wing*motor;
}
int callEmptyParamter(){
	return 0;
}
int equals_with(int expected, int result) {
	Expect_equal_(expected, result);
	return 0;
}
There_is_type_(int);
Used_type_is_(int);
int inner(int input){return input;}
int return_five_inner(int input) {return 5;}
It_may_(inner, int, input, and_return_type_of_(int));
int outter(int input) {return inner(input);}
int zero_returner() {return 0;}
void one_accepter(int input) {Expect_equal_(1, input);}
int nothing() {return 0;}
void do_nothing(void){}
int return_nothing_called=0;
void return_nothing(){return_nothing_called=1;}
int _integer(int expected, int result) {
	return expected - result;
}
Feature(When) {
	Description("xxxxx"
				"YYYY")
	int i =0;
	int toCompare1[] = {2,3,2};
	int toCompare2[] = {3,4,3};
	int toCompare3[] = {5,6,7};
	Given() 
	A_list_(int, tail);
	A_list_(int, wing , 2,,3 );
	A_list_(int, motor , 3,,4);

	Scenario (fly, with_each_of, wing, motor, tail) {
		Given() 
		The_list_(tail , 5,,7 )
		i =0;
		isFlyDone=0;
		_BDD_init();
		__BDD_When_Before = do_nothing;
		__BDD_When_After = do_nothing;
		It_return_(wing*motor, _integer) when_it_(fly, wing, motor, tail)   {
			Expect_equal_(0,isFlyDone);
			Expect_equal_(0,i++);
		}
		Expect_equal_(1,isFlyDone);
		Expect_equal_(1,i++);
		When_it_(callEmptyParamter);
		_BDD_init();
	}
	Scenario (function_does_not_return) {
		Given() 
		The_list_(tail , 5,,7 )
		i =0;
		isFlyDone=0;
		When_it_(outter, 3) it_cause  {
			Expect_equal_(0,i++);
		}
		Expect_equal_(1,i++);
	}
	Scenario (function_return_check) {
		It_return_(1, _integer) when_it_(zero_returner);
	}
	Scenario (function_return_less_than_check) {
		It_return_(less_than, 2, _integer) when_it_(zero_returner);
	}
	Scenario (function_input_check) {
		When_it_(one_accepter, 1);
	}
	Scenario (function_using_mock) {
		It_return_(1, _integer) when_it_(outter,3) {
			And_it_(inner, _(3,int), then_return_(1,int));
		}
	}
	Scenario (function_using_mock_times) {
		It_return_(1, _integer) when_it_(outter,3) {
			And_it_(inner, _(3,int), then_return_(1,int));times_(1);
		}
	}
	Scenario (function_using_manual_mock) {
		It_return_(5, _integer) when_it_(outter,3) {
			And_when_it_(inner, it_(return_five_inner));
		}
	}
	
}
int secondExecuted = 0;
int firstExecuted = 0;
Feature(sample_multiple_scenario) {
	Description("xxxxx"
				"YYYY")
	
	Given() 


	Scenario (first) {
		firstExecuted =1;		
	}
	Scenario (second) {
		secondExecuted =1;
	}
}

Feature(multiple_scenario_get_count) {
	Description("")
	
	Given() 
	
	Scenario (get_count) {
		*scenario_target_index =0;
		sample_multiple_scenario(_BDD_GET_SIZE, scenario_current_index, scenario_target_index, scenario_target_size, 0,0,0, scenario_target_names,  scenario_target_name_remain);
		Expect_equal_(2, *scenario_target_size);
	}
}

Feature(multiple_scenario_get_index) {
	Description("")
	
	Given() 
	
	Scenario (get_count) {
		*scenario_target_size =0;
		*scenario_current_index =0;
		scenario_target_names[0] = "second";
		sample_multiple_scenario(_BDD_GET_INDEX, scenario_current_index, scenario_target_index, scenario_target_size, 0, 0, 0, scenario_target_names, scenario_target_name_remain);
		Expect_equal_(2, *scenario_target_index);
	}
	Scenario (execute_one) {
		*scenario_target_index =2;
		*scenario_current_index =0;
		scenario_target_names[0] = "second";
		firstExecuted = 0;
		secondExecuted = 0;
		sample_multiple_scenario(_BDD_EXECUTE_SELECTED, scenario_current_index, scenario_target_index,scenario_target_size, 0,0, 0, scenario_target_names,  scenario_target_name_remain);
		Expect_equal_(0, firstExecuted);
		Expect_equal_(1, secondExecuted);
	}
}

Feature(include_feature) {
	firstExecuted = 0;
	secondExecuted = 0;
	Include_feature_(sample_multiple_scenario);
	Expect_equal_(1, firstExecuted);
	Expect_equal_(1, secondExecuted);
}


Feature(feature_to_include_other_feature1) {
	Include_feature_(sample_multiple_scenario);
}
Feature(feature_to_include_other_feature2) {
	Include_feature_(feature_to_include_other_feature1);
}

Feature(include_feature_get_index) {
	char* _scenario_target_names[4];
	int buffer_scenario_target_index[] = {0,0,0,0,0,0};
	_scenario_target_names[0] = "feature_to_include_other_feature2";
	_scenario_target_names[1] = "feature_to_include_other_feature1";
	_scenario_target_names[2] = "sample_multiple_scenario";
	_scenario_target_names[3] = "second";
	*scenario_target_name_remain = 3;
	*scenario_current_index =0;
	scenario_mode = _BDD_GET_INDEX;
	scenario_target_names = _scenario_target_names;
	scenario_target_index = buffer_scenario_target_index;
	Include_feature_(feature_to_include_other_feature2);
	Expect_equal_(1, scenario_target_index[0]);
	Expect_equal_(1, scenario_target_index[1]);
	Expect_equal_(1, scenario_target_index[2]);
	Expect_equal_(2, scenario_target_index[3]);
}

Feature(include_feature_get_index_wrong_name) {
	char* _scenario_target_names[4];
	int buffer_scenario_target_index[] = {0,0,0,0,0,0};
	_scenario_target_names[0] = "feature_to_include_other_feature2";
	_scenario_target_names[1] = "feature_to_include_other_feature1";
	_scenario_target_names[2] = "sample_multiple_scenario";
	_scenario_target_names[3] = "wrong_name";
	*scenario_target_name_remain = 3;
	*scenario_current_index =0;
	scenario_mode = _BDD_GET_INDEX;
	scenario_target_names = _scenario_target_names;
	scenario_target_index = buffer_scenario_target_index;
	Include_feature_(feature_to_include_other_feature2);
	Expect_equal_(1, scenario_target_index[0]);
	Expect_equal_(1, scenario_target_index[1]);
	Expect_equal_(1, scenario_target_index[2]);
	Expect_equal_(0, scenario_target_index[3]);
}
Feature(include_feature_execute) {
	int buffer_scenario_target_index[] = {1,1,1,2};
	*scenario_target_name_remain = 3;
	*scenario_current_index =0;
	scenario_mode = _BDD_EXECUTE_SELECTED;
	scenario_target_names = 0;
	scenario_target_index = buffer_scenario_target_index;

	firstExecuted = 0;
	secondExecuted = 0;

	Include_feature_(feature_to_include_other_feature2);

	Expect_equal_(0, firstExecuted);
	Expect_equal_(1, secondExecuted);
}

Feature(include_feature_execute_not_full_path) {
	int buffer_scenario_target_index[] = {1,1,1,0};
	*scenario_target_name_remain = 3;
	*scenario_current_index =0;
	scenario_mode = _BDD_EXECUTE_SELECTED;
	scenario_target_names = 0;
	scenario_target_index = buffer_scenario_target_index;

	firstExecuted = 0;
	secondExecuted = 0;

	Include_feature_(feature_to_include_other_feature2);

	Expect_equal_(1, firstExecuted);
	Expect_equal_(1, secondExecuted);
}


//Feature(study_do_while_can_be_on_for_statement) {
	//for(;;do{}while(1)) {}	
//}
/*Feature(check_two_goto1) {
	int i=0;
label1:	
	goto label2;
label2:
	//for (i=0; i<2; goto label1) {}

	//if (1) 
	//	try {} catch(...){};
}
Feature(check_two_goto2) {
label1:	
	return;
}*/
//#define Test_feature_(Name) Feature_##Name
#define some_feature(name) void a_##name()

#define quatation_macro(A) #A
Feature(Study_quatation_macro) {
	char* text = quatation_macro("hello world");
}
#define Call_each(...) 
#define Feature_set(Name, ...) void Feature_set##Name() {  }
#define Test_feature_(Name) Name(scenario_mode, scenario_current_index, scenario_target_index, scenario_target_size, scenario_current_index_temp, scenario_target_index_temp, scenario_target_size_temp, scenario_target_names,  scenario_target_name_remain)



Application(Self_documetation) {
	Features() {
		Include_feature_(SimpleFeatureDefinition);
		Include_feature_(Description_simple);
		Include_feature_(Given_a_variable);
		Include_feature_(Given_a_set_char);
		Include_feature_(Given_a_set_struct);
		Include_feature_(Given_a_list);
		Include_feature_(Given_a_list_is_by);
		Include_feature_(ScenarioSimple);
		Include_feature_(Story_with_each_of);
		Include_feature_(Story_with_combination_of);
		Include_feature_(Story_in_out_list_combination);
		Include_feature_(Story_in_out_list_each);
		Include_feature_(Story_in_out_set_combination);
		Include_feature_(Story_in_out_set_each);
		Include_feature_(Story_in_out_table_set_combination);
		Include_feature_(Story_in_out_table_set_each);
		Include_feature_(Story_table_set_combination);
		Include_feature_(Story_table_set_each);
		//Test_feature_(Scenario_two) ;
		Include_feature_(When) ;
		Include_feature_(multiple_scenario_get_count);
		Include_feature_(Study_quatation_macro);
		Include_feature_(multiple_scenario_get_index);
		Include_feature_(include_feature);
		Include_feature_(include_feature_get_index);
		Include_feature_(include_feature_get_index_wrong_name);
		Include_feature_(include_feature_execute);
		Include_feature_(include_feature_execute_not_full_path);
	}
}

void main(void) {
	Self_documetation();

}