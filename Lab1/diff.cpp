// Tyler Timms
// CS3 Lab 1
// 08/29/2018

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    // open the two files.
    std::ifstream file1(argv[1]);
    std::ifstream file2(argv[2]);
    
    if(file1.is_open() && file2.is_open()) {
        std::string file1Line, file2Line;
        int lineNumber = 0;
        
        // get each line one by one to compare.
        while(!file1.eof() || !file2.eof()){
            ++lineNumber;
            std::getline(file1, file1Line);
            std::getline(file2, file2Line);
            
            if(file1Line != file2Line){
                // calculate number of spaces before carat placement.
                int numSpaces = 0;
                char c1 = ' ', c2 = ' ';
                while(c1 == c2){
                    c1 = file1Line[numSpaces];
                    c2 = file2Line[numSpaces];
                    ++numSpaces;
                }
                if(lineNumber >=10) ++numSpaces;
                if(lineNumber >=100) ++numSpaces;
                numSpaces += 13;
                std::string spaceString(numSpaces, ' ');
                
                // output differing lines and carat marker.
                std::cout << "file1.txt: " << lineNumber << ": " << file1Line
                          << std::endl << "file2.txt: " << lineNumber << ": "
                          << file2Line << std::endl << spaceString << "^\n\n";
            }
        }
        file1.close();
        file2.close();
    }
    else {
        std::cout << "Unable to open one or more of the files.\n";
    }
}
