#pragma once
#include <string>
#include <stdexcept>

enum class ImportanceLevels 
{
    SMALL,
    MIDDLE,
    HIGH,
};

inline std::string ToStr(ImportanceLevels importanceLevel)
{
    switch (importanceLevel) 
    {
        case ImportanceLevels::SMALL:  return "SMALL";
        case ImportanceLevels::MIDDLE: return "MIDDLE";
        case ImportanceLevels::HIGH:   return "HIGH";
        default:                       throw std::runtime_error("Неизвестный уровень важности:");
    }
}

inline ImportanceLevels ToImportanceLevel(std::string str)
{
    if (str == "SMALL") {
        return ImportanceLevels::SMALL;
    } 
    else if (str == "MIDDLE") {
        return ImportanceLevels::MIDDLE;
    } 
    else if (str == "HIGH") {
        return ImportanceLevels::HIGH;
    } 
    else {
        throw std::runtime_error("Неизвестный уровень важности: '" + str + "'");
    }
}