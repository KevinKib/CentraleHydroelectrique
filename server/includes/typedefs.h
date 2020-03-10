/**
 * Header for the different typedef
 **/

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <string>
#include <utility>
#include <map>
#include "../libs/json/single_include/nlohmann/json.hpp"

using ushort = unsigned short;
using uint = unsigned int;
using JSON = nlohmann::json;

using IDHydraulic = std::string;
using IDTurbine = std::string;
using Attribute = std::string;

using TCPResponse = std::pair<bool, std::string>;

#endif