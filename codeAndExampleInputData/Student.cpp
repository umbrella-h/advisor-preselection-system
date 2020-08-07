# include <iostream>
# include <vector>
# include <string>
# include "Student.h"

using namespace std;

Student::Student(const string n, const string i, const int g, const vector<Person*> h, const vector<Person*> o):Person(n,i), grade(g){

	for(int i=0; i<h.size(); i++)
        historyTeacher.push_back(h[i]);
    for(int i=0; i<o.size(); i++)
        teacherOrder.push_back(o[i]);   
}

int Student::getGrade(){
    return grade;
}

//alter_0622_2100
vector<Person*> Student::getHistoryTeacher(){
	 return historyTeacher; 
}

vector<Person*> Student::getTeacherOrder(){
	 return teacherOrder; 
} 
//---------------

void Student::print()const {
	 cout << "[Student's] \n";
    cout << "name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "grade: " << grade << endl;
    cout << "history teacher: ";
    for(int i=0; i<historyTeacher.size(); i++)
        cout << historyTeacher[i]->getName() << ".  ";
    cout << endl;
    cout << "teacher order: ";
    for(int i=0; i<teacherOrder.size(); i++)
        cout << teacherOrder[i]->getName() << ".  ";
    cout << endl;
    cout << "-----------------------" << endl;

}
