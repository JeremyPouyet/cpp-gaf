#include <fstream> //ifstream, ofstream
#include <string>
#include <sys/types.h> // stat, mkdir
#include <sys/stat.h> // stat, mkdir
#include <cerrno> // errno
#include <iostream>
#include <vector>

static const std::string defaultClassName = "__CLASS__";

static const std::vector<std::pair<std::string, std::string> > files = {
    {"Makefile", ""},
    {"Class", ".cpp"},
    {"Class", ".hh"},
    {"problem", ".ini"}
};

static void replace(std::string &file, const std::string &className) {
    size_t start = 0;
    while ((start = file.find(defaultClassName, start)) != std::string::npos) {
        file.replace(start, defaultClassName.length(), className);
        start += className.length();
    }
}

int main(int ac, char **av) {
    if (ac != 2) {
        std::cout << "Usage: generator project_name" << std::endl;
        return -1;
    }
    std::string className(av[1]);
    std::string problemPath = std::string("../problems/") + className;
    if (mkdir(problemPath.c_str(), 0750) == -1) {
        std::cerr << "Could not create directory " << problemPath
                << ". Maybe this problem already exists ?" << std::endl;
        return -1;
    }
    std::ifstream srcFile;
    std::string content, currentFile;
    std::ofstream destFile;
    for (auto file : files) {
        currentFile = "./files/" + file.first + file.second;
        srcFile.open(currentFile, std::ifstream::in);
        if (srcFile.is_open() == false) {
            std::cout << "Error, can't open " << currentFile << std::endl;
            return -1;
        }
        content.assign((std::istreambuf_iterator<char>(srcFile)),
                (std::istreambuf_iterator<char>()));
        srcFile.close();
        replace(content, className);
        currentFile = problemPath + "/" + className + file.second;
        destFile.open(currentFile);
        if (destFile.is_open() == false) {
            std::cout << "Error, can't open " << currentFile << std::endl;
            return -1;
        }
        destFile << content;
        destFile.close();
    }
}
