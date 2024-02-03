#ifndef _PERSON_H
#define _PERSON_H
//header files
#include <string>
#include <iostream>
/*
    Person class
*/
class Person
{
    private:
        int age; // stores person age
        std::string name; //stores the naem of person
        int numberOfFriends; // stores number of friends, useful for array
        std::string password;                      //stores person's password
        std::string placeOfBirth;                      //stores person's date of birth

    public:
        ~Person(); // Destructor to verify it's been deleted
        int getAge() const;               // gets age of person 
        std::string getName() const;        //gets name of person
        operator std::string() const;         // operator string() overloading
        int getNumberOfFriends() const;                 //gets number of friends
        std::string getPlaceOfBirth() const;                  //gets place of birth
        friend std::ostream & operator << (std::ostream & out, const Person & p); // operator << overloading
        Person(std::string name, int age, std::string placeOfBirth, int numberOfFriends); //constructor with 4 parameters
};
#endif