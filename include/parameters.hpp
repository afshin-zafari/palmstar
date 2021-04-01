#pragma once 
namespace Parameters
{
    const long no_of_hands = 100;
    const int no_features_per_hand = 50;
    const int size_of_feature = 64;
    const int bytes_per_feature = size_of_feature;
    const int bits_per_feature = size_of_feature * 8;
    const long bits_per_hand = bits_per_feature *  no_features_per_hand;
}