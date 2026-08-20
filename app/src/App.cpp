#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <regex>
#include <memory>

#include "JournalLib.h"

// Потокобезопасная передача реализована с помощтю очереди
std::queue<std::pair<std::string, ImportanceLevels>> dataQueue;
std::mutex mutex;
std::condition_variable conditionVar;
std::atomic<bool> running{true};

// Функция  потока, который работает с Journal
void JournalWrite(Journal& journal)
{
    while (running)
    {
        // Запирается поток и ождается пока поступят данные
        std::unique_lock<std::mutex> lock(mutex);

        conditionVar.wait(lock, [] {
            return !dataQueue.empty() || !running;
        });

        if (!running && dataQueue.empty()) {
            break;
        }

        auto data = dataQueue.front();
        std::string message = data.first;
        ImportanceLevels importanceLevel = data.second;
        dataQueue.pop();

        lock.unlock();

        if (message == "--SET")
        {
            journal.SetImportanceLevel(importanceLevel);
        }
        else
        {
            journal.Write(message, importanceLevel);
        }
    }
}

int main(int argc, char* argv[])
{
    ImportanceLevels defaultImportanceLevel = ToImportanceLevel(std::string(argv[2]));
    
    Journal journal(defaultImportanceLevel);
    FileWriter writer{std::string(argv[1])};
    journal.SetWriter(std::make_unique<FileWriter>(writer));

    std::thread thread([&journal] () {JournalWrite(journal);});

    // Регулярки для парсинга аргументов
    std::regex regexImportanceLevel("^(.*?)(?:\\s*--(.*))?$");
    std::regex regexSetLevel("^SET .*");

    while (true)
    {
        std::cout << "Введите сообщение и по необходимости уровень важности(--SMALL/--MIDDLE/--HIGH) или exit для выхода или --SET (SMALL/MIDDLE/HIGH)\n";

        std::string line;
        std::getline(std::cin, line);
        if (line == "exit")
        {
            break;
        }

        std::smatch match;
        std::regex_search(line, match, regexImportanceLevel);
        
        std::string message = match[1];
        std::string importanceLevelStr = match[2];

        ImportanceLevels importanceLevel;
        if (std::regex_match(importanceLevelStr, regexSetLevel))
        {
            message = "--SET";
            importanceLevelStr.erase(0, 4);
            importanceLevel = ToImportanceLevel(importanceLevelStr);
        }
        else
        {
            importanceLevel = importanceLevelStr == "" ? defaultImportanceLevel : ToImportanceLevel(importanceLevelStr);
        }

        {
            std::lock_guard<std::mutex> lock(mutex);
            dataQueue.push(std::make_pair(message, importanceLevel));
        }
        conditionVar.notify_one();
    }

    running = false;
    conditionVar.notify_one();
    thread.join();
}