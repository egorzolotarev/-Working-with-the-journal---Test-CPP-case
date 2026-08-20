#pragma once

#include <memory>
#include <string>

#include "ImportanceLevels.h"
#include "IWriter.h"

class Journal {
public:

    explicit Journal(ImportanceLevels importanceLevel = ImportanceLevels::MIDDLE)
    {
        SetImportanceLevel(importanceLevel);
    }

    void SetWriter(std::unique_ptr<IWriter> writer);

    void SetImportanceLevel(const ImportanceLevels& importanceLevel);

    void Write(const std::string& message, const ImportanceLevels& importanceLevel);

    void Write(const std::string& message);
private:
    std::unique_ptr<IWriter> _writer;
    ImportanceLevels _importanceLevel = ImportanceLevels::MIDDLE;
};