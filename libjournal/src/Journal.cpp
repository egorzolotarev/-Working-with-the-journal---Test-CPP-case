#include "Journal.h"
#include <iostream>

void Journal::SetWriter(std::unique_ptr<IWriter> writer)
{
    _writer = std::move(writer);
}

void Journal::SetImportanceLevel(const ImportanceLevels& importanceLevel)
{
    _importanceLevel = importanceLevel;
}

void Journal::Write(const std::string& message, const ImportanceLevels& importanceLevel)
{
    // Валидация аргументов
    if (_writer == nullptr)
    {
        throw std::runtime_error("Не задано место записи");
    }

    if (importanceLevel < _importanceLevel)
    {
        return;
    }

    _writer->Write(message, ToStr(importanceLevel));
}

void Journal::Write(const std::string& message)
{
    Write(message, _importanceLevel);
}