#include <fstream>
#include <filesystem>
#include <stdexcept>

#include "FileWriter.h"


void FileWriter::Write(const std::string& message, const std::string& importanceLevel)
{
    // Валидация аргументов
    if (_filePath.empty())
    {
        throw std::runtime_error("Путь к файлу для записи не указан");
    }
    std::ofstream file(_filePath, std::ios::app);
        
    if (!file.is_open())
    {
        throw std::runtime_error("Не удалось открыть файл для записи");
    }

    // Запись
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    file << importanceLevel << " : " << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S") << " : " << message << "\n";

    file.close();
}

void FileWriter::SetFilePath(const std::string& filePath)
{
    // Валидация аргументов
    std::filesystem::path path(filePath);
        
    if (!std::filesystem::exists(path))
    {
        throw std::runtime_error("Такой путь не существует");
    }

    _filePath = filePath;
}