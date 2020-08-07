#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H
#include <vector>
#include <map>
#include "Person.h"
#include "Student.h"
#include "Teacher.h"


class Distributor {
    private:
        std::vector<Teacher*> tVec;
        std::vector<Student*> sVec;
        std::map<Teacher*, std::vector<Student*>> resultTS;
        std::map<Teacher*, int> teacherAcceptedNum;
        std::map<Student*, Teacher*> resultST;        
        
    public:
        Distributor(std::vector<Teacher*>& t, std::vector<Student*>& s);
        void distribute();
        void printResult();
        std::map<Teacher*, std::vector<Student*>> getResultTS();
        std::map<Student*, Teacher*> getResultST();
        std::vector<Student*> getStudentByTeacher(Teacher* oneT);
        Teacher* getTeacherByStudent(Student* oneS);
        void addStudentToTeacher(Student& aS, Teacher& aT);           
        
};

#endif

