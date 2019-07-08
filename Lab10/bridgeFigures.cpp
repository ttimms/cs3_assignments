// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko
// 2/12/2014
//
// Modified by Tyler Timms
// 11/14/2018

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill{
public:
   Fill(char fillChar, char borderChar):fillChar_(fillChar),
        borderChar_(borderChar){}
   virtual char getBorder()=0;
   virtual char getInternal()=0;
   virtual ~Fill() {}
protected:
   char fillChar_;
   char borderChar_;
};

// concrete body
class Hollow: public Fill{
public:
   Hollow(char fillChar):Fill(fillChar, fillChar){borderChar_ = ' ';}
   char getBorder() override {return fillChar_;}
   char getInternal() override {return borderChar_;}
   ~Hollow(){}
};

// another concrete body
class Filled: public Fill {
public:
   Filled(char fillChar):Fill(fillChar, fillChar){}
   char getBorder() override {return fillChar_;}
   char getInternal() override {return fillChar_;}
   ~Filled(){}
};

class EnhancedFilled: public Fill {
public:
   EnhancedFilled(char fillChar, char borderChar):
                  Fill(fillChar, borderChar){}
   char getBorder() override {return borderChar_;}
   char getInternal() override {return fillChar_;}
   ~EnhancedFilled(){}
};

// abstract handle
class Figure {
public:
   Figure(int size, Fill* fill): size_(size), 
				 fill_(fill){}
   virtual void draw() =0;
   void changeFill(const Fill *newFill){fill_ = const_cast<Fill*>(newFill);}
   virtual ~Figure(){}
protected:
   int size_;
   Fill *fill_;
};

// concrete handle
class Square: public Figure{
public:
   Square(int size, Fill* fill): Figure(size, fill){}
   void draw() override;

};


void Square::draw(){
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
	 if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	    cout << fill_ -> getBorder();
	 else
	    cout << fill_ -> getInternal();
      cout << endl;
   }
}


int main(){

   // ask user for figure parameters
   cout << "Enter fill character: "; 
            char fchar; cin >> fchar;
   cout << "Filled or hollow? [f/h] "; 
           char ifFilled; cin >> ifFilled;
   cout << "Enter size: "; int size; cin >> size;
  
   // assign userbox to new square either filled or hollow
   Figure *userBox = new Square(size, ifFilled == 'f'? 
	       static_cast<Fill *>(new Filled(fchar)):
	       static_cast<Fill *>(new Hollow(fchar))
     				                     ); 
  

   userBox -> draw();
   cout << endl;

   // Get new fill character
   cout << "Enter new fill character: ";
   cin >> fchar;
   
   // changes print character for either hollow or filled square
   userBox -> changeFill((ifFilled == 'f'? 
                        static_cast<Fill *>(new Filled(fchar)):
	                static_cast<Fill *>(new Hollow(fchar))));
   userBox -> draw();
   cout << endl;

   cout << "Enter new borderChar for EnhancedFilled: ";
   char bchar;
   cin >> bchar;
   
   // Demonstrates the three classes. Hollow, Filled, and EnhancedFilled
   Figure *filled = new Square(size, static_cast<Fill *>(new Filled(fchar)));
   Figure *enhanced = new Square(size, static_cast<Fill *>
                        (new EnhancedFilled(fchar, bchar)));
   Figure *hollow = new Square(size, static_cast<Fill *>(new Hollow(fchar)));

   // Draw the three figures.
   cout << "Filled Square:\n";
   filled -> draw();
   cout << endl;
   cout << "enhanced square:\n";
   enhanced -> draw();
   cout << endl;
   cout << "hollow square:\n";
   hollow -> draw();
   cout << endl;
}