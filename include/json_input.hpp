#include <assert.h>
#include <fstream>
#include <streambuf>
#include <sstream>
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON 
#include "manus_types.hpp"
#include "log_manager.hpp"
PersonPtr CreateNewPersonFromJSON(std::string json_filename);