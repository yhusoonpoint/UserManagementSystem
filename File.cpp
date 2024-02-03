//header files
#include <fstream>
#include <sstream>
#include <cstring>
#include <cctype>
#include "Person.h"
#include <regex>
using namespace std;
//checks if it's int or not
bool isDigit(const string & value)
{
    for (char const & i : value) 
    {
        if (std::isdigit(i) == 0) 
            return false;
    }
    return true;
}
// testing function to print array
void printArray(string * arrayToPrint, int & length)
{
     for(int i = 0;  i < length; i++)
    { 
           cout << arrayToPrint[i] << endl;
    }
}
// function that returns an int for error checking 
// it adds the data to the file and delete the entry after
int addToFile(string whatToWrite,const char * fileName)
{
    ofstream * file = new ofstream;
    (*file).open(fileName,std::ios_base::app);
    if(!(*file << endl << whatToWrite)){
        delete file;
        return 1;
    }
    delete file;
    return 0;
}
// Getline function that recurs if the input is empty 
// gets input via char and converts to string so it can be passed around easily
string & myGetLine(const string message, string & value, bool passwordEntry)
{
    char * temp = new char[256];
    cout << message;
    cin.getline(temp,256);
    value = temp;
    delete [] temp;
    if(value == "" || value == " " || (!passwordEntry && value.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos)) // makes sure no special character is written
    {
        cout << "\nError, Please Try Again.\n";
        value = myGetLine(message,value, passwordEntry);
    }
    return value;
}
/*
    Function to display message and ask for int
    loop makes sure an int is being entered.
*/
int & intGetLine(const string message, int & value)
{ 
    string * tempValue = new string;
    *tempValue = myGetLine(message,*tempValue,true);
    while(!isDigit(*tempValue))
    {
        cout << "\nError, Please Try Again.\n";
        *tempValue =  myGetLine(message,*tempValue,true);
    }
    return value = stoi(*tempValue);    
}
// Simple Hash function to encrpyt the password
// cant be decrepted so we call it when we also want to compare password data in file.
unsigned int RSHash(const char * str, unsigned int length)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	unsigned int i = 0;
	for (i = 0; i < length; ++str, ++i)
	{
		hash = hash * a + (*str);
		a = a * b;
	}
	return hash; // returns an integer value as encrption
}
// function to split word and return the location of the array created
string * splitter(string & word, char delimeter, const int & num)
{
    int j = 0;
    string * tempArray = new string[num];
    for(int i = 0; i < word.length() && j < num; i++)
    {
        if (word[i] == delimeter)
        {
            j++;
            continue;
        }
        tempArray[j] += word[i];
    }
    return tempArray;
}
// pointer function becuase it returning the location of an array created in it
// it checks the first value before the seperator to verify the user has a file, if not it sees the user in the friend session and assume it is there. 
string * readfromFile(const char * fileName, const string & nameOfPerson)
{
    ifstream * f = new ifstream(fileName);
    string * eachLineInFile = new string;
    while (getline(*f, *eachLineInFile)) 
    {
        if((*eachLineInFile).find(nameOfPerson) != string::npos) 
           { 
               
               string * temp = splitter(*eachLineInFile,'*', 6);
               if(nameOfPerson != temp[0])
               {
                    continue;
               }
                delete eachLineInFile,f;
                return temp;
           }
    }
    delete eachLineInFile,f;
    return NULL;
}
// function to print the details and make the person class
void makeAndPrintDetails(const string & name, const string & password, const char * fileName)
{
    //converts password to char * for the Hash function 
    char * passwordChar = new char[password.length()];
    strcpy(passwordChar, password.c_str());

    string * fileData = readfromFile(fileName,name);
    
    if(fileData && fileData[5] == to_string(RSHash(passwordChar,password.length())))
    {
        Person * p = new Person(fileData[0], stoi(fileData[1]), fileData[2], stoi(fileData[3]));
        cout << *p; // using the overload to print in the format we want.
        //uses splitter to seperate the file and sends it back as an array of data
        string * friends = splitter(fileData[4],',',(*p).getNumberOfFriends()); 
        // looping through the number of friends
        for(int i = 0; i < (*p).getNumberOfFriends(); i++)
        {
           fileData = readfromFile(fileName,friends[i]);
           //after reading from file it stores the array of data found and prints the details
           // if nothing is found then it tells the user
           if(fileData)
                cout << "   - " << fileData[0] << " (" << fileData[1] << ") born in " << fileData[2] << ".\n" ;
            else
                cout << "   - " << friends[i] << " IS NOT REGISTERED.\n";
        }
        delete [] friends;
        delete p;
    }
    else
        cout << "USER NOT FOUND!!!\n"; // if after the files, and the user is not found or if the file is not found it outputs this.
    delete [] fileData, passwordChar; //deletes data
}
//main function
int main()
{  
    /* 
        dynamically allocating local variables
    */
    int * age = new int;
    char * passwordChar;     
    int * choice = new int;
    bool * dontStop = new bool;   
    string * password = new string;
    string * tempHolder = new string;
    string * friendsName = new string;
    const char * fileName = "Data.txt";
    string * nameOfPerson = new string;
    string * placeOfBirth = new string;
    string * fileData = NULL;
    *dontStop = true;
    //loop to keep program running until iit has been exited
    while(*dontStop)
    {
        // using switch to sort out the input rather than if statement
        switch (intGetLine("Please select a number for the option of: \n   1- Login \n   2- Register \n   3- Exit \nOption:",*choice))
        {
        case 1:
            *nameOfPerson = myGetLine("Please type in name (Case Sentitive): ",*nameOfPerson,false);
            *password = myGetLine("Please type in password: ", *password,true);
            makeAndPrintDetails(*nameOfPerson, *password, fileName); // prints the details if they're correct.
            break;
        case 2:
            //checks if user already exist, it's placed here so user doesn't have to type in all value before it alerts.
            if(readfromFile(fileName,myGetLine("Please Type In Your Name: ", *nameOfPerson,false)))
            {
                cout << "\nUSER ALREADY EXIST!!!\n\n";
                break;
            }
            *age = intGetLine("Please type in Your age: ",*age);
            *password = myGetLine("Please create Your Password: ", *password,true);
            passwordChar = new char[(*password).length()];
            strcpy(passwordChar, (*password).c_str());
            *placeOfBirth = myGetLine("Please Type In Your Place of birth: ", *placeOfBirth,false);
            intGetLine("How many friends do you have? ",*choice);
            //looping through the number of friends they have and adding each frineds name seperating with a comma
            for(int i = 0; i < *choice; i++)
              *friendsName += ((*friendsName).length() != 0) ? ("," + myGetLine("Type in your friend's Full-Name (Case Sentitive): ", *tempHolder,false)) : (myGetLine("Type in your friend's Full-Name (Case Sentitive): ", *tempHolder,false)); 
            // adding to file using * as a seperator
            // if no error occured then it would print the details.
            if(addToFile(*nameOfPerson + "*" + to_string(*age) + "*" + *placeOfBirth + "*" + to_string(*choice) + "*" + *friendsName + "*" + to_string(RSHash(passwordChar,(*password).length())), fileName) == 0)
                makeAndPrintDetails(*nameOfPerson,*password,fileName);
            break;
        case 3:
            *dontStop = false; //breaks loop and exit
            break;
        default:
            cout << "INCORECT VALUE!!!\n";    
            break;
        }
        //assigniing all values to nothing to reset them
        //deleting would delete memory allocated
        *nameOfPerson = *password = *placeOfBirth = *friendsName = *tempHolder = "";
        *choice = *age = 0;
        passwordChar = NULL;
    }
    
    delete nameOfPerson, password,placeOfBirth,friendsName,tempHolder,choice,age,fileName,dontStop;
    delete [] passwordChar;
    return 0;
}

