#include <gtest/gtest.h>
#include "HashMap.hpp"


namespace
{
    std::string key1 = "foo";
    std::string val1 = "bar";
    std::string key2 = "baz";
    std::string val2 = "qux";
    std::string key3 = "ab";
    std::string val3 = "cd";
    std::string key4 = "abc";
    std::string val4 = "def";
    std::string key5 = "abcd";
    std::string val5 = "efgh";
    std::string key6 = "abcde";
    std::string val6 = "fghij";
    std::string key7 = "bcde";
    std::string val7 = "fghi";
    std::string key8 = "bcd";
    std::string val8 = "efg";
    std::string key9 = "bc";
    std::string val9 = "de";
    std::string key10 = "abcdefghij";
    std::string val10 = "asdf";
}


TEST(TestHashMap, sizeOfNewlyCreatedHashMapIsZero)
{
    HashMap empty;
    ASSERT_EQ(0, empty.size());
}


TEST(TestHashMap, sizeIncreasesAfterAdd)
{
    HashMap hm;
    hm.add(key1, val1);
    ASSERT_EQ(1, hm.size());
    
    hm.add(key2, val2);
    ASSERT_EQ(2, hm.size());
}


TEST(TestHashMap, sizeIncreasesAfterAddToFirstBucket)
{
    HashMap hm;
    hm.add(key10, val10);
    ASSERT_EQ(1, hm.size());
}


TEST(TestHashMap, sizeDoesntChangeAfterDuplicateAdd)
{
    HashMap hm;
    hm.add(key1, val1);
    hm.add(key1, val1);
    ASSERT_EQ(1, hm.size());

    hm.add(key1, val2);
    ASSERT_EQ(1, hm.size());
}


TEST(TestHashMap, returnsCorrectValueAfterAdd)
{
    HashMap hm;
    hm.add(key1, val1);
    ASSERT_EQ(val1, hm.value(key1));

    hm.add(key2, val2);
    ASSERT_EQ(val2, hm.value(key2));
}


TEST(TestHashMap, returnsCorrectValueAfterDuplicateAdd)
{
    HashMap hm;
    hm.add(key1, val1);
    hm.add(key1, val2);
    ASSERT_EQ(val1, hm.value(key1));
}


TEST(TestHashMap, returnsEmptyStringIfKeyIsInvalid)
{
    HashMap hm;
    ASSERT_EQ("", hm.value(key1));

    hm.add(key1, val1);
    ASSERT_EQ("", hm.value(key2));
}


TEST(TestHashMap, containsReturnsFalseIfKeyIsInvalid)
{
    HashMap hm;
    ASSERT_FALSE(hm.contains(key1));

    hm.add(key1, val1);
    ASSERT_FALSE(hm.contains(key2));
}


TEST(TestHashMap, containsReturnsTrueIfKeyIsValid)
{
    HashMap hm;
    hm.add(key1, val1);
    ASSERT_TRUE(hm.contains(key1));

    hm.add(key2, val2);
    ASSERT_TRUE(hm.contains(key2));
}


TEST(TestHashMap, removeIsSuccessful)
{
    HashMap hm;
    hm.add(key1, val1);
    hm.remove(key1);
    ASSERT_FALSE(hm.contains(key1));

    hm.add(key1, val1);
    hm.add(key2, val2);
    hm.remove(key2);
    ASSERT_FALSE(hm.contains(key2));
}


TEST(TestHashMap, removeIsSuccessfulForFirstBucket)
{
    HashMap hm;
    hm.add(key10, val10);
    hm.remove(key10);
    ASSERT_FALSE(hm.contains(key10));
    ASSERT_EQ(0, hm.size());
}


TEST(TestHashMap, removeDoesNothingIfKeyIsInvalid)
{
    HashMap hm;
    hm.remove(key1);
    ASSERT_EQ(0, hm.size());
    ASSERT_FALSE(hm.contains(key1));
}


TEST(TestHashMap, sizeDecreasesAfterRemove)
{
    HashMap hm;
    hm.add(key1, val1);
    hm.remove(key1);
    ASSERT_EQ(0, hm.size());

    hm.add(key1, val1);
    hm.add(key2, val2);
    hm.remove(key2);
    ASSERT_EQ(1, hm.size());
    hm.remove(key1);
    ASSERT_EQ(0, hm.size());
}


TEST(TestHashMap, returnsCorrectBucketCountIfEmpty)
{
    unsigned int numBuckets = 10;
    HashMap hm;
    ASSERT_EQ(numBuckets, hm.bucketCount());
}


TEST(TestHashMap, returnsCorrectBucketCountBeforeRehashing)
{
    unsigned int numBuckets = 10;
    HashMap hm;

    hm.add(key1, val1);
    hm.add(key2, val2);
    ASSERT_EQ(numBuckets, hm.bucketCount());
    
    hm.remove(key2);
    ASSERT_EQ(numBuckets, hm.bucketCount());
    hm.remove(key1);
    ASSERT_EQ(numBuckets, hm.bucketCount());
}


TEST(TestHashMap, returnsCorrectBucketCountAfterRehashing)
{
    unsigned int numBuckets = 10;
    unsigned int newNumBuckets = 2*numBuckets + 1;
    HashMap hm;

    hm.add(key1, val1);
    hm.add(key2, val2);
    hm.add(key3, val3);
    hm.add(key4, val4);
    hm.add(key5, val5);
    hm.add(key6, val6);
    hm.add(key7, val7);
    hm.add(key8, val8);
    ASSERT_EQ(numBuckets, hm.bucketCount());
    
    hm.add(key9, val9);
    ASSERT_EQ(newNumBuckets, hm.bucketCount());
}


TEST(TestHashMap, returnsCorrectLoadFactorIfEmpty)
{
    HashMap hm;
    ASSERT_EQ(0.0, hm.loadFactor());
}


TEST(TestHashMap, returnsCorrectLoadFactorBeforeRehashing)
{
    unsigned int numBuckets = 10;
    HashMap hm;

    hm.add(key1, val1);
    ASSERT_EQ((double) 1/numBuckets, hm.loadFactor());

    hm.add(key2, val2);
    ASSERT_EQ((double) 2/numBuckets, hm.loadFactor());
}


TEST(TestHashMap, returnsCorrectLoadFactorAfterRehashing)
{
    unsigned int numBuckets = 10;
    unsigned int newNumBuckets = 2*numBuckets + 1;
    HashMap hm;

    hm.add(key1, val1);
    hm.add(key2, val2);
    hm.add(key3, val3);
    hm.add(key4, val4);
    hm.add(key5, val5);
    hm.add(key6, val6);
    hm.add(key7, val7);
    hm.add(key8, val8);
    ASSERT_EQ((double) 8/numBuckets, hm.loadFactor());
    
    hm.add(key9, val9);
    ASSERT_EQ((double) 9/newNumBuckets, hm.loadFactor());
}


TEST(TestHashMap, returnsZeroMaxBucketSizeIfEmpty)
{
    HashMap hm;
    ASSERT_EQ(0, hm.maxBucketSize());
}


TEST(TestHashMap, returnsCorrectMaxBucketSizeWithDifferentKeyLengths)
{
    HashMap hm;
    hm.add(key1, val1);
    ASSERT_EQ(1, hm.maxBucketSize());

    hm.add(key2, val2);
    ASSERT_EQ(2, hm.maxBucketSize());

    hm.add(key5, val5);
    ASSERT_EQ(2, hm.maxBucketSize());
    ASSERT_EQ(3, hm.size());
}


TEST(TestHashMap, canUseCustomHasher)
{
    HashMap hm{[](const std::string& str) { return 0; }};

    //Add & Size
    hm.add(key1, val1);
    ASSERT_EQ(1, hm.size());

    //Value
    ASSERT_EQ(val1, hm.value(key1));

    //Remove & Contains
    hm.remove(key1);
    ASSERT_FALSE(hm.contains(key1));

    //MaxBucketSize
    hm.add(key1, val1);
    hm.add(key2, val2);
    hm.add(key3, val3);
    hm.add(key4, val4);
    ASSERT_EQ(4, hm.maxBucketSize());
}


TEST(TestHashMap, canCopyBucketsUsingCopyConstructor)
{
    HashMap hm1;
    hm1.add(key1, val1);
    hm1.add(key2, val2);
    hm1.add(key3, val3);
    
    HashMap hm2{hm1};
    ASSERT_TRUE(hm2.contains(key1));
    ASSERT_EQ(val2, hm2.value(key2));
    ASSERT_EQ(2, hm2.maxBucketSize());
}


TEST(TestHashMap, canCopyBucketsUsingAssignmentOperator)
{
    HashMap hm1;
    hm1.add(key1, val1);
    hm1.add(key2, val2);
    hm1.add(key3, val3);

    HashMap hm2;
    hm2.add(key4, val4);
    hm2.add(key5, val5);

    hm2 = hm1;
    ASSERT_TRUE(hm2.contains(key1));
    ASSERT_TRUE(hm2.contains(key2));
    ASSERT_EQ(val3, hm2.value(key3));

    ASSERT_EQ(hm1.size(), hm2.size());
    ASSERT_EQ(hm1.maxBucketSize(), hm2.maxBucketSize());
}
