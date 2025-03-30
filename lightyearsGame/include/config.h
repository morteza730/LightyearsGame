#pragma once
#include <string>

std::string get_resource(){
    #ifdef NDEBUG
        return "assets/";
    #else
        return "E:/C++/projects/game dev/light_years_project/lightyearsGame/assets/";
    #endif
}
