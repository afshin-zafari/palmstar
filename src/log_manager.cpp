    #include "log_manager.hpp"
    
    const int DashLength = 150;
    const int SpaceLength = DashLength /2-10;

    void callLog(LogTags tag, std::string file, std::string function, int line_no)
    {
        //char s[400] ;
        //sprintf(s,"%30.30s, %20.20s, %4d : ", file.c_str(), function.c_str(), line_no);
        std::cerr << std::setw(30) << file << ", ";
        std::cerr << std::setw(30) << function << ", ";
        std::cerr << std::setw(4)  << line_no  << " : " ;
    }
    void LogStart()
    {
        std::string s(DashLength,'-');
        std::string sp(SpaceLength,' ');
        std::cerr << s << std::endl; 
        std::cerr << sp << "Start of Log\n" ;
        std::cerr << s << std::endl; 
    }
    void LogFinish()
    {
        std::string s(DashLength,'-');
        std::string sp(SpaceLength,' ');
        std::cerr << s << std::endl; 
        std::cerr << sp << "End of Log\n" ;
        std::cerr << s << std::endl; 
    }