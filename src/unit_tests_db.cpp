
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
        void BruteForcePerformanceTest()
        {
            return;
            FUNCTION_PROFILING;
            const int N = 400;
            const int feature_per_hand = 700;
            typedef std::bitset<512> bits;
            std::array<bits,N*feature_per_hand> *features =  new std::array<bits,N*feature_per_hand>();
            std::array<bits,  feature_per_hand> *query=  new std::array<bits,feature_per_hand>();
            int cnt;
            for(auto f: *features)
            {
                    for(auto q: *query)
                    {
                        cnt = (f^q).count();
                    }
            }
            LogWrite(DEBUG_LEVEL,"no of hands =%d, features per hand = %d",N,feature_per_hand, cnt);
            delete features;
            delete query;
            UNIT_TEST_RESULT(true);
        }
        void BruteForcePerformanceTest2()
        {
            FUNCTION_PROFILING;
            const int Hands = 10;
            const int Descriptors_per_hand = 500;
            typedef std::bitset<512> Descriptor;
            const int Descriptors_in_DB = Hands*Descriptors_per_hand;
            Descriptor *db_records = new Descriptor[Descriptors_in_DB];
            Descriptor *query= new Descriptor[Descriptors_per_hand];
            int cnt;
            for(int i=0;i<Descriptors_in_DB; i++)
            {
                for(int j=0;j<Descriptors_per_hand; j++)
                {
                    cnt = (db_records[i]^query[j]).count();
                }
            }
            LogWrite(DEBUG_LEVEL,"no of hands =%d, features per hand = %d",Hands,Descriptors_per_hand, cnt);
            delete db_records;
            delete query;
            UNIT_TEST_RESULT(true);
        }
        void TestMatrixCompare()
        {            
            FUNCTION_PROFILING;
            const long D = 500;
            const long  N = 100;
            typedef std::bitset<512> bits;
            bits *query= new bits[D];
            for(int i=0; i<D;i++)
            {
                query[i] = std::rand() * std::rand();
            }
            Profiler::StartDBSearch();
            ulong max_distance=0, min_distance=512,avg_distance, sum_distance =0;
            std::map<ulong,ulong> histogram;
            for(int j=0;j<D;j++)
            {
                for(int i=j+1;i<D; i++)
                {
                    auto diff = (query[i] ^ query[j]).count();
                    max_distance = diff > max_distance ? diff : max_distance;
                    min_distance = diff < min_distance ? diff : min_distance;                    
                    sum_distance += diff;
                    histogram[diff ] ++;
                }
            }
            std::vector<std::pair<ulong,ulong>> top_hist;
            
            for(auto kv: histogram)
            {
                top_hist.push_back(kv);
            }
            auto compare = [](std::pair<ulong,ulong>  &a, std::pair<ulong,ulong> &b){return b.second < a.second;};
            std::sort( top_hist.begin(),top_hist.end(), compare);
            int cnt=0;
            for( auto sorted: top_hist)
            {
                LogWrite(DEBUG_LEVEL,"top_10 sorted[%ld]=%ld", sorted.first, sorted.second );    
                if ( cnt++ > 10 ) 
                    break;
            }
            typedef std::pair<ulong,ulong>  point;
            typedef std::array<point,10> cluster_center;
            auto eucledean_dist = [](point a, point b)
            {
                auto x = (a.first - b.first);
                auto y = (a.second- b.second);
                return x*x + y*y;
            };
            std::vector<cluster_center> cluster;
            std::vector<std::pair<ulong,ulong>> top_cluster;
            ulong cl_id=0;
            for(int i=0;i<20;i++)
            {
                point p1{std::rand()%100,std::rand()%100};
                cluster_center a{p1,p1,p1,p1,p1,p1,p1,p1,p1,p1};
                cluster.push_back(a);
            }
            for(auto cl: cluster)
            {
                ulong sum=0;
                for(int i=0;i<cl.size();i++)
                {
                    auto diff = eucledean_dist(cl[i],top_hist[i]);
                    sum += diff;
                }
                top_cluster.push_back ( std::pair<ulong,ulong>(cl_id,sum)),
                cl_id++;
            }
            std::sort( top_cluster.begin(),top_cluster.end(), compare);
            for( auto sorted: top_cluster)
            {
                LogWrite(DEBUG_LEVEL,"cluster sorted[%ld]=%ld", sorted.first, sorted.second );    
            }

            Profiler::FinishDBSearch();

            LogWrite(DEBUG_LEVEL,"no of hands =%ld, features per hand = %ld",N,D );
            LogWrite(DEBUG_LEVEL,"distance min= %ld, max= %ld, sum = %ld, hist.size:%ld",min_distance, max_distance, sum_distance,histogram.size());
            for(auto kv: histogram)
            {
                LogWrite(DEBUG_LEVEL,"map[%ld] = %ld",kv.first, kv.second);
            }
            UNIT_TEST_RESULT(true);
        }
        void LoadPersonFromJSONFile()
        {
            std::string json_filename("./person_00.json");
            auto p = CreateNewPersonFromJSON(json_filename);
            LogWrite(DEBUG_LEVEL,"index finger length : %f",p->LeftHandPalm->HandGeometries.IndexFinger.Length )
            LogWrite(DEBUG_LEVEL,"Right hand.palm-print-feature[0].keypont.y : %f",p->RightHandPalm->PalmPrintFeatures[0]->Keypoint.y)

            UNIT_TEST_RESULT((p->LeftHandPalm->HandGeometries.IndexFinger.Length - 72.42671873646435) < 1e-6);
            UNIT_TEST_RESULT((p->RightHandPalm->PalmPrintFeatures[0]->Keypoint.y - 190.8213043) < 1e-6);
            UNIT_TEST_RESULT( (p->RightHandPalm->PalmPrintFeatures[2]->Descriptor->Bytes[10] == static_cast<std::byte>(244)));
        }
    }
}