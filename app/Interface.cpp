#include "Interface.hpp"


namespace
{
    void invalid() { std::cout << "INVALID" << std::endl; }
}


Interface::Interface()
    : debug{false}
{
}


Interface::Interface(const Interface& in)
    : hm{in.hm}, debug{in.debug}
{
}


Interface::~Interface()
{
}


Interface& Interface::operator=(const Interface& in)
{
    if (this != &in)
    {
        hm = in.hm;
        debug = in.debug;
    }
    return *this;
}


void Interface::create(const std::string& user, const std::string& pass)
{
    if (!hm.contains(user))
    {
        hm.add(user, pass);
        std::cout << "CREATED" << std::endl;
    }
    else { std::cout << "EXISTS" << std::endl; }
}


void Interface::login(const std::string& user, const std::string& pass)
{
    if (hm.contains(user) && pass == hm.value(user))
    { std::cout << "SUCCEEDED" << std::endl; }
    else { std::cout << "FAILED" << std::endl; }
}


void Interface::remove(const std::string& user)
{
    if (hm.contains(user))
    {
        hm.remove(user);
        std::cout << "REMOVED" << std::endl;
    }
    else { std::cout << "NONEXISTENT" << std::endl; }
}


void Interface::clear()
{
    HashMap newHm;
    hm = newHm;
    std::cout << "CLEARED" << std::endl;
}


void Interface::debugOn()
{
    if (!debug)
    {
        debug = true;
        std::cout << "ON NOW" << std::endl;
    }
    else { std::cout << "ON ALREADY" << std::endl; }
}


void Interface::debugOff()
{
    if (debug)
    {
        debug = false;
        std::cout << "OFF NOW" << std::endl;
    }
    else { std::cout << "OFF ALREADY" << std::endl; }
}


void Interface::loginCount() const
{
    if (debug) { std::cout << hm.size() << std::endl; }
    else { invalid(); }
}


void Interface::bucketCount() const
{
    if (debug) { std::cout << hm.bucketCount() << std::endl; }
    else { invalid(); }
}


void Interface::loadFactor() const
{
    if (debug) { std::cout << hm.loadFactor() << std::endl; }
    else { invalid(); }
}


void Interface::maxBucketSize() const
{
    if (debug) { std::cout << hm.maxBucketSize() << std::endl; }
    else { invalid(); }
}


void Interface::run()
{
    std::string line;

    while (getline(std::cin, line))
    {
        std::istringstream iss(line);
        std::string cmd1;
        std::string cmd2;
        std::string cmd3;
        iss >> cmd1 >> cmd2 >> cmd3;

        if (cmd1 == "CREATE")
        {
            if (cmd2 == "") { invalid(); }
            else { create(cmd2, cmd3); }
        }
        else if (cmd1 == "LOGIN")
        {
            if (cmd2 == "") { invalid(); }
            else
            {
                if (cmd2 == "COUNT") { loginCount(); }
                else { login(cmd2, cmd3); }
            }
        }
        else if (cmd1 == "REMOVE")
        {
            if (cmd2 == "") { invalid(); }
            else { remove(cmd2); }
        }
        else if (cmd1 == "CLEAR")
        {
            if (cmd2 != "") { invalid(); }
            else { clear(); }
        }
        else if (cmd1 == "DEBUG")
        {
            if (cmd2 == "ON") { debugOn(); }
            else if (cmd2 == "OFF") { debugOff(); }
            else { invalid(); }
        }
        else if (cmd1 == "BUCKET")
        {
            if (cmd2 == "COUNT") { bucketCount(); }
            else { invalid(); }
        }
        else if (cmd1 == "LOAD")
        {
            if (cmd2 == "FACTOR") { loadFactor(); }
            else { invalid(); } 
        }
        else if (cmd1 == "MAX")
        {
            if (cmd2 == "BUCKET" && cmd3 == "SIZE") { maxBucketSize(); }
            else { invalid(); }
        }
        else if (cmd1 == "QUIT")
        {
            std::cout << "GOODBYE" << std::endl;
            break;
        }
        else { invalid(); }
    }
}
