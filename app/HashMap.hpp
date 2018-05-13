// This header file contains a declaration for a HashMap class, which
// is a separately-chained hash table implementation of a map (i.e.,
// a collection of key/value pairs), where the keys and values are
// strings.  This HashMap consists of a dynamically-allocated array
// of "buckets", each of which is a pointer to the first node in a
// linked list of key/value pairs that have hashed to that bucket.

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <functional>
#include <string>



class HashMap
{
public:
    typedef std::function<unsigned int(const std::string&)> HashFunction;

    // This constant specifies the number of buckets that a HashMap will
    // have when it is initially constructed.
    static constexpr unsigned int initialBucketCount = 10;


public:
    HashMap();

    HashMap(HashFunction hasher);

    HashMap(const HashMap& hm);

    ~HashMap();

    HashMap& operator=(const HashMap& hm);

    // add() takes a key and a value.  If the key is not already stored in
    // this HashMap, the key/value pair is added; if the key is already
    // stored, the function has no effect.
    //
    // If adding the new key/value pair will cause the load factor of this
    // HashMap to exceed 0.8, the following must happen:
    //
    // (1) The number of buckets should be increased by doubling it and
    //     adding 1 (i.e., if there were 10 buckets, increase it to
    //     2 * 10 + 1 = 21).
    // (2) All key/value pairs should be rehashed into their new buckets,
    //     important because changing the number of buckets will likely
    //     change which bucket a particular key hashes to (especialy if
    //     you're using % to determine the index of that bucket).
    void add(const std::string& key, const std::string& value);

    // remove() takes a key and removes it (and its associated value) from
    // this HashMap if it is already present; if not, the function has no
    // effect.
    void remove(const std::string& key);

    // contains() returns true if the given key is in this HashMap, false
    // if not.
    bool contains(const std::string& key) const;

    // value() returns the value associated with the given key in this HashMap
    // if the key is stored in this HashMap; if not, the empty string is
    // returned.  (Going forward, we'll discover that throwing an exception
    // is a better way to handle the scenario where the key is not present,
    // but we'll conquer that at a later date.)
    std::string value(const std::string& key) const;

    // size() returns the number of key/value pairs stored in this HashMap.
    unsigned int size() const;

    // bucketCount() returns the number of buckets currently allocated in
    // this HashMap.
    unsigned int bucketCount() const;

    // loadFactor() returns the proportion of the number of key/value pairs
    // to the number of buckets, a measurement of how "full" the HashMap is.
    // For example, if there are 20 key/value pairs and 50 buckets, we would
    // say that the load factor is 20/50 = 0.4.
    double loadFactor() const;

    // maxBucketSize() returns the number of key/value pairs stored in this
    // HashMap's largest bucket.
    unsigned int maxBucketSize() const;


private:
    // This structure describes the nodes that make up the linked lists in
    // each of this HashMap's buckets.
    struct Node
    {
        std::string key;
        std::string value;
        Node* next;
    };


    // Store the hash function (either the default hash function or the one
    // passed to the constructor as a parameter) in this member variable.
    // When you want to hash a key, call this member variable (i.e., follow
    // it with parentheses and a parameter) just like you would any other
    // function.
    HashFunction hasher;

    Node** buckets;

    unsigned int sz;

    unsigned int numBuckets;
};



#endif // HASHMAP_HPP

