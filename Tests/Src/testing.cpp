#include "testing.hpp"
#include "main.hpp"

//----------------Variables------------------
group * firstGroup; // Pointer to first group
//---------------Class methods---------------
// Allows for outside char * output functions
void TestFramework::printOut(const char* n) {
    // Add custom print() function here
    print(n);
} 

// New group creation function
group::group(const char * t){
	addToGroupList(this);
	groupName = t;
}

// Report group results
void group::report(){
    int correct_counter = 0;
    int bad_counter = 0;
    char buff[20];
    TestFramework Frame;
    node<test_result> *temp=new node<test_result>;
    temp=head;
    Frame.printOut("----------------------------\n");
    Frame.printOut("Group report: ");
    Frame.printOut(groupName);
    Frame.printOut("\n----------------------------\n");
    while(temp!=nullptr)
    {
        if (!temp->data.res){
            bad_counter++;
            Frame.printOut("Test Failed: "); 
            Frame.printOut(temp->data.exact);
            Frame.printOut("\n");
        }
        else
            correct_counter++;
        temp=temp->next;
    }
    Frame.printOut("\n");
    Frame.printOut("Passed tests: ");
    convertChar(correct_counter, buff);
    Frame.printOut(buff);
    Frame.printOut("\n");
    Frame.printOut("Failed tests: ");
    convertChar(bad_counter, buff);
    Frame.printOut(buff);
    Frame.printOut("\n");
}

// Read and store every test result in group
void group::f_Test(bool eval, const char * exact){
    test_result results;
    results.res = eval;
    results.exact = exact;
    appendTo(results);
} 
//----------------Functions------------------
// Int to char* conversion
char *convertChar(int number, char *buff){
    if (number / 10 == 0) {
        *buff++ = number + '0';
        *buff = '\0';
        return buff;
    }
    buff = convertChar(number / 10, buff);
    *buff++ = number % 10 + '0';
    *buff = '\0';
    return buff;
}

// Adds new group pointer to last group
void addToGroupList(group * n){
	group* temp;
	temp=firstGroup;
	if(firstGroup==nullptr){
	   	firstGroup=n;
	   	firstGroup->nextG=nullptr;
	}
	else{
	   	while(temp->nextG != nullptr)
	   		temp=temp->nextG;
	   	temp->nextG = n;
	   	n->nextG = nullptr;
	}
}

// Report all results
void report_all(){
    group* temp = firstGroup;
    while(temp!=nullptr){
        temp->report();
        temp=temp->nextG;
    }
}
