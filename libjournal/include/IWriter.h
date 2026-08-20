#pragma once

#include <string>

#include "ImportanceLevels.h"

class IWriter {
public:
    virtual void Write(const std::string& message, const ImportanceLevels& importanceLevel) = 0;

    virtual ~IWriter() = default;
};