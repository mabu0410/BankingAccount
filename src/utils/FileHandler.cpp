#include "utils/FileHandler.h"
#include <fstream>
#include <sys/stat.h>

std::vector<std::string> FileHandler::readAllLines(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                lines.push_back(line);
            }
        }
        file.close();
    }
    
    return lines;
}

bool FileHandler::writeLine(const std::string& filename, const std::string& line) {
    std::ofstream file(filename, std::ios::app);
    
    if (file.is_open()) {
        file << line << std::endl;
        file.close();
        return true;
    }
    
    return false;
}

bool FileHandler::writeAllLines(const std::string& filename, const std::vector<std::string>& lines) {
    std::ofstream file(filename, std::ios::trunc);
    
    if (file.is_open()) {
        for (const auto& line : lines) {
            file << line << std::endl;
        }
        file.close();
        return true;
    }
    
    return false;
}

bool FileHandler::updateLine(const std::string& filename, const std::string& id, 
                              const std::string& newLine) {
    std::vector<std::string> lines = readAllLines(filename);
    bool found = false;
    
    for (auto& line : lines) {
        // Check if line starts with the given ID
        if (line.find(id) == 0) {
            line = newLine;
            found = true;
            break;
        }
    }
    
    if (found) {
        return writeAllLines(filename, lines);
    }
    
    return false;
}

bool FileHandler::deleteLine(const std::string& filename, const std::string& id) {
    std::vector<std::string> lines = readAllLines(filename);
    std::vector<std::string> newLines;
    bool found = false;
    
    for (const auto& line : lines) {
        if (line.find(id) != 0) {
            newLines.push_back(line);
        } else {
            found = true;
        }
    }
    
    if (found) {
        return writeAllLines(filename, newLines);
    }
    
    return false;
}

bool FileHandler::fileExists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void FileHandler::createFileIfNotExists(const std::string& filename) {
    if (!fileExists(filename)) {
        std::ofstream file(filename);
        file.close();
    }
}
