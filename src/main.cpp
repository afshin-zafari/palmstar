#include "main.hpp"

int main()
{ 
    LogStart();
    UnitTests::ExactMatch::test_exact_equality();
    LogFinish();
}