#pragma once

#include "IWriter.h"

class FileWriter: public IWriter {
public:
    FileWriter(const std::string& filePath)
    {
        SetFilePath(filePath);
    }

    void SetFilePath(const std::string& filePath);

    void Write(const std::string& message, const std::string& importanceLevel) override;

private:
    std::string _filePath;
};