# ifndef RULE_H
# define RULE_H
# include "Person.h"
# include "Student.h"

class Rule {
    protected:
        Person* teacher = nullptr;
    public:
        Rule() = default;
        Rule(Person* t) {teacher = t;}
        virtual bool studentIsAccepted(Student* s) = 0;
        virtual void printRule() = 0;
};
# endif