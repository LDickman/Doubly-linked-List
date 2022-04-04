//  Person.cpp
//
//  Function implementations for Person class, CS 223, Lab 1
//
//  Student: Lauren Dickman
//  Date: Tuesday, January 29, 2020
//
//    Person Class Instance Variables
//    string first;      // the person's first name
//    string last;       // the person's last name
//    int age;           // the person's age

#include <iostream>
#include <string>
#include "Person.h"

using namespace std;

// CONSTRUCTORS for the Person class:
//  	Person(std::string fname = "J", std::string lname = "Doe", int currAge = 0);
//  	Precondition: May be called with 0 arguments, 1 argument (fname),
//                    2 arguments (fname, lname), or all 3 arguments.
//  	Precondition: fname has size 1 or more
//  	Precondition: lname has size 1 or more
//  	Precondition: currAge >= 0
//  	Postcondition: An instance of class Person has been initialized with
//                     the provided (or default) values: fname, lname, currAge
   Person::Person(string fname, string lname, int A)
   {
   first = fname; // the person's first name
   last = lname;  // the person's last name
   age =A;        // the person's age
   }

// ACCESSOR MEMBER FUNCTIONS
//   std::string getFirstName() const;
//      Precondition: None
//      Postcondition: person's first name is returned
   string Person::getFirstName() const
   {
   	return first;
   }
//
//   std::string getLastName() const;
//      Precondition: None
//      Postcondition: person's last name is returned
   string Person::getLastName() const
   {
   	return last;
   }
//
//   int getAge() const;
//      Precondition: None
//      Postcondition: person's age is returned
   int Person::getAge() const
   {
   	return age;
   }
//
//   std::string getFullName() const;
//      Precondition: None
//      Postcondition: person's full name (first and last) is returned
   string Person::getFullName() const
   {
   	return (first +" "+ last);
   }

// MODIFICATION MEMBER FUNCTIONS for the Person class:
//   void setFirstName(std::string newName);
//      Precondition: newName has size 1 or more
//      Postcondition: person's first name is now newName
   void Person::setFirstName(string newName) // newName has size 1 or more
   {
   	first = newName; // the person's first name
   }
//
//   void setLastName(std::string newName);
//      Precondition: newName has size 1 or more
//      Postcondition: person's last name is now newName
   void Person::setLastName(string newName)  // newName has size 1 or more
   {
   	last = newName;  // the person's last name
   }
//
//   void setAge(int newAge);
//      Precondition: newAge >= 0
//      Postcondition: person's age is now newAge
   void Person::setAge(int newAge)           // newAge >= 0
   {
   	age = newAge;        // the person's age
   }
//
//   void agePerson();
//      Precondition: None
//      Postcondition: person's age is now one year older
   void Person::agePerson() // makes the Person one year older
   {
   	age = age + 1;
   }

// OPERATOR OVERLOADING:
//
//   bool operator==(const Person& personA, const Person& personB);
//       equality operator (==); personA and personB are "equal" iff they have:
//          - the same first name,
//          - the same last name, and
//          - the same age
	bool operator==(const Person& personA, const Person& personB)
	{
		return (personA.getFirstName() == personB.getFirstName() && personA.getLastName() == personB.getLastName() && personA.getAge() == personB.getAge());
	}

//   bool operator!=(const Person& personA, const Person& personB);
//        inequality operator (!=); logical negation of the equality operator
	bool operator!=(const Person& personA, const Person& personB)
	{
		return !(personA.getFirstName() == personB.getFirstName() && personA.getLastName() == personB.getLastName() && personA.getAge() == personB.getAge());
	}
//   bool operator<(const Person& personA, const Person& personB);
//        strictly-less-than operator (<); personA and personB are compared as
//        follows:
//          1. By last name: "Karie Abc, age 5" < "Joe Xyz, age 2" since
//             "Abc" < "Xyz".
//          2. If last names are the same, then by first name:
//             "Jane Abc, age 5" < "Karie Abc, age 2" since "Abc" == "Abc" and
//             "Jane" < "Karie".
//          3. If full names are the same, then by age:
//             "Jane Xyz, age 2" < "Jane Xyz, age 5".
	bool operator<(const Person& personA, const Person& personB)
	{
		if (personA.getFirstName() == personB.getFirstName() && personA.getLastName() == personB.getLastName())
      {
          if (personA.getAge() == personB.getAge())
              return false;
          else if (personA.getAge() < personB.getAge()) 
              return true;
          else 
              return false;
      }
        else if (personA.getLastName() == personB.getLastName())
    	{
        	if (personA.getFirstName() < personB.getFirstName()) 
            	return true;
        	else 
              return false;
    	}
    	else
    	{
        	if (personA.getLastName() < personB.getLastName()) 
            	return true;
        	else 
              return false;
    	}
	}

//   Person operator+(const Person& personA, const Person& personB);
//        addition operator (+); as in real life, when you add two people
//        together you get a newborn person:
//          - new Person first name is "Baby"
//          - new Person last name is the hyphenation of the parents' last names:
//            "Ella Mercier" + "Juan Sanchez" -> "Baby Mercier-Sanchez, age 0"
	Person operator+(const Person& personA, const Person& personB)
	{
		string newName = personA.getLastName() +"-"+ personB.getLastName();
		int age = 0;
		Person baby("Baby", newName, age);
		return baby;
	}

//   std::ostream& operator<<(std::ostream& out, const Person& person);
//        stream output operator (<<); for example, a Person named "John Doe"
//        with age 8 would produce the following output:
//            Person: John Doe, age 8
//
//        note: The above sample output begins with 'P' and ends with '8'.
//        `<<` DOES NOT put whitespace or newline after the age.
//
//        note: `<<` returns the `out` parameter to allow chaining of stream output
	ostream& operator<<(ostream& out, const Person& person)
	{
    	out << "Person: " << person.getFullName() << ", age " << person.getAge();
    	return out;
	}

// 		  std::istream& operator>>(std::istream& in, Person& person);
//        stream input operator; for example: if the input stream `in` holds
//        the message, "Person: Jean Mercier, age 8", then `in >> p1` will
//        change p1's data to become:
//             - first name: "Jean"
//             - last name: "Mercier"
//             - age: 8
	istream& operator>>(istream& in, Person& person)
	{
    	in.ignore(8);
    	in >> person.first;
    	in.ignore(1);
    	getline(in,person.last,',');
    	in.ignore(4);
    	in >> person.age;
    	return in;
	}
