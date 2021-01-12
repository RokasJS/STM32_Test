#ifndef TESTING_HPP_INCLUDED
#define TESTING_HPP_INCLUDED

//---------Function Prototypes---------
// Int to char* conversion
char * convertChar(int number, char *buff);
void report_all();
//---------------Structs---------------
// Hold temporary test results
struct test_result {    
    bool res;
    const char * group;
    const char * exact;
  };

// Generic linked list node
template<class T>
struct node {
	node<T>* next;
	T data;
};

//---------------Classes---------------
// Parent generic linked list class
template<class T>
class LList {
  public:
    node<T>* head;
    node<T>* next;
    LList<T>() {
      head = nullptr;
      next = nullptr;
    }
    ~LList<T>(){
    	node<T>* current = head;
    	while( current != 0 ) {
    		node<T>* next = current->next;
    	    delete current;
    	    current = next;
    	}
    	head = 0;
    }
    virtual void appendTo(T data) {
      node<T>* temp=new node<T>;
      temp->data=data;
      temp->next=nullptr;
      if(head==nullptr) {
          head=temp;
          next=temp;
          temp=nullptr;
      }
      else {
          next->next=temp;
          next=temp;
      }
    }
};

// Group child class
class group: public LList<test_result>{
	public:
	  group(const char * t);
	  const char * groupName;
	  group* nextG;
	  void report();
	  void f_Test(bool eval, const char * exact);
};

// Required for listing all groups
extern group* firstGroup;
void addToGroupList(group * n);

// Allow for outside char * output functions
class TestFramework { 
public:
    virtual void printOut(const char* n);
};

//----------------Macros----------------
// Spawn new group class instance 
#define NEW_GROUP(name)             \
group * name = new group(#name);    \
//groupCounter.appendTo(name);

// Test group body
#define TEST_G(name)                \
  bool test_##name(void);           \
  bool var_##name = test_##name();  \
  bool test_##name(void)            \
{ USING_GROUP(name)    

// Create temporary pointer to class 
#define USING_GROUP(name)           \
  group * tmp = name;   

// Change temporary pointer to class
#define CHANGE_GROUP(name)          \
  tmp = name;  

// Required for test group body
#define END return 0; } 

// Check if condition is true 
#define TEST(check)                 \
  tmp->f_Test(check, #check);

// Report group results
#define REPORT(name)                \
  name->report();

// Report all results
#define REPORT_ALL                  \
  report_all();

#endif
