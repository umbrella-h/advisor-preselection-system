#ifndef GRADERESTRICTION_H
#define GRADERESTRICTION_H
#include <vector>
#include <string>
#include "Rule.h"
#include "Person.h"
#include "Student.h"

class GradeRestriction : public Rule{
    private:
        int ruleNum = 1;
        int restrictionGrade = 0;
    public:
        GradeRestriction() = default;
        GradeRestriction(int res, Person* t);
        bool studentIsAccepted(Student* s) override;
        void printRule() override;
};

#endif