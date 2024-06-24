#ifndef PRINT_HELPER_H
#define PRINT_HELPER_H

#include <Arduino.h>

class PrintHelper
{
public:
    PrintHelper();

    void printHeader(const String &header);
    void printKeyValue(const String &key, const String &value);
    void printError(const String &errorMessage);
    void printSuccess(const String &successMessage);
    void printDebug(const String &debugMessage);
};

#endif // PRINT_HELPER_H
