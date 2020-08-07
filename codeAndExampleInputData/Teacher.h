# ifndef TEACHER_H
# define TEACHER_H
# include <vector>
# include <iostream>
# include "Person.h"
# include "Student.h"
# include "Rule.h"

class Teacher : public Person {
    private:
        int limit; // limit of the number of students
        std::vector<Rule*> rules;
    public:
        Teacher();
        Teacher(const std::string n, const std::string i, const int l); // (name, id, limit)
        void print() const override;
        void setRule(Rule* r);
        bool validate(Student* s);
        int getLimit();
        ~Teacher() = default;        
};

# endif
