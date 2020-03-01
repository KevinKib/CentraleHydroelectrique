#include <iostream>
#include "../libs/http/httplib.h"
#include "../libs/json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, const char **argv)
{
    using namespace httplib;

    Server server;
    json j;
    j["toto"] ="titi";
    
    std::cout << j << std::endl;

    return 0;
}