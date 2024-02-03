#include "person.h"
// destructor shows they've been logged out
Person::~Person()
{
    std::cout << "\nYOU HAVE BEEN LOGGED OUT !!!\n\n";
}
// gets age and return
int Person::getAge() const
{
    return age;
}
// gets and returns name
std::string Person::getName() const
{
    return name;
}
/*
    prints simplified details in a specific format, eg
        -Samuel Jackson (55) born in the US.
*/
Person::operator std::string() const 
{
    std::string value;
    value = "  - " + this->name + " (" + std::to_string(this->age) + ") born in " + this->placeOfBirth + "."; 
    return value;
}
// gets and return number of friend
int Person::getNumberOfFriends() const
{
    return numberOfFriends;
}
// gets and return place of birth
std::string Person::getPlaceOfBirth() const
{
    return placeOfBirth;
}
/*
    prints details in a specified format, eg
    Welcome Susie Marley!
    Your age is 45
    You were born in the UK.
    You have 3 friends and they are 
        -Samuel Jackson (55) born in the US.
        -Leslie Winkle (33) born in Australia.
        -Cristiano Ronaldo NOT REGISTERED.
*/
std::ostream & operator << (std::ostream & out, const Person & p)
{
    out << "Welcome " << p.name << "!\nYour age is " << p.age << ".\nYou have " << p.numberOfFriends << " friends and they are\n";
    return out;
}
// constructor and adding to variables via constructor list
// shows they've been logged in if succesful
Person::Person(std::string name, int age, std::string placeOfBirth,int numberOfFriends):name(name),age(age),placeOfBirth(placeOfBirth),numberOfFriends(numberOfFriends)
{
    std::cout << "YOU HAVE SUCCESSFULLY LOGGED IN !!!\n\n";
}