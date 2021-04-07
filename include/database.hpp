#include "feature_set.hpp"

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