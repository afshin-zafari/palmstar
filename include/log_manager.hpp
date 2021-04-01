#include <iostream>
#pragma once
  
enum LogTags
{
    DEBUG_LEVEL,
    INFO_LEVEL
}
_LogTags;
#ifndef LogWrtie
#define LogWrite(tag,text) \
        callLog(tag,text,__FILE__,__PRETTY_FUNCTION__,__LINE__)
#endif
void callLog(LogTags tag, std::string text, std::string file, std::string function, int line_no);
