// Logger Singleton
// Tyler Timms
// 10/31/2018

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

using std::string;
using std::ofstream;
using std::endl;

class Logger{
public:
    static Logger& log(){
        static Logger log;
        return log;
    }

    ~Logger();

    void report(const string&);

    // Deleted functions
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger();

    ofstream logFile;
};

Logger::Logger(){
    logFile.open("log.txt");
}

Logger::~Logger(){
    logFile.close();
}

void Logger::report(const string& message){
    logFile << message << endl;
}

#endif