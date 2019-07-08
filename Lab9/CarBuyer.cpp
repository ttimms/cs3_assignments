// needed for lab
// Mikhail Nesterenko
// 3/14/2016
//
// Modified by Tyler Timms
// 11/14/2018

#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <string>
#include "CarFactory.h"

using std::vector;
using std::string;
using std::cout; using std::endl;

class CarLot{
public:
   CarLot();
   Car *testDriveCar(int i){return car4sale_[i];}

   // if a car is bought, requests a new one
   Car *buyCar(int i){ 
      Car *bought = car4sale_[i];
      car4sale_[i] = 
        factories_[rand()%factories_.size()]->requestCar();
      return bought;
   }

   int lotSize(){return car4sale_.size();}

   Car* nextCar(){
     static int index = 0;
     Car* testDrivenCar;
     testDrivenCar = testDriveCar(index);
     index = (++index) % lotSize();
     return testDrivenCar;
   }
		     
private:
   vector<Car *> car4sale_; // single car for sale at the lot
   vector<CarFactory *> factories_;
};


CarLot::CarLot(){
   // creates 2 Ford factories and 2 Toyota factories 
   factories_.push_back(new FordFactory());   
   factories_.push_back(new ToyotaFactory());
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());

   // gets the first car for sale

   car4sale_.push_back(factories_[rand() % factories_.size()] -> requestCar());
   car4sale_.push_back(factories_[rand() % factories_.size()] -> requestCar());
   car4sale_.push_back(factories_[rand() % factories_.size()] -> requestCar());
}



CarLot *carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(){
   static const std::array<std::string, 5>
      models = {"Corolla", "Camry",
                "Prius", "4Runner", "Yaris"};

   string requestedModel = models[rand() % models.size()];
   cout << "Customer requesting Toyota " << requestedModel << endl;

   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   for(int i=0; i<carLotPtr->lotSize(); ++i){
      Car *toBuy = carLotPtr -> nextCar(); 

      cout << "test driving " 
      << toBuy->getMake() << " "
      << toBuy->getModel();

      if (toBuy->getMake() == "Toyota" && toBuy->getModel() == requestedModel){
          cout << " love it! buying it!" << endl;
          carLotPtr -> buyCar(i);
          break;
      } else
          cout << " did not like it!" << endl;
   }
   cout << endl;
}

// test-drives a car
// buys it if Ford
void fordLover(){
   static const std::array<std::string, 4>
      models = {"Focus", "Mustang", 
		            "Explorer", "F-150"};

   string requestedModel = models[rand() % models.size()];

   cout << "Customer requesting Ford " << requestedModel << endl;
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   for(int i=0; i<carLotPtr->lotSize(); ++i){
      Car *toBuy = carLotPtr -> nextCar();
      cout << "test driving "
      << toBuy->getMake() << " "
            << toBuy->getModel();
      
      if (toBuy->getMake() == "Ford" && toBuy->getModel() == requestedModel){
          cout << " love it! buying it!" << endl;
          carLotPtr -> buyCar(i);
          break;
      } else
          cout << " did not like it!" << endl;
   }
   cout << endl;
}



int main() {
   srand(time(nullptr));

   toyotaLover();
   fordLover();
   toyotaLover();
  
}