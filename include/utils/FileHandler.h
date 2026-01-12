#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>

class FileHandler {
public:
    static std::vector<std::string> readAllLines(const std::string& filename);
    static bool writeLine(const std::string& filename, const std::string& line);
    static bool writeAllLines(const std::string& filename, const std::vector<std::string>& lines);
    static bool updateLine(const std::string& filename, const std::string& id, const std::string& newLine);
    static bool deleteLine(const std::string& filename, const std::string& id);
    static bool fileExists(const std::string& filename);
    static void createFileIfNotExists(const std::string& filename);
};

#endif // FILE_HANDLER_H
