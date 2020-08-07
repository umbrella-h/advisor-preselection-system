#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "Distributor.h"

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

Distributor::Distributor(vector<Teacher*>& t, vector<Student*>& s){

	for(int i=0; i<t.size(); i++){
		tVec.push_back(t[i]);
      teacherAcceptedNum[t[i]] = 0;
   }
   for(int i=0; i<s.size(); i++){
		sVec.push_back(s[i]);        
   }
}

map<Teacher*, vector<Student*>> Distributor::getResultTS(){ 
	return resultTS; 
}

map<Student*, Teacher*> Distributor::getResultST(){ 
	return resultST; 
}

vector<Student*> Distributor::getStudentByTeacher(Teacher* oneT){	
	return resultTS[oneT];
}

Teacher* Distributor::getTeacherByStudent(Student* oneS){
	return resultST[oneS];
}


void Distributor::addStudentToTeacher(Student& aS, Teacher& aT){
    Student* sp = &aS;
    Teacher* tp = &aT;
    resultTS[tp].push_back(sp);
    resultST[sp] = tp;
    teacherAcceptedNum[tp] ++; 
}

void Distributor::distribute(){
	int orderNum = 3;
	cout <<endl << "===============Steps===============\n\n";
	srand((unsigned)time(NULL));
	cout<< "( random seed: " << (unsigned)time(NULL) << " )\n";
			
	for(int i=0; i!= orderNum; ++i){	
		cout<<"\n------------[ Step_"<< (i+1) <<" ]-------------\n\n";
		cout << "Teacher/   TimesChosenByStudents/  redundancy/\n";
		for(decltype(tVec.size()) k=0; k!= tVec.size(); ++k){
			vector<int> tempS;// index for calling Student* s in sVec. 
									// record of srudents going to be assigned in this step. 
			vector<Student*> tempNextS;// index for calling Student* s in sVec.
												// record of srudents going to be assigned in the next step
												
			for(int j=0; j< sVec.size(); j++){
				//cout << "@@@@@@\n" << 	sVec[j]->getTeacherOrder()[i] << endl;			
				if(tVec[k]==sVec[j]->getTeacherOrder()[i] 
						&& tVec[k]->validate(sVec[j])){					
					tempS.push_back(j);				
				}else{
					tempNextS.push_back(sVec[j]);
				}										
			}
			int redundancy = teacherAcceptedNum[tVec[k]] + tempS.size() 
				- tVec[k]->getLimit();//	(eg. -2: still able to accept 2 students)
				
			cout<< " "<< tVec[k]->getName() << "          "<< tempS.size() 
				<< "                " << redundancy << endl;
			
			if(redundancy > 0){				
				for(int n=0; n< redundancy; n++){
					int eraseIndex = rand() % tempS.size();
					tempNextS.push_back(sVec[tempS[eraseIndex]]);
					tempS.erase(tempS.begin() + eraseIndex);					
				}
			}
			for(int m=0; m< tempS.size(); m++){
				addStudentToTeacher(*sVec[tempS[m]], *tVec[k]);
			}
			sVec.clear();
			for(int m=0; m< tempNextS.size(); m++){			
				sVec.push_back(tempNextS[m]);
			}
			if (sVec.empty())	{
				return;
			}								
		}		
	}	
	
	//-------the last two random assignment steps---------------------------
	
	cout<<"\n------------[ Step_"<< orderNum + 1 
		<<" ]-------------\n"<<endl;
	cout << "Teacher/   TimesChosenByStudents/  redundancy/\n";
		
	int sumR = 0;// sum of redundancy of all of the teachers
	vector<int> rVec;// redundancy of available teachers (eg. -2: still able to accept 2 students)
	vector<int> lastTVec;// index for calling available Teacher* s in tVec		
	vector<int> indexS;// index for calling Student* s in sVec.
							 // If the number of students is less than -sumR,
							 // the last serveral(ps. -sumR-sVec.size()) indexes is fake(could be thought as fake students)
	vector<Student*> tempNextS1;
							 
							 
	//vector<int> indexNextS;// record of srudents going to be assigned in the next step
	
	for(decltype(tVec.size()) k=0; k!= tVec.size(); ++k){
		int redundancy = teacherAcceptedNum[tVec[k]] + 0 - tVec[k]->getLimit();
		cout<< " "<< tVec[k]->getName() << "          "<< 0 << "                " 
			<< redundancy << endl;
		sumR += redundancy;
		
		if(redundancy <0){
			lastTVec.push_back(k);
			rVec.push_back(redundancy);	
		}	
	}
	
	for(int i =0; i< -sumR; i++){
		indexS.push_back(i);
	}

	// Fill Teacher 
	
	for(int i=0; i< lastTVec.size(); i++){
		Teacher* &currentTeacher = tVec[lastTVec[i]];
		for(int j=0; j< -rVec[i]; j++){
			int chosenIndex = rand() % indexS.size();
			int &chosenStudentIndex = indexS[chosenIndex];
			Student* chosenStudent = sVec[indexS[chosenIndex]];
			//cout << chosenStudentIndex << " ";
			if( chosenStudentIndex < sVec.size() && currentTeacher->validate(chosenStudent)){
				//currentTeacher->addStudent(chosenStudent);
				addStudentToTeacher(*chosenStudent, *currentTeacher);	
				indexS.erase(indexS.begin() + chosenIndex);										
			}
			else if(chosenStudentIndex < sVec.size() && !currentTeacher->validate(chosenStudent)){
				// Not Valid Student, Do Nothing		
			}else{
				// Empty, nothing to add to Teacher 
				indexS.erase(indexS.begin() + chosenIndex);
			}
		}		
	}
	
	for(int m=0; m< indexS.size(); m++){
		if(indexS[m]<sVec.size()){
				tempNextS1.push_back(sVec[indexS[m]]);
			}	
	}	
	sVec.clear();
	for(int m=0; m< tempNextS1.size(); m++){			
		sVec.push_back(tempNextS1[m]);
	}
	if (sVec.empty())	{
		return;
	}

	cout<<"\n------------[ Step_"<< orderNum + 2 
		<<" ]-------------\n"<<endl;
	cout << "Teacher/   TimesChosenByStudents/  redundancy/\n";	
	sumR =0;
	rVec.clear();
	lastTVec.clear();
	indexS.clear();// index for calling Student* s in sVec.
							 // If the number of students is less than -sumR,
							 // the last serveral(ps. -sumR-sVec.size()) indexes is fake(could be thought as fake students)
							 
	for(decltype(tVec.size()) k=0; k!= tVec.size(); ++k){
		int redundancy = teacherAcceptedNum[tVec[k]] + 0 - tVec[k]->getLimit();
		cout<< " " << tVec[k]->getName() << "         "<< 0 << "               " 
			<< redundancy << endl;
		sumR += redundancy;
		
		if(redundancy <0){
			lastTVec.push_back(k);
			rVec.push_back(redundancy);	
		}	
	}
	for(int i =0; i< -sumR; i++){
		indexS.push_back(i);
	}					 	
	for(int i=0; i< lastTVec.size(); i++){
		for(int j=0; j< -rVec[i]; j++){
			int chosenIndex = rand() % indexS.size();
			if(indexS[chosenIndex] < sVec.size()){
				addStudentToTeacher(*sVec[indexS[chosenIndex]], *tVec[lastTVec[i]]);							
			}
			indexS.erase(indexS.begin() + chosenIndex);
			if (indexS[0] >= sVec.size()){
				return;
			}	
		}
	}	
}

void Distributor::printResult(){
	cout <<endl << "===============Student===============" <<endl <<endl;
	for(int i=0; i<tVec.size();i++){
		for(int j=0; j< resultTS[tVec[i]].size(); j++){
			resultTS[tVec[i]][j]->print();
			cout << "Assignment Result: " << resultST[resultTS[tVec[i]][j]]->getName() << "\n";
			cout << "--------------------------------------#\n\n";
		}
	}	
	cout <<endl << "===============Teacher===============" <<endl <<endl;
	for(int i=0; i<tVec.size();i++){
		tVec[i]->print();
		cout << "Student List: ";
      for (int j=0; j<resultTS[tVec[i]].size(); j++){
        cout << resultTS[tVec[i]][j]->getName() << ". ";
      }
      cout << "\n--------------------------------------#\n\n";
	}		
}
