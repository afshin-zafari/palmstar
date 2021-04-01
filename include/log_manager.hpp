#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
  
enum LogTags
{
    DEBUG_LEVEL,
    INFO_LEVEL
}
_LogTags;
#ifndef LogWrtie
#define LogWrite(tag,format, args...) \
        callLog(tag,__FILE__,__FUNCTION__,__LINE__);\
        fprintf(stderr, format, ##args);\
        fprintf(stderr, "\n");
#endif
void callLog(LogTags tag, std::string file, std::string function, int line_no);
void LogStart();
void LogFinish();

