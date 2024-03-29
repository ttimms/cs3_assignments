// testing the implementation of templated list collection
// Mikhail Nesterenko
// 9/10/2015

#include <iostream>
#include <string>
#include "Collection.h" // template definition

using std::cout; using std::endl;
using std::string;

int main(){

   // manipulating integers
   Collection<int> cone;
   cout << "Integer collection: ";
   cone.addItem(1); cone.addItem(2); cone.addItem(3);
   cone.printCollection();

   cone.removeItem(2);
   cone.printCollection();

   if(equal(cone, cone))
      cout << "cone is equal to itself" << endl;


   // uncomment when you debug the code above
    

   // manipulating strings
   string sa[] = {"yellow", "orange", "green", "blue"};
   Collection<string> ctwo;

   for(auto s : sa)
      ctwo.addItem(s);

   cout << "String collection: ";
   ctwo.printCollection();


   // manipulating character collections

   // individal collections
   Collection<char> a2g, h2n, o2u;
   for(char c='a'; c <='g'; ++c) a2g.addItem(c);
   for(char c='h'; c <='n'; ++c) h2n.addItem(c);
   for(char c='o'; c <='u'; ++c) o2u.addItem(c);

   if(!equal(a2g, h2n))
      cout << "a2g is not equal to h2n" << endl;

   // collection of collections
   Collection<Collection<char>> cpile;

   // adding individual collections
   cpile.addItem(a2g);
   cpile.addItem(h2n);
   cpile.addItem(o2u);

   // printing characters from last collection added
   cout << "Last added character collection: ";
   cpile.lastItem().printCollection(); 

   
}