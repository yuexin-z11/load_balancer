// ipBlocker.h

#pragma once

#include <string>
#include <vector>
#include <cstdint>

using namespace std;

class ipBlocker{
public:
    void addBlock(const string &cidr);

    bool isBlocked(const string &ip) const; // check is the ip address is in blocked range

private:
    vector<pair<uint32_t, uint32_t>> range;

    static uint32_t ipToInt(const string &ip);

    static pair<uint32_t, uint32_t>cidrToRange(const string &cidr);
};