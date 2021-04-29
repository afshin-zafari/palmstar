#include "manus_types.hpp"
Person::Person()
{
    RightHandPalm = new Hand();
    RightHandBack= new Hand();
    LeftHandPalm= new Hand();
    LeftHandBack= new Hand();
}
Feature::Feature()
{
    Descriptor = new DescriptorType();
}
Feature::~Feature()
{
    delete Descriptor;
}
void DescriptorType::CopyToBits()
{
    for(int i=0; i < Bytes.size(); i++)    
    {
        BitString bits (static_cast<int>(Bytes[i]));
        Bits <<= 8;
        Bits |= bits;
    }

}