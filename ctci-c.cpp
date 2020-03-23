#include <iostream>
using namespace std;

// defines a macro- what is a macro in c++? 
#define NAME_SIZE 50

class Person {
    int id; // all members are PRIVATE by default- is this the same in typescript?
    char name[NAME_SIZE];

    public:
        void aboutMe() { // void: nothing returned
            cout << "I am a person";
        }
};

class Student: public Person { // I think : means extend
    public:
        void aboutMe() {
            cout << "I am a student";
        }
};

int main() {
    Student * p = new Student(); // I think this is where we create a pointer to a new student class
    p->aboutMe(); // prints "I am a student"-- this is shorthand for allocating memory
    delete p; // delete the memory allocation
    return 0;
}