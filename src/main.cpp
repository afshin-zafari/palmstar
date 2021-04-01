#include "main.hpp"
#include "create_features.hpp"
#include <map>


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

int main()
{ 
    LogWrite (DEBUG_LEVEL, "test 1");
    
    return -1;
    HandKerArray &A=* new HandKerArray(no_of_hands) ;
    std::map<HandKey, int> dict;
    for (int index = 0; index < no_of_hands; index ++)
    {
        auto hand_features = create_random_features();
        auto hand_features_bits = convert_to_bitset(hand_features);
        auto hand_key = create_key(hand_features_bits);
        std::pair p = dict.insert_or_assign(hand_key, index);
        if ( p.second == false){
            std::cout << "duplicate key is genereated.\n" ;
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
    std::cout << "no of hands " <<  no_of_hands << std::endl;

    std::cout << "no_features_per_hand " <<  no_features_per_hand << std::endl;
    std::cout << "size of feature in bytes " << size_of_feature << std::endl;
    std::cout << "bits per hand "<<  bits_per_hand << std::endl;

    std::cout << "Average elapsed time for search : " << search_time.count()/N << "s\n";

}