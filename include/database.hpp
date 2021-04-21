#include "feature_set.hpp"
#include <array>

typedef unsigned long long HandID;
typedef unsigned long long PersonID;
class Database
{
    public:
    struct DbStructureType
    {
        int no_of_persons;
        int no_of_records_for_a_hand;
        int no_of_features;
        int bits_per_feature;
    } DbStructure;
    struct DbRecordType
    {
        FeatureSetPtr features;
        HandID hand_id;
        PersonID person_id;
    } ;
    typedef DbRecordType *DbRecordTypePtr;
    typedef std::vector<DbRecordTypePtr> RecordSpase;
    typedef RecordSpase *RecordSpasePtr;
    RecordSpasePtr records;
    void CreateDatabase();
    void PopulateRandom(int bits_distance);
    void DumpRecordsView(int record_start, int record_end, int feature_start, int feature_end);
    void ReportHandsVariations(PersonID person, HandID hand);
};
struct PalmPrintImage
{
    int x,y;
    int features[64];
};
struct VeinImage
{
    int x,y;
    int features[64];
    std::bitset<512> bits;
};
typedef std::array<PalmPrintImage,500> ArrayOfPalmPrintFeatures;
typedef ArrayOfPalmPrintFeatures *ArrayOfPalmPrintFeaturesPtr;
typedef std::array<VeinImage,200> ArrayOfVeinImageFeatures;
typedef ArrayOfVeinImageFeatures *ArrayOfVeinImageFeaturesPtr;
struct HandRecord 
{
    std::array<int,10> geometric_features;
    ArrayOfPalmPrintFeaturesPtr PalmPrintFeatures;
    ArrayOfVeinImageFeaturesPtr VeinFeatures;
    HandRecord ();
};
/*
time profiling
memory consumption
accuracy %

trace a single query search
for p in partitions(K-2,K+2)
    for r in records(p)
        for i,j
            dist (Fi,Fj) -> Top K -> GV
dist: Euclidian, Hamming , likelihood
GV: 1,2,3
buckets: 1,2,3
masks: no, yes
processor: GPU, CPU
run: sequential , parallel
gpu-code: open_cv_gpu, open_cl
cpu-code: internal C++, opencv


*/