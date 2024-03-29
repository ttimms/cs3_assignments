// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

// modified by Tyler Timms
// 9/19/2018

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student{
public:
   Student(string firstName, string lastName, string course): 
      firstName_(firstName), lastName_(lastName) {classes_.push_back(course);}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_)),
      classes_(move(org.classes_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
  string print() const;
  void addCourse(const string course){classes_.push_back(course);}
  string getCourse(){return classes_.back();}
  const string getLast() const{return lastName_;}

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < right.firstName_);
   }
private:
   string firstName_;
   string lastName_;
   list<string> classes_;
};

string Student::print() const{
  string temp = firstName_ + ' ' + lastName_ + ' ';
  for(const auto& e : classes_)
    temp += (e + ' ');
  return temp;
}


// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // vector of courses of students
   vector <list<Student>> courseStudents; 

   for(int i=1; i < argc-1; ++i){
      list<Student> roster;
      readRoster(roster, argv[i]);  
      cout << "\n\n" << argv[i] << "\n";  
      printRoster(roster);
      courseStudents.push_back(move(roster)); 
   }


   // reading in dropouts
   list<Student> dropouts; 
   readRoster(dropouts, argv[argc-1]); 
   cout << "\n\n dropouts \n"; printRoster(dropouts);

   list<Student> allStudents;  // master list of students
 
   for(auto& lst : courseStudents) 
     allStudents.splice(allStudents.end(),lst);

   cout << "\n\n all students unsorted \n"; 
           printRoster(allStudents);

   allStudents.sort(); // sorting master list
   cout << "\n\n all students sorted \n"; printRoster(allStudents);

   allStudents.unique(); // eliminating duplicates
   cout << "\n\n all students, duplicates removed \n"; printRoster(allStudents);
   
   for (const auto& str : dropouts)  // removing individual dropouts
      allStudents.remove(str);
   cout << "\n\n all students, dropouts removed \n"; printRoster(allStudents);

}


void readRoster(list<Student>& roster, string fileName){
   ifstream course(fileName);
   int i = 0;
   string currentCourse;
    while(fileName.at(i) != '.'){
        currentCourse += fileName.at(i);
        ++i;
    }

   string first, last;
   while(course >> first >> last)
      roster.push_back(Student(first, last, currentCourse));
   course.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
   for(const auto& student : roster)
      cout << student.print() << endl;
}