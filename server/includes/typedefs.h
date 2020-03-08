/**
 * Header for the different typedef
 **/

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <string>
#include <map>
#include "../libs/json/single_include/nlohmann/json.hpp"

using ushort = unsigned short;
using uint = unsigned int;
using JSON = nlohmann::json;

using IDHydrolic = std::string;
using IDTurbine = std::string;
using Attribute = std::string;

#endif