#include "PrintHelper.h"

PrintHelper::PrintHelper()
{
    // Constructor, can initialize if needed
}

void PrintHelper::printHeader(const String &header)
{
    Serial.println("===================================");
    Serial.println(header);
    Serial.println("===================================");
}

void PrintHelper::printKeyValue(const String &key, const String &value)
{
    Serial.print(key);
    Serial.print(": ");
    Serial.println(value);
}

void PrintHelper::printError(const String &errorMessage)
{
    Serial.print("[ERROR] ");
    Serial.println(errorMessage);
}

void PrintHelper::printSuccess(const String &successMessage)
{
    Serial.print("[SUCCESS] ");
    Serial.println(successMessage);
}

void PrintHelper::printDebug(const String &debugMessage)
{
    Serial.print("[DEBUG] ");
    Serial.println(debugMessage);
}
