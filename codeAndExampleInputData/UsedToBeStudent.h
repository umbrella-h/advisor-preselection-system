#ifndef USEDTOBESTUDENT_H
#define USEDTOBESTUDENT_H
#include <string>
#include "Rule.h"
#include "Person.h"
#include "Student.h"
#include "Teacher.h"

class UsedToBeStudent : public Rule {
    private:
        int ruleNum = 2;
    public:
        UsedToBeStudent(Person* t);
        virtual bool studentIsAccepted(Student* s);
        virtual void printRule();
};

#endif