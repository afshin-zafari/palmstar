    #include "log_manager.hpp"
    void callLog(LogTags tag, std::string text, std::string file, std::string function, int line_no)
    {
        char s[400] ;
        sprintf(s,"%30.30s, %20.20s %4d : %s\n", 
                file.c_str(), function.c_str(), line_no, text.c_str());
        std::cout << s;
    }