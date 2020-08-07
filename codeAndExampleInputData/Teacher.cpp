# include "Teacher.h"
# include "Person.h"
# include "Student.h"
# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

Teacher::Teacher(const string n, const string i, const int l) : Person(n, i), limit(l) { }; // (name, id, limit)

void Teacher::print() const {
    cout << "[Teacher's]: " << endl;
    Person::print();
    cout << "The limit of student number is: " << limit << endl;
    cout << "Rule: " << endl;
    for(auto it = rules.begin(); it != rules.end(); it++){
        (*it)->printRule();
    }
    cout << endl;
}

void Teacher::setRule (Rule* r){
    rules.push_back(r);
}

int Teacher::getLimit(){
    return limit;
}

bool Teacher::validate(Student* s){
    for(auto it = rules.begin(); it != rules.end(); it++){
        bool accepted = false;
        if((*it)->studentIsAccepted(s)){
            accepted = true;
        }else{
            return false;
        }
        return accepted;
    }
    return true;
}
