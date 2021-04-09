#include <map>
#include <chrono>
#include "log_manager.hpp"
auto get_ticks=[](){return std::chrono::steady_clock::now();};
typedef std::chrono::time_point<std::chrono::steady_clock> qrt_time_t;
struct ProfileInfo
{
 uint subject;
 qrt_time_t start, end;
 ulong count, min, max;
 //std::chrono::duration<double> 
 long duration;
 float average;
 std::string file_name;
};
typedef ProfileInfo *ProfileInfoPtr;
class Profiler
{
    public:
    enum Subjects
    {
        ANY_FUNCTION_CALL,
        DB_CREATE,
        DB_CLUSTER,
        DB_SEARCH,
    };
    static std::string SubjectsStrings[];
    static std::map<std::string,ProfileInfoPtr> measurements;
    static void Start(Subjects);
    static void Finish(Subjects);
    static void Suspend(Subjects);
    static void Resume(Subjects);
    static void FunctionStarted(std::string file_name, std::string func_name);
    static void FunctionFinished(std::string);
    static void Report(std::string name="");
    static void ReportFunctionProfiling(std::string name);
    private:
    static void _Start(std::string, Subjects);
    static void _Finish(std::string);
};
std::string Profiler::SubjectsStrings[] = {"DB_CREATE","DB_CLUSTER", "DB_SEARCH"};
std::map<std::string,ProfileInfoPtr> Profiler::measurements = * new std::map<std::string,ProfileInfoPtr> ();
class FunctionProfiling
{
    public:
    std::string function_name;
    FunctionProfiling(std::string file_name, std::string func_name);
    ~FunctionProfiling();
};
#define FUNCTION_PROFILING   FunctionProfiling __local_obj(__FILE__,__FUNCTION__);
