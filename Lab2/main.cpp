// Tyler Timms
// 9/5/2018
// cs3 Lab2

#include <iostream>
#include <string>
#include <fstream>
#include "WordList.h"

int main(int argc, char* argv[]){

    std::ifstream file(argv[1]);
    std::string word;
    WordList wl;
    while(file >> word){

        for(int i = 0; i < word.size(); ++i){
            // check whether character is punctuation or not
            if (ispunct(word[i]))
                word.erase(i--, 1);
        }

        wl.addWord(word);
    }
    wl.sortWordList();
    wl.print();
}
