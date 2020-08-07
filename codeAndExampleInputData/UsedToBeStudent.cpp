# include "UsedToBeStudent.h"
# include "Rule.h"
# include "Student.h"
# include <iostream>

using namespace std;

UsedToBeStudent::UsedToBeStudent(Person* t):Rule(t) {}


bool UsedToBeStudent::studentIsAccepted(Student* s){
    
    for(auto it = (s->getHistoryTeacher()).begin(); it != (s->getHistoryTeacher()).end(); it++) {
        if ((*it)->getName() == teacher->getName()){
            return true;
        }
    }
    
    return false; 
}


void UsedToBeStudent::printRule() {
    cout << "Rule No." << ruleNum << " is \"UsedToBeStudent\"" << endl;
    cout << "Student should have been taughted by teacher " << teacher->getName() << endl;
}