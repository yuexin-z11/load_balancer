#include "ipBlocker.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

using namespace std;

uint32_t ipBlocker::ipToInt(const string &ip){
    istringstream iss(ip);
    uint32_t o1, o2, o3, o4;
    char dot;
    if (!(iss >> o1 >> dot >> o2 >> dot >> o3 >> dot >> o4))
        throw invalid_argument("Bad IP format");
    return (o1 << 24) | (o2 << 16) | (o3 << 8) | o4;
}

pair<uint32_t, uint32_t> ipBlocker::cidrToRange(const string &cidr){
    auto slash = cidr.find('/');
    if (slash == string::npos){
        throw invalid_argument("Bad CIDR format");
    }
    string net = cidr.substr(0, slash);
    int prefix = stoi(cidr.substr(slash+1));
    uint32_t base = ipToInt(net);
    uint32_t mask = prefix==0 ? 0 : (~uint32_t(0) << (32-prefix));
    uint32_t start = base & mask;
    uint32_t end = start | ~mask;
    return {start, end};
}

void ipBlocker::addBlock(const string &cidr){
    range.push_back(cidrToRange(cidr));
}

bool ipBlocker::isBlocked(const string &ip) const {
    uint32_t val = ipToInt(ip);
    for(auto &r : range){
        if (val >= r.first && val <= r.second){
            return true;
        }
    }
    
    return false;
}