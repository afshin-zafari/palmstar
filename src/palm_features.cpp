#include "palm_features.hpp"
#include "log_manager.hpp"

OneFeature::OneFeature(int no_of_bytes)
{
    this->Bytes = new ByteVector(no_of_bytes);
    _no_of_bytes = no_of_bytes;
}
OneFeature::OneFeature(std::string hex_string)
{
    _no_of_bytes = hex_string.length()/2;
    this->Bytes = new ByteVector(_no_of_bytes);

    if (Bits.size() < _no_of_bytes * 8)
        Bits.reset();

    ByteVector &_Bytes = *Bytes;
    short int b;
    for(int i=0; i < _no_of_bytes; i++)    
    {
        std::istringstream ss( hex_string.substr(i*2,2));
        ss >> std::hex >> b;
        _Bytes[i] = (byte)b;
        if ( Bits.size() < _no_of_bytes * 8)
        {
            FeatureDataType bits (static_cast<long>(b));
            Bits <<= 8;
            Bits |= bits;
        }
    }
}
OneFeature::OneFeature(std::vector<int>  &list)
{
    _no_of_bytes = list.size();
    this->Bytes = new ByteVector(_no_of_bytes);
    ByteVector &_Bytes = *Bytes;
    if (Bits.size() >= _no_of_bytes * 8)
        Bits.reset();
    short int b;
    for(int i=0; i < _no_of_bytes; i++)    
    {
        _Bytes[i] = (byte)list[i];
        if ( Bits.size() >= _no_of_bytes * 8)
        {
            FeatureDataType bits (static_cast<long>(list[i]));
            Bits <<= 8;
            Bits |= bits;
        }
    }
}
std::string OneFeature::to_string()
{
    ByteVector &_Bytes = *Bytes;
    std::ostringstream ss;
    char s[3];
    for(int i=0; i< _no_of_bytes; i++)    
    {
        sprintf(s,"%02X",(short int)_Bytes[i]);
        ss << s ;
    }
    return ss.str();
}
std::string OneFeature::to_bit_string()
{
    LogWrite(DEBUG_LEVEL, "no_ of bytes : %d", _no_of_bytes);
    LogWrite(DEBUG_LEVEL, "bits : %ld, _no_of_bytes * 8:%d", Bits.size(), _no_of_bytes * 8);
    if ( Bits.size() >= _no_of_bytes * 8)
        return Bits.to_string();
    return "";
}
byte OneFeature::get_byte_from_bitset(int byte_index)
{
    int  b = 0;
    for(int i=0; i< 8; i++)
    {
        if (Bits[byte_index * 8+i]) 
            b |= 1<<(7-i);
    }
    return (byte)b;
}

void OneFeature::get_value_from_bits()
{
    ByteVector &_Bytes = *Bytes;
    for(int bi =0; bi < _no_of_bytes; bi++)
    {
        auto bval=get_byte_from_bitset(bi);
        _Bytes[bi]= bval;
    }
}
void OneFeature::PopulateRandom()
{
    ByteVector &_Bytes = *Bytes;
    for(int i=0; i < _no_of_bytes; i++)    
    {
        byte b = (byte)(std::rand() % 256); 
        _Bytes[i] = b;
        if ( Bits.size() >= _no_of_bytes * 8)
        {
            FeatureDataType bits (static_cast<long>(b));
            Bits <<= 8;
            Bits |= bits;
        }
    }   
}
void OneFeature::TweakBits(int no_of_bits)
{
    //LogWrite(DEBUG_LEVEL,"before tweak: %s", to_string().c_str())
    auto fcopy = Bits;
    for(int j=0;j < no_of_bits;  j++)    
    {
        int i = std::rand() % Bits.size(); 
        Bits[i] = Bits[i] ^ true;        
    }
    get_value_from_bits();
    //LogWrite(DEBUG_LEVEL," after tweak: %s", to_string().c_str());
    //LogWrite(DEBUG_LEVEL," diff count : %ld", (fcopy ^ Bits).count());
    assert(((fcopy ^ Bits).count() >0 ));
}
float OneFeature::DifferenceWith(OneFeature*f)
{
    double result = 0.0;
    auto diff = f->Bits ^ Bits;
    LogWrite(DEBUG_LEVEL,"dif-bits count:%ld",diff.count());
    result = (diff.count() * 1.0) / Bits.size();
    return result;
}
void OneFeature::copy_value_from(OneFeature *f)
{
    Bits = FeatureDataType(f->Bits.to_string());
    get_value_from_bits();
}
uint OneFeature::GetBitCountGroup()
{
    return Bits.count() / BitCountGroupSize ;
}