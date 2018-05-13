#include "HashMap.hpp"


HashMap::HashMap()
    : hasher{ [this](const std::string& str) 
              { return str.length() % this->numBuckets; } },
      buckets{new Node*[initialBucketCount]},
      sz{0},
      numBuckets{initialBucketCount}
{
    for (int i = 0; i < numBuckets; i++)
    {
        buckets[i] = nullptr;
    }
}


HashMap::HashMap(HashFunction hasher)
    : hasher{hasher},
      buckets{new Node*[initialBucketCount]},
      sz{0},
      numBuckets{initialBucketCount}
{
    for (int i = 0; i < numBuckets; i++)
    {
        buckets[i] = nullptr;
    }
}


HashMap::HashMap(const HashMap& hm)
    : hasher{hm.hasher},
      buckets{new Node*[hm.numBuckets]},
      sz{hm.sz},
      numBuckets{hm.numBuckets}
{
    for (int i = 0; i < numBuckets; i++)
    {
        Node* current = hm.buckets[i];
        Node** ptr = &buckets[i];
        *ptr = nullptr;

        while (current != nullptr)
        {
            Node* newNode = new Node;
            newNode->key = current->key;
            newNode->value = current->value;
            newNode->next = nullptr;

            *ptr = newNode;
            ptr = &newNode->next;
            current = current->next;
        }
    }
}


HashMap::~HashMap()
{
    for (int i = 0; i < numBuckets; i++)
    {
        Node* current = buckets[i];
        while (current != nullptr)
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] buckets;
    buckets = nullptr;
}


HashMap& HashMap::operator=(const HashMap& hm)
{
    if (this != &hm)
    {
        Node** newBuckets = new Node*[hm.numBuckets];
        for (int i = 0; i < hm.numBuckets; i++)
        {
            Node* current = hm.buckets[i];
            Node** ptr = &newBuckets[i];
            *ptr = nullptr;

            while (current != nullptr)
            {
                Node* newNode = new Node;
                newNode->key = current->key;
                newNode->value = current->value;
                newNode->next = nullptr;

                *ptr = newNode;
                ptr = &newNode->next;
                current = current->next;
            }
        }
        // Delete prev buckets
        for (int i = 0; i < numBuckets; i++)
        {
            Node* current = buckets[i];
            while (current != nullptr)
            {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }

        sz = hm.sz;
        numBuckets = hm.numBuckets;

        delete[] buckets;
        buckets = newBuckets;
    }
    return *this;
}


void HashMap::add(const std::string& key, const std::string& value)
{
    if (this->contains(key)) { return; }

    double loadFactor = (double) (sz+1)/numBuckets;
    if (loadFactor > 0.8)
    {
        unsigned int oldNumBuckets = numBuckets;
        numBuckets = 2*numBuckets + 1;
        
        Node** newBuckets = new Node*[numBuckets];
        for (int i = 0; i < numBuckets; i++)
        {
            newBuckets[i] = nullptr;
        }

        for (int i = 0; i < oldNumBuckets; i++)
        {
            std::string key;
            std::string val;
            Node* current = buckets[i];
            
            while (current != nullptr)
            {
                key = current->key;
                val = current->value;
                unsigned int newHashIndex = hasher(key);
                
                if (newBuckets[newHashIndex] == nullptr)
                {
                    newBuckets[newHashIndex] = new Node{key, val, nullptr};
                }
                else
                {
                    Node* newCurrent = newBuckets[newHashIndex];
                    while (newCurrent->next != nullptr)
                    {
                        newCurrent = newCurrent->next;
                    }
                    newCurrent->next = new Node{key, val, nullptr};
                }

                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] buckets;
        buckets = newBuckets;
    }

    unsigned int hashIndex = hasher(key); 

    if (buckets[hashIndex] == nullptr)
    {
        buckets[hashIndex] = new Node{key, value, nullptr};
    }
    else
    {
        Node* current = buckets[hashIndex];
        while (current->next != nullptr)
        {
            current = current->next; 
        }
        current->next = new Node{key, value, nullptr};
    }
    sz++;
}


void HashMap::remove(const std::string& key)
{
    unsigned int hashIndex = hasher(key);
    Node* current = buckets[hashIndex];
    Node* prev = nullptr;

    if (current != nullptr && current->key != key)
    {
        prev = current;
        current = current->next;
    }
    
    if (current == nullptr) { return; }
    else
    {
        if (prev == nullptr)
        {
            buckets[hashIndex] = current->next;
        }
        else
        {
            prev->next = current->next;
        }
        delete current;
        sz--;
    }
}


bool HashMap::contains(const std::string& key) const
{
    unsigned int hashIndex = hasher(key);
    Node* current = buckets[hashIndex];

    while (current != nullptr)
    {
        if (current->key == key) { return true; }
        current = current->next;
    }
    return false;
}


std::string HashMap::value(const std::string& key) const
{
    unsigned int hashIndex = hasher(key);
    Node* current = buckets[hashIndex];

    while (current != nullptr)
    {
        if (current->key == key) { return current->value; }
        current = current->next;
    }
    return "";
}


unsigned int HashMap::size() const
{
    return sz;
}


unsigned int HashMap::bucketCount() const
{
    return numBuckets;
}


double HashMap::loadFactor() const
{
    return (double) sz/numBuckets;
}


unsigned int HashMap::maxBucketSize() const
{
    unsigned int max = 0;
    
    for (int i = 0; i < numBuckets; i++)
    {
        unsigned int curr = 0;
        Node* current = buckets[i];
        while (current != nullptr)
        {
            curr++;
            current = current->next;
        }
        if (curr > max) { max = curr; }
    }
    return max;
}
