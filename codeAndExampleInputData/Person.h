# ifndef PERSON_H
# define PERSON_H
# include <iostream>

class Person {
    protected:
        std::string name;
        std::string id;
    public:
        Person(const std::string name, const std::string id);
        std::string getName() const;
        std::string getId() const;
        virtual void print() const;
};

# endif
