#include <gtest/gtest.h>
#include <string>
#include "HashMap.hpp"


TEST(HashMap_SanityChecks, canConstructWithNoArguments)
{
    HashMap hm1;
}


TEST(HashMap_SanityChecks, canConstructWithLambdaExpression)
{
    HashMap hm1{[](const std::string& s) { return 0; }};
}


namespace
{
    unsigned int someHashFunction(const std::string& s)
    {
        return 19;
    }
}


TEST(HashMap_SanityChecks, canConstructWithFunction)
{
    HashMap hm1{someHashFunction};
}


namespace
{
    void takesHashMapByValue(HashMap hm)
    {
    }
}


TEST(HashMap_SanityChecks, canCopyConstruct)
{
    HashMap hm1;
    HashMap hm2{hm1};
    HashMap hm3 = hm2;
    takesHashMapByValue(hm1);
}


TEST(HashMap_SanityChecks, canAssign)
{
    HashMap hm1;
    HashMap hm2;
    hm1 = hm2;
}


TEST(HashMap_SanityChecks, canAddKeyValuePair)
{
    HashMap hm1;
    std::string key{"Boo"};
    std::string value{"perfect"};
    hm1.add(key, value);
}


TEST(HashMap_SanityChecks, canRemove)
{
    HashMap hm1;
    std::string key{"Alex"};
    hm1.remove(key);
}


TEST(HashMap_SanityChecks, canCheckIfContainsKey)
{
    HashMap hm1;
    std::string key{"Boo"};
    bool b = hm1.contains("Boo");
    b = !b;
}


TEST(HashMap_SanityChecks, canGetValueAssociatedWithKey)
{
    HashMap hm1;
    std::string key{"Boo"};
    std::string value = hm1.value(key);
}


TEST(HashMap_SanityCheckTests, canGetSize)
{
    HashMap hm1;
    unsigned int i = hm1.size();
    ++i;
}


TEST(HashMap_SanityCheckTests, canGetBucketCount)
{
    HashMap hm1;
    unsigned int b = hm1.bucketCount();
    ++b;
}


TEST(HashMap_SanityCheckTests, canGetLoadFactor)
{
    HashMap hm1;
    double lf = hm1.loadFactor();
    lf += 1.0;
}


TEST(HashMap_SanityCheckTests, canGetMaxBucketSize)
{
    HashMap hm1;
    unsigned int mbs = hm1.maxBucketSize();
    ++mbs;
}

