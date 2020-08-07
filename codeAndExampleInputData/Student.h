# ifndef STUDENT_H
# define STUDENT_H
# include <vector>
# include <string>
# include "Person.h"

class Student : public Person{
    private:
        int grade;
        std::vector<Person*> historyTeacher; 
        std::vector<Person*> teacherOrder; 
        
    public:
        Student(const std::string n, const std::string i, const int g, const std::vector<Person*> h, const std::vector<Person*> o);//(name, id, history, order)
        int getGrade();
        std::vector<Person*> getHistoryTeacher();
		std::vector<Person*> getTeacherOrder();
        void print()const override;
        ~Student() = default;
};

#endif
