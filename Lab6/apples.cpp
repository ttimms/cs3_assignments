// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 2/16/2018
//
// Modified by Tyler Timms
// 10/4/2018

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};

//used with generate to get random Apples object
Apples randomApple(){
   const double minWeight = 8.;
   const double maxWeight = 3.;
   Apples a;
   a.weight = minWeight + 
              static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
   a.color = rand() % 2 == 1 ? "green" : "red";
   return a;
}

// used for accumulate()
double addWeight(double sum, Apples a){
    sum = sum + a.weight;
    return sum;
}

void printContainer(Apples ap){
    cout << ap.color << " " << ap.weight << endl;
}

// used as functor for remove_if)()
class isLighterThan{
public:
    isLighterThan(double min) : min_(min){}
    bool operator() (Apples ap) {return ap.weight < min_;}
private:
    double min_;
};

int main(){
   srand(time(nullptr));

   cout << "Input crate size: ";
   int size;
   cin >> size;

   vector <Apples> crate(size);

   // assign random weight and color to apples in the crate
    std::generate(crate.begin(), crate.end(), randomApple);
 
   cout << "Enter weight to find: ";
   double toFind;
   cin >> toFind;
   
   // count apples heavier than toFind
   int cnt = std::count_if(crate.cbegin(), crate.cend(), 
                           [&](Apples a){return a.weight > toFind;});

   cout << "There are " << cnt << " apples heavier than " 
	<< toFind << " oz" <<  endl;

   // find positions where apples are heavier than toFind
   auto it = std::find_if(crate.cbegin(), crate.cend(),
                          [&](Apples ap){return ap.weight > toFind;});
   if(it != crate.end()){
      cout << "at positions ";
      int pos = 0;
      while(it != crate.cend()){
         cout << it - crate.cbegin() << ", ";
         it = std::find_if(it+1, crate.cend(), 
                          [&](Apples ap){return ap.weight > toFind;});
    }
    cout << endl;
   }

    // returns iterator to heaviest apple in crate
   auto heaviest = std::max_element(crate.begin(), crate.end(),
                   [](Apples lhs, Apples rhs){return lhs.weight < rhs.weight;});


   cout << "Heaviest apple weighs: " << (*heaviest).weight << " oz" << endl;

   // adds the cummulative weight of all the apples
   auto fp = addWeight;
   double sum = 0;
   std::accumulate(crate.cbegin(), crate.cend(), sum, fp);

   cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;

   std::transform(crate.begin(), crate.end(), crate.begin(), 
                  [&](Apples ap){ap.weight += toGrow; return ap;});

   
   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;
   
   // removes apples lighter than minAccept via remove_if and functor
   auto lighter = isLighterThan(minAccept);
   crate.erase(std::remove_if(crate.begin(), crate.end(), lighter),
                crate.end());

   cout << "removed " << size - crate.size() << " elements" << endl;

   // sort apples by weight
   std::sort(crate.begin(), crate.end(), 
             [](Apples lhs, Apples rhs){return lhs.weight < rhs.weight;});


   // copy all red apples from crate to peck
   deque<Apples> peck;
   std::remove_copy_if(crate.begin(), crate.end(), 
                       std::back_inserter(peck), 
                       [](Apples ap) {return ap.color == "red";});

   // erase all green apples from crate
   crate.erase(
       std::remove_if(crate.begin(), crate.end(), 
                      [](Apples ap) {return ap.color == "green";})
       ,crate.end()
       );

   cout << "apples in the crate"<< endl;
   std::for_each(crate.cbegin(), crate.cend(), printContainer);

   cout << endl;

   cout << "apples in the peck"<< endl;
   std::for_each(peck.cbegin(), peck.cend(), printContainer);
}
