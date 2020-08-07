# include <iostream>
# include "Person.h"
# include <string>
using namespace std;

Person::Person(const string name = "NAS", const string id = "NAS") : name(name), id(id) {}

string Person::getName() const { return name; }

string Person::getId() const { return id; }

void Person::print() const{
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
}
