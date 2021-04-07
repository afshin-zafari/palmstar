#include "palm_features.hpp"
class FeatureSet ;
typedef FeatureSet *FeatureSetPtr;
class FeatureSet {
public:
  FeatureSet(int, int);
  int             no_of_features;
  FeatureArrayPtr FeatureValues;
  OneFeature     *get_feature(int);
  void            set_feature_value(int, OneFeature *);
  void            PopulateRandom();
  void            TweakBits(int no_of_bits_per_feature);
  int             CopyTo(FeatureSetPtr fs_dest);
  std::string     to_string();
};
