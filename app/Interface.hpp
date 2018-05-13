#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <sstream>
#include "HashMap.hpp"


class Interface
{
public:
    Interface();

    Interface(const Interface& in);

    ~Interface();

    Interface& operator=(const Interface& in);

    void create(const std::string& user, const std::string& pass);

    void login(const std::string& user, const std::string& pass);

    void remove(const std::string& user);

    void clear();

    void debugOn();

    void debugOff();

    void loginCount() const;

    void bucketCount() const;

    void loadFactor() const;

    void maxBucketSize() const;

    void run();

private:
    HashMap hm;
    bool debug;
};

#endif
