// figures: class adapter pattern
// Mikhail Nesterenko
// 2/16/2014
//
// Modified by Tyler Timms
// 11/14/2018

#include <iostream>

using std::cout; using std::endl; using std::cin;

// base interface
class Figure {
public:
   virtual void draw()=0;
   virtual ~Figure(){}
};

// adaptee/implementer
class LegacyRectangle{
public:
   LegacyRectangle(int topLeftX, 
		   int topLeftY, 
		   int bottomRightX, 
		   int bottomRightY): 
      topLeftX_(topLeftX), 
      topLeftY_(topLeftY), 
      bottomRightX_(bottomRightX), 
      bottomRightY_(bottomRightY){}

   void oldDraw(){
      for(int i=0; i < bottomRightY_; ++i){
	 for(int j=0; j < bottomRightX_; ++j)
	    if(i >= topLeftY_  && j >= topLeftX_ )
	       cout << '*';
	    else
	       cout << ' ';
	 cout << endl;
      }
   }

   void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY){
       topLeftX_ = topLeftX;
       topLeftY_ = topLeftY;
       bottomRightX_ = bottomRightX;
       bottomRightY_ = bottomRightY;
   }

   int getTopLeftX(){return topLeftX_;}
   int getTopLeftY(){return topLeftY_;}
   int getBottomRightX(){return bottomRightX_;}
   int getBottomRightY(){return bottomRightY_;}

private: // defining top/left and bottom/right coordinates 
   int topLeftX_;
   int topLeftY_;
   int bottomRightX_;
   int bottomRightY_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter: public Figure, 
		     private LegacyRectangle {
public:
   SquareAdapter(int size): 
         LegacyRectangle(0,0,size,size){};

   void draw() override{
      oldDraw();
   }

   int size(){return getBottomRightY() - getTopLeftY();}

   void resize(int newSize){
       move(getTopLeftX(), getTopLeftY(), newSize, newSize);
    }
};


int main(){
   cout << "Enter a size for the square: ";
   int size;
   cin >> size;
   SquareAdapter *square = new SquareAdapter(size);
   square->draw();
   cout << endl << "Enter a new size: ";
   cin >> size;
   square->resize(size);
   square->draw();
}