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
 double duration;
 float average;
 std::string file_name;
};
typedef ProfileInfo *ProfileInfoPtr;
class Profiler
{
    public:
    enum SubjectCode
    {
        ANY_FUNCTION_CALL,
        DB_CREATE,
        DB_CLUSTER,
        DB_SEARCH
    };
    static const  std::string SubjectsStrings[];
    static std::map<std::string,ProfileInfoPtr> measurements;
    static void Start(SubjectCode);
    static void Finish(SubjectCode);
    static void Suspend(SubjectCode);
    static void Resume(SubjectCode);
    static void FunctionStarted(std::string file_name, std::string func_name);
    static void FunctionFinished(std::string);
    static void Report(std::string name="");
    static void ReportFunctionProfiling(std::string name);
    static void ReportProfilingSubject(std::string name);
    static void StartDBSearch();
    static void FinishDBSearch();
    static void _Start(std::string, SubjectCode);
    static void _Finish(std::string);
    private:
};
class FunctionProfiling
{
    public:
    std::string function_name;
    FunctionProfiling(std::string file_name, std::string func_name);
    ~FunctionProfiling();
};
#define FUNCTION_PROFILING   FunctionProfiling __local_obj(__FILE__,__FUNCTION__);
