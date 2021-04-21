#include <list>
#include "palm_features.hpp"
class FeatureNode
{
    public:
    FeatureNode *Left,*Right;
    OneFeaturePtr NodeValue;
    FeatureNode();
    FeatureNode(OneFeaturePtr);
    void InsertFeature(OneFeaturePtr fp);
};
typedef FeatureNode *FeatureNodePtr ;
class FeatureTree
{
    public:
    FeatureNodePtr root;    
    FeatureTree();
    void InsertFeature(OneFeaturePtr f);
};