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
            HandKerArray &A=* new HandKerArray(no_of_hands) ;
            std::map<HandKey, int> dict;
            for (int index = 0; index < no_of_hands; index ++)
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
                int rnd = std::rand() % no_of_hands;
                auto start = now();
                auto found = dict[A[rnd]];
                search_time += now() - start;
            }
            LogWrite(DEBUG_LEVEL, "no of hands              = %ld",  no_of_hands );
            LogWrite(DEBUG_LEVEL, "no of features per hand  = %d", no_features_per_hand );
            LogWrite(DEBUG_LEVEL, "size of one feature      = %d bytes", size_of_feature );
            LogWrite(DEBUG_LEVEL, "bits per hand            = %ld ", bits_per_hand );
            LogWrite(DEBUG_LEVEL, "Average time for search  = %3.2f micro-seconds", search_time.count()/N*1000000);
        }
    }
}