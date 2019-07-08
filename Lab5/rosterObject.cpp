// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

// Modified by Tyler Timms
// 10/1/2018
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>
#include <utility>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move; using std::map;
using std::make_pair;


class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
  string print() const {return firstName_ + ' ' + lastName_;}

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < left.firstName_);
   }
private:
   string firstName_;
   string lastName_;
};




// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   map<Student, list<string>> allStudents;  // master list of students
   for(int i=1; i < argc; ++i){

      string currentCourse;
      string fileName = argv[i];
      int j = 0;
      while(fileName.at(j) != '.'){
         currentCourse += fileName.at(j);
         ++j;
      }
      list<string> classes;

      classes.push_back(currentCourse);
      list<Student> roster;
      readRoster(roster, argv[i]);
      for(auto e : roster){
          auto ret = allStudents.insert(make_pair(e, classes));
          if(!ret.second){
              ret.first->second.push_back(currentCourse);
          }
      }
      //courseStudents.push_back(move(roster)); 
   }

   for(auto e : allStudents){
       cout << e.first.print() + " :";
       for(auto str : e.second){
           cout << " " + str + ' ';
       }
       cout << endl;
   }
}


void readRoster(list<Student>& roster, string fileName){
   ifstream course(fileName);
    
   string first, last;
   while(course >> first >> last)
      roster.push_back(Student(first, last));
   course.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
   for(const auto& student : roster)
      cout << student.print() << endl;
}
