#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <vector>
class Request {
    public:
        std::string prefix;
        std::vector<std::string> args;
        std::string command;
        std::string trailing;
        bool is_valid;
};

#endif 