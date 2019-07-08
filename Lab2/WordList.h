// Tyler Timms
// 9/5/2018
// cs3 Lab2
#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include <iostream>
#include <string>

// create a new temp word array of size + 1 each time a new word is found. copy
// all elements over, deallocate old array, update pointer to new array.
// Valgrind to check for memory leaks.


// WordOccurrence class ------------------------------------------------------
class WordOccurrence {
public:
    WordOccurrence(const std::string& word="", int num=0);
    bool matchWord(const std::string &); // returns true if word matches stored
    void increment(); // increments number of occurrences
    std::string getWord() const; 
    int getNum() const;

private:
    std::string word_;
    int num_;
};

// WordList class ------------------------------------------------------------
class WordList{
public:
    WordList();
    WordList(const WordList&);
    ~WordList();

    friend bool equal(const WordList&, const WordList&);

    WordList& operator=(const WordList&);
    void addWord(const std::string &);
    void print();
    void sortWordList();
private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
};
// WordOccurrence Definitions ------------------------------------------------
WordOccurrence::WordOccurrence(const std::string& word, int num){
    word_ = word;
    num_ = num;
}

bool WordOccurrence::matchWord(const std::string &word){
    if(word_ == word)
        return true;
    else 
        return false;
}

void WordOccurrence::increment(){
    ++num_;
}

std::string WordOccurrence::getWord() const{
    return word_;
}

int WordOccurrence::getNum() const{
    return num_;
}

// WordList Definitions ------------------------------------------------------
WordList::WordList(){
  size_ = 0;
  wordArray_ = new WordOccurrence[size_];
}

WordList::WordList(const WordList &wl){
  size_ = wl.size_;
  wordArray_ = new WordOccurrence[size_];
  for(int i = 0; i < size_; ++i){
    wordArray_[i] = wl.wordArray_[i];
  }
}

WordList::~WordList(){
  delete [] wordArray_;
}

WordList& WordList::operator=(const WordList &rhs){
    if(&rhs != this){
        delete [] wordArray_;
        size_ = rhs.size_;
        wordArray_ = new WordOccurrence[size_];
        for(int i = 0; i < size_; ++i){
            wordArray_[i] = rhs.wordArray_[i];
        }
    }
  return *this;
}

bool equal(const WordList& lhs, const WordList& rhs){
    if(lhs.size_ != rhs.size_)
        return false;
    for(int i = 0; i < lhs.size_; ++i){
        if(lhs.wordArray_[i].getWord() != rhs.wordArray_[i].getWord())
            return false;
    }
    return true;
}

void WordList::addWord(const std::string &word){ 
    
    //check if the word is in the list already
    for(int i = 0; i < size_; ++i){
        if(wordArray_[i].matchWord(word)){
            wordArray_[i].increment();
            return;
        }
    }
    //add the new word if not in list
    WordList temp(*this);
    ++size_;
    delete [] wordArray_;
    wordArray_ = new WordOccurrence[size_];
    for(int i = 0; i < size_ - 1; ++i){
        wordArray_[i] = temp.wordArray_[i];
    }
    wordArray_[size_ - 1] = WordOccurrence(word, 1);

}

void WordList::print(){
    for(int i = 0; i < size_; ++i){
        std::cout << wordArray_[i].getWord() << " " << wordArray_[i].getNum()
                  << std::endl;
    }
}

void WordList::sortWordList(){
    int left, right;
    for(int j = 0; j < size_; j++){
        left = 0;
        right = 1;
        for(int i = 0; i < size_ - 1; ++i){
            if(wordArray_[left].getNum() < wordArray_[right].getNum()){
                std::swap(wordArray_[left], wordArray_[right]);
            }
            ++left;
            ++right;
        }
    }
}

#endif // WORDCOUNT_H
