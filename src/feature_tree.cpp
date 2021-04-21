#include "feature_tree.hpp"
FeatureNode::FeatureNode()
{
}
FeatureNode::FeatureNode(OneFeaturePtr fp)
{
    NodeValue = new OneFeature(fp->_no_of_bytes);
    NodeValue->copy_value_from(fp);    
}
FeatureTree::FeatureTree()
{
    root = new FeatureNode();
}
void FeatureTree::InsertFeature(OneFeaturePtr fp)
{
    root->InsertFeature(fp);
}
void FeatureNode::InsertFeature(OneFeaturePtr fp)
{
    if (NodeValue == nullptr)
    {
        NodeValue = new OneFeature(fp->_no_of_bytes);
        NodeValue->copy_value_from(fp);
        return;
    }
    if (NodeValue->DifferenceWith(fp)<0.5)
    {
        if ( Left == nullptr)
        {
            Left = new FeatureNode(fp);
            return;            
        }
        Left->InsertFeature(fp);
    }
    else
    {
        if ( Right == nullptr)
        {
            Right = new FeatureNode(fp);
            return;            
        }
        Right->InsertFeature(fp);
    }
}