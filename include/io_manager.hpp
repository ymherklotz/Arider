#ifndef IO_MANAGER_HPP
#define IO_MANAGER_HPP

#include <string>
#include <vector>

class IOManager
{
public:
    static bool readFileToBuffer(const std::string &file_path, std::vector<unsigned char> &buffer);
};


#endif
