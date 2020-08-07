# include <iostream>
# include <fstream>
# include <vector>
# include <string>
# include <sstream>
# include <typeinfo>
# include <cstring>
# include "Person.h"
# include "Student.h"
# include "Teacher.h"
# include "Rule.h"
# include "GradeRestriction.h"
# include "UsedToBeStudent.h"
# include "Distributor.h"

using namespace std;

vector<Teacher*> createTeacher();
vector<Student*> readStudent(string, vector<Teacher*>);
void deleteStudentVector(vector<Student*>);

int main() {
	vector<Teacher*> tp_vec = createTeacher();
	vector<Student*> sp_vec = readStudent("StudentList.csv",tp_vec);

	/*for(int i=0;i<sp_vec.size();i++)
		sp_vec[i]->print();

	for(int i=0; i<tp_vec.size(); i++)
		tp_vec[i]->print();*/
	
	Distributor dis = Distributor(tp_vec, sp_vec);
	
	dis.distribute();
	dis.printResult();//----comment this if you don't need the long output.

	cout << sp_vec[0]->getName() << " is assigned to Prof." 
		<< dis.getTeacherByStudent(sp_vec[0])->getName() << "! Congratulations!\n"<< endl;
		
	cout << "Prof." << tp_vec[0]->getName() 
		<< " is going to have a good year with the students, " << endl;
	for(int i=0; i< dis.getStudentByTeacher(tp_vec[0]).size(); i++){
		cout << dis.getStudentByTeacher(tp_vec[0])[i]->getName() << ". ";
	}
	cout<< "\nCongratulations!\n\n";
	
	map<Teacher*, vector<Student*>> mapResultTS = dis.getResultTS();
	map<Student*, Teacher*> mapResultST = dis.getResultST(); 
		
		 
   return 0;
}

vector<Teacher*> createTeacher() {
	ifstream fin;
	fin.open("TeacherList.csv");
	
	string line;
    vector<string> teacherNameList;
    vector<string> teacherIdList;
	vector<int> numLimitList;
	vector<int> gradeLimitList;
	vector<int> taughtRuleList;
    while (getline(fin, line)){
    	string id;
    	string name;
		string numLimitString;
		int numLimit;
		string gradeLimitString;
		int gradeLimit;
		string taughtRuleString;
		int taughtRule;
		stringstream sin(line);

		getline(sin, name, ',');
		getline(sin, id, ',');
		getline(sin, numLimitString, ',');
		getline(sin, gradeLimitString, ',');
		getline(sin, taughtRuleString, ',');

		numLimit = stoi(numLimitString);
		gradeLimit = stoi(gradeLimitString);
		taughtRule = stoi(taughtRuleString);

        teacherNameList.push_back(name);
        teacherIdList.push_back(id);
		numLimitList.push_back(numLimit);
		gradeLimitList.push_back(gradeLimit);
		taughtRuleList.push_back(taughtRule);
    }


	vector<Teacher*> teachers;
	for(int i=0; i<teacherNameList.size(); i++) {
		Teacher* t = new Teacher(teacherNameList[i], teacherIdList[i], numLimitList[i]);
		teachers.push_back(t);
	}

	for(int i=0; i<teacherNameList.size(); i++){
		if(gradeLimitList[i] != 0){
			GradeRestriction* gr = new GradeRestriction(gradeLimitList[i], teachers[i]);
			teachers[i]->setRule(gr);
		}
		if(taughtRuleList[i] != 0){
			UsedToBeStudent* utbs = new UsedToBeStudent(teachers[i]);
			teachers[i]->setRule(utbs);
		}
	}

	return teachers;
}

vector<Student*> readStudent(string fileName, vector<Teacher*> tp_vec){
    vector<Student*> sp_vec;
    Student* student = nullptr;

    ifstream inFile;
    inFile.open(fileName);
    if (!inFile){
            cout << "Fail to open file" << endl;
            exit(1);
    }
    string line;
    while(getline(inFile,line)){
        string name;
        string id;
        int grade;
        string temp;
        vector<Person*> h;
        vector<Person*> o;

        istringstream sin(line);

        getline(sin, name, ',');
        getline(sin, id, ',');
        getline(sin, temp, ',');
        grade = stoi(temp);
        for(int i=0;i<6;i++){
            getline(sin, temp, ',');
            if(temp != "N"){
                int id = stoi(temp);
                h.push_back(tp_vec[id]);
            }
        }  
        for(int j=0;j<3;j++){
            getline(sin, temp, ',');
            if(temp != "N"){
                int id = stoi(temp);
                o.push_back(tp_vec[id]);
            }
        }
        //cout << o.size() << endl;
        student = new Student(name,id,grade,h,o);
        sp_vec.push_back(student);

    }
    return sp_vec;

}

void deleteStudentVector(vector<Student*> sp){
    for(int i=0 ; i<sp.size() ; i++){
        delete sp[i];//////error: *sp[i]
    }
    sp.clear();
}
