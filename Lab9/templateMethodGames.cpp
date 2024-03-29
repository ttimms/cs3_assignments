// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014
// Dice Game added by Tyler Timms
// 11/07/2018

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

using std::cout; using std::endl; using std::string; using std::cin;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
   Game():playersCount_(0), movesCount_(0), 
	  playerWon_(noWinner){}

   // template method
   void playGame(const int playersCount = 0) {
      playersCount_ = playersCount;
      movesCount_=0;

      initializeGame();

      for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
	    makeMove(i);
	  if (i==playersCount_-1) 
	    ++movesCount_; 
      }

      printWinner();
   }

   virtual ~Game(){}

protected:
   // primitive operations
   virtual void initializeGame() = 0;
   virtual void makeMove(int player) = 0;
   virtual void printWinner() = 0;
   virtual bool endOfGame() {
      return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
   static const int noWinner=-1;

   int playersCount_;
   int movesCount_;
   int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
   // implementing concrete methods
   void initializeGame(){
      playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
   }

   void makeMove(int player) {
      if (movesCount_ > minMoves_){ 
	 const int chance = 
	   minMoves_ + rand() % (maxMoves_ - minMoves_);
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Monopoly, player "<< playerWon_<< " won in "
	   << movesCount_<< " moves." << endl;
   }

private:
   static const int numPlayers_ = 8; // max number of players
   static const int minMoves_ = 20; // nobody wins before minMoves_
   static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
//  primitive operations
class Chess: public Game {
public:
   void initializeGame(){
      playersCount_ = numPlayers_; // initalize players
      for(int i=0; i < numPlayers_; ++i) 
	     experience_[i] = rand() % maxExperience_ + 1 ; 
   }

   void makeMove(int player){
      if (movesCount_ > minMoves_){
	 const int chance = (rand() % maxMoves_) / experience_[player];
	 if (chance < movesCount_) playerWon_= player;
      }
   }

   void printWinner(){
      cout << "Chess, player " << playerWon_ 
	   << " with experience " << experience_[playerWon_]
	   << " won in "<< movesCount_ << " moves over"
	   << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
           << endl;
   }

private:
   static const int numPlayers_ = 2;
   static const int minMoves_ = 2; // nobody wins before minMoves_
   static const int maxMoves_ = 100; // somebody wins before maxMoves_
   static const int maxExperience_ = 3; // player's experience
                              // the higher, the greater probability of winning
   int experience_[numPlayers_]; 
};

// Dice Game ------------------------------------------------------------------

class Dice : public Game {
public:
    void initializeGame(){
        playersCount_ = numPlayers_;
    }

    void makeMove(int player){
        if(movesCount_ < maxMoves_ && !endOfGame()){
            string currentPlayer = player > 0 ? "You" : "Computer";
            cout << currentPlayer + " rolled: ";

            if(currentPlayer == "Computer"){                
                bool skip = false;
                if(movesCount_ > 0){
                    skip = (rand()%2) > 0 ? true : false;
                }
                if(!skip){
                    int currentScore = 0;
                    for(int i = 0; i < numDice_; ++i){
                        int thisRoll = (rand()%6) + 1;
                        cout << thisRoll << " ";
                        currentScore += thisRoll;
                    }
                    if(currentScore > compHighScore_)
                        compHighScore_ = currentScore;
                    cout << "= " << currentScore << " ";
                }
                if(skip){
                    cout << "passed, ";
                    if(skip && passed_){
                        playerWon_ = compHighScore_ >= playerHighScore_ ? 0 : 1;
                    }
                }
                cout << "computer's highest score = " << compHighScore_ << endl;
            }

            if(currentPlayer == "You"){
                if(!passed_){
                    int currentScore = 0;
                    for(int i = 0; i < numDice_; ++i){
                        int thisRoll = (rand()%6) + 1;
                        cout << thisRoll << " ";
                        currentScore += thisRoll;
                    }
                    if(currentScore > playerHighScore_)
                        playerHighScore_ = currentScore;
                    cout << "= " << currentScore << " ";
                }
                if(passed_){
                    cout << "passed, ";
                }
                cout << "player's highest score = " << playerHighScore_ << endl;
                if(movesCount_ < maxMoves_ - 1){
                    cout << "Roll again? [y/n] ";
                    char rollAgain;
                    cin >> rollAgain;
                    if(rollAgain == 'y'){
                        passed_ = false;
                    }
                    if(rollAgain == 'n'){
                        passed_ = true;
                    }
                }
            }           
        }
        else{
            playerWon_ = compHighScore_ >= playerHighScore_ ? 0 : 1;
        }
    }

    void printWinner(){
        if(playerWon_ == 0){
            cout << "you lose" << endl;
        }
        else{
            cout << "you win" << endl;
        }
    }

private:
    static const int numPlayers_ = 2;
    static const int maxMoves_ = 3;
    static const int numDice_ = 5;
    int compHighScore_ = 0;
    int playerHighScore_ = 0;
    bool passed_ = false;
};

//-----------------------------------------------------------------------------
int main() {
   srand(time(nullptr));

   Game* gp = nullptr;
    /*
   // play chess 10 times
   for (int i = 0; i < 10; ++i){ 
      gp = new Chess;
      gp->playGame(); 
      delete gp;
   }
      

   // play monopoly 5 times
   for (int i = 0; i < 5; ++i){
      gp = new Monopoly;
      gp->playGame(); 
      delete gp;
   }
   */
    // play Dice
    gp = new Dice;
    gp->playGame();
    delete gp; 
}