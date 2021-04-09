#include "profiler.hpp"
FunctionProfiling::FunctionProfiling(std::string file_name, std::string func_name):
     function_name(func_name)
{
    Profiler::FunctionStarted(file_name, func_name);
}
FunctionProfiling::~FunctionProfiling()
{
    Profiler::FunctionFinished(function_name);
}
void Profiler::_Start(std::string str, Subjects subject)
{
    if ( measurements[str] == nullptr)
    {
        measurements[str] = new ProfileInfo();
    }
    ProfileInfo &p = *measurements[str];
    p.start = get_ticks();
    p.subject = subject;
    p.count = 0;
}
void Profiler::Start(Subjects subject)
{
    auto str = SubjectsStrings[subject];
    _Start(str, subject);
}
void Profiler::_Finish(std::string str)
{
    if ( measurements[str] == nullptr)
    {
        return ;
    }
    ProfileInfo &p = *measurements[str];
    p.end = get_ticks();
    int n = p.count ++;
    p.duration = std::chrono::duration_cast<std::chrono::microseconds>(p.end - p.start).count(); // micro seconds
    p.average = (n * p.average + p.duration) / p.count;
    p.min = p.min < p.duration ? p.min : p.duration;
    p.max = p.max > p.duration ? p.max : p.duration;
}
void Profiler::Finish(Subjects subject)
{
    auto str = SubjectsStrings[subject];
    _Finish(str);
}
void Profiler::FunctionStarted(std::string file_name, std::string func_name)
{
    _Start(func_name, ANY_FUNCTION_CALL);
    measurements[func_name]->file_name = file_name;
}
void Profiler::FunctionFinished(std::string f_name)
{
    _Finish(f_name);
    ReportFunctionProfiling(f_name);
}
void Profiler::ReportFunctionProfiling(std::string name)
{
    auto p = measurements[name];
    callLog(DEBUG_LEVEL,p->file_name,name,0);
    fprintf(stderr, "time spent= %3.3f milli-seconds\n", p->average/1000);
}