#pragma once

#include <string>

class IWriter {
public:
    virtual void Write(const std::string& message, const std::string& importanceLevel) = 0;

    virtual ~IWriter() = default;
};