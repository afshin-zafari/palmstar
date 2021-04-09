
#include "unit_tests.hpp"
namespace UnitTests
{
    namespace DatabaseTests
    {
        void CreateRandomDB()
        {
            FUNCTION_PROFILING;
            Database db;
            const int bits_distance_for_tweak = 5;
            db.DbStructure.bits_per_feature = Parameters::bits_per_feature;
            db.DbStructure.no_of_features = 10;
            db.DbStructure.no_of_persons = 20;
            db.DbStructure.no_of_records_for_a_hand = 3;
            db.CreateDatabase();
            db.PopulateRandom(bits_distance_for_tweak);
            db.DumpRecordsView(0,3,0,5);
            UNIT_TEST_RESULT(true);
        }
    }
}