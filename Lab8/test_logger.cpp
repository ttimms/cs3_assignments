// Logger Singleton
// Tyler Timms
// 10/31/2018

#include "logger.h"

int main(){
    Logger::log().report("test log message 1");
    Logger::log().report("test log message 2");
    Logger::log().report("test log message 3");
    Logger::log().report(""); // test empty message
    Logger::log().report("test log message 4");
}