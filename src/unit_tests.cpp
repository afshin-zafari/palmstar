#include "unit_tests.hpp"
namespace UnitTests{
    namespace ExactMatch{
        FeaturesBitPtr convert_to_bitset(FeatureVectorPtr hand_features)
        {
            FeaturesBitPtr fbp = new FeaturesBits(); 
            FeaturesBits &fb = *fbp;
            fb.reset();
            for( auto element :*hand_features)
            {
                fb <<= 8;
                FeaturesBits bs(element);
                fb |= bs ;
            }
            return fbp ;
        }


        HandKey create_key(FeaturesBitPtr fb)
        {
            return hash_fn(*fb);
        }

        void test_exact_equality()
        {
            HandKerArray &A=* new HandKerArray(Parameters::no_of_hands) ;
            std::map<HandKey, int> dict;
            for (int index = 0; index < Parameters::no_of_hands; index ++)
            {
                auto hand_features = create_random_features();
                auto hand_features_bits = convert_to_bitset(hand_features);
                auto hand_key = create_key(hand_features_bits);
                std::pair p = dict.insert_or_assign(hand_key, index);
                if ( p.second == false){
                    LogWrite(DEBUG_LEVEL,"duplicate key is genereated." ); 
                    continue;
                }
                A[index] = hand_key;
            }
            std::chrono::duration<double> search_time;
            const int N = 1000;
            for(int i=0; i< N; i++)
            {
                int rnd = std::rand() % Parameters::no_of_hands;
                auto start = now();
                auto found = dict[A[rnd]];
                search_time += now() - start;
            }
            LogWrite(DEBUG_LEVEL, "no of hands              = %ld",  Parameters::no_of_hands );
            LogWrite(DEBUG_LEVEL, "no of features per hand  = %d", Parameters::no_features_per_hand );
            LogWrite(DEBUG_LEVEL, "size of one feature      = %d bytes", Parameters::size_of_feature );
            LogWrite(DEBUG_LEVEL, "bits per hand            = %ld ", Parameters::bits_per_hand );
            LogWrite(DEBUG_LEVEL, "Average time for search  = %3.2f micro-seconds", search_time.count()/N*1000000);
        }
    }
    namespace FeatureBasics
    {
        void CreateFeatures()
        {
            LogWrite(DEBUG_LEVEL,"")
            std::string ss, in_str;
            ss = "0123456789ABCDEF" ;     // 16 characters long, one hex charcater for 4 bits
            in_str  = ss + ss + ss + ss;  // it is now 64 hex characters
            in_str += ss + ss + ss + ss;  // and finally 128 hex charcaters == 64 bytes
            OneFeature f(in_str);
            std::string fs= f.to_string();
            LogWrite(DEBUG_LEVEL, "constructed from string: %s", in_str.c_str());
            LogWrite(DEBUG_LEVEL, "converted     to string: %s", fs.c_str() );
            UNIT_TEST_RESULT(fs == in_str);
        }
        void CreateFeaturesIntArray()
        {
            std::vector<int> a({ 1, 2, 3, 4, 5, 6, 7, 8, 9,10,
                                11,12,13,14,15,16,17,18,19,20,
                                21,22,23,24,25,26,27,28,29,30,
                                31,32,33,34,35,36,37,38,39,40,
                                41,42,43,44,45,46,47,48,49,50,
                                51,52,53,54,55,56,57,58,59,60,
                                61,62,63,64                                
                                });
            OneFeature f(a);
            LogWrite(DEBUG_LEVEL, "size of the array : %ld", a.size());
            std::string fs= f.to_string();
            LogWrite(DEBUG_LEVEL, "constructed from array: %s", fs.c_str());
            std::string f_bits= f.to_bit_string();
            LogWrite(DEBUG_LEVEL, "bit string : %s", f_bits.c_str());
            UNIT_TEST_RESULT(f_bits.substr(31*8,8) == "00100000");
        }
    }
}