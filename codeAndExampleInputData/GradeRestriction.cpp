# include "GradeRestriction.h"
# include "Person.h"
# include "Student.h"
# include "Rule.h"
# include <iostream>

using namespace std;

GradeRestriction::GradeRestriction(int res, Person* t):Rule(t), restrictionGrade(res){ };

bool GradeRestriction::studentIsAccepted(Student* s){
    if ((s->getGrade()) >= restrictionGrade)
        return true;
    else
        return false;
}

void GradeRestriction::printRule() {
    cout << "Rule No." << ruleNum << " is \"GradeRestriction to Student.\"" << endl;
    cout << "Student should at least be at grade " << restrictionGrade << "." << endl;
}
