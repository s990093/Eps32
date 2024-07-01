#ifndef PRINT_HELPER_H
#define PRINT_HELPER_H

#include <Arduino.h>

class PrintHelper
{
public:
    PrintHelper(bool debugMode = false);

    virtual void printHeader(const String &header);
    virtual void printKeyValue(const String &key, const String &value);
    virtual void printError(const String &errorMessage);
    virtual void printSuccess(const String &successMessage);
    virtual void printDebug(const String &debugMessage);

protected:
    bool debugMode; // to store the debug mode state
};
#endif // PRINT_HELPER_H
