#pragma once

#include "IWriter.h"
#include "ImportanceLevels.h"

class FileWriter: public IWriter {
public:
    FileWriter(const std::string& filePath)
    {
        SetFilePath(filePath);
    }

    void SetFilePath(const std::string& filePath);

    void Write(const std::string& message, const ImportanceLevels& importanceLevel) override;

private:
    std::string _filePath;
};