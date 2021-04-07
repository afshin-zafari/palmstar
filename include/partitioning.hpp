#include "feature_set.hpp"

struct Span 
{
    int start, end;
};
class FeatureSetPartition
{
    public:
    FeatureSetPtr originalFeatureSet;
    Span  columnSpan, rowSpan;
    FeatureArray get_feature_part(int i, int j);
};
typedef FeatureSetPartition *FeatureSetPartitionPtr;
typedef std::vector<FeatureSetPartitionPtr> *PartitionsPtr;
class FeatureSetView
{
    public:
    PartitionsPtr parttions;
    FeatureSetPartitionPtr get_partition(int i, int j );
};