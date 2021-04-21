#include "profiler.hpp"
const std::string Profiler::SubjectsStrings[] = {"AnyCall","DB_CREATE","DB_CLUSTER", "DB_SEARCH"};
std::map<std::string,ProfileInfoPtr> Profiler::measurements = std::map<std::string,ProfileInfoPtr> ();

FunctionProfiling::FunctionProfiling(std::string file_name, std::string func_name):
     function_name(func_name)
{
    Profiler::FunctionStarted(file_name, func_name);
}
FunctionProfiling::~FunctionProfiling()
{
    Profiler::FunctionFinished(function_name);
}
void Profiler::_Start(std::string str, SubjectCode subject)
{
    if ( measurements[str] == nullptr)
    {
        measurements[str] = new ProfileInfo();
    }
    measurements[str]->start = get_ticks();
    measurements[str]->subject = subject;
    measurements[str]->count = 0;
}
void Profiler::Start(SubjectCode subject)
{
    //std::string str = SubjectsStrings[subject];
}
void Profiler::StartDBSearch()
{
    _Start(SubjectsStrings[SubjectCode::DB_SEARCH], SubjectCode::DB_SEARCH);

}
void Profiler::_Finish(std::string str)
{
    if ( measurements[str] == nullptr)
    {
        return ;
    }
    measurements[str]->end = get_ticks();
    int n = measurements[str]->count ++;
    measurements[str]->duration = std::chrono::duration<double>(measurements[str]->end - measurements[str]->start).count(); 
    measurements[str]->average = (n * measurements[str]->average + measurements[str]->duration) / measurements[str]->count;
    measurements[str]->min = measurements[str]->min < measurements[str]->duration ? measurements[str]->min : measurements[str]->duration;
    measurements[str]->max = measurements[str]->max > measurements[str]->duration ? measurements[str]->max : measurements[str]->duration;
}
void Profiler::FinishDBSearch()
{
    _Finish(SubjectsStrings[SubjectCode::DB_SEARCH]);
    ReportProfilingSubject(SubjectsStrings[SubjectCode::DB_SEARCH]);
}
void Profiler::Finish(SubjectCode subject)
{
    _Finish(SubjectsStrings[subject]);
}
void Profiler::FunctionStarted(std::string file_name, std::string func_name)
{
    _Start(func_name, ANY_FUNCTION_CALL);
    measurements[func_name]->file_name = file_name;
}
void Profiler::ReportProfilingSubject(std::string subject)
{
    callLog(DEBUG_LEVEL,"---",subject.c_str(),0);
    fprintf(stderr, "GENERAL PROFILING: time spent= %3.3f milli-seconds\n", measurements[subject]->average*1000.0);

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
    fprintf(stderr, "FUNCTION PROFILING: total time = %3.3f milli-seconds\n", p->average*1000.0);
}