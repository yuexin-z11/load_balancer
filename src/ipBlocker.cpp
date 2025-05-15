#include "ipBlocker.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

using namespace std;

/// \brief Convert a dotted IPv4 address string to a 32-bit integer.
///
/// Parses an address of the form "a.b.c.d" where each octet is 0–255.
///
/// \param ip The dotted-quad IPv4 string to convert.
/// \return The 32-bit integer representation: (a<<24)|(b<<16)|(c<<8)|d.
/// \throws std::invalid_argument If the input string is not a valid IPv4 address.
uint32_t ipBlocker::ipToInt(const string &ip){
    istringstream iss(ip);
    uint32_t o1, o2, o3, o4;
    char dot;
    if (!(iss >> o1 >> dot >> o2 >> dot >> o3 >> dot >> o4))
        throw invalid_argument("Bad IP format");
    return (o1 << 24) | (o2 << 16) | (o3 << 8) | o4;
}

/// \brief Convert a CIDR notation string to an inclusive IP range.
///
/// Parses a string like "192.168.0.0/24" into a start and end address.
///
/// \param cidr The CIDR block string (e.g. "10.0.0.0/8").
/// \return A pair of 32-bit integers {start, end} for the block.
/// \throws std::invalid_argument If the CIDR format is invalid.
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

/// \brief Add a CIDR block to the blocker's internal list.
///
/// Converts the CIDR string to a numeric range and stores it.
///
/// \param cidr The CIDR notation string to block.
void ipBlocker::addBlock(const string &cidr){
    range.push_back(cidrToRange(cidr));
}

/// \brief Determine if an IP address is blocked by any stored CIDR.
///
/// \param ip The dotted-quad IPv4 string to check.
/// \return True if the IP is within any blocked range; otherwise false.
bool ipBlocker::isBlocked(const string &ip) const {
    uint32_t val = ipToInt(ip);
    for(auto &r : range){
        if (val >= r.first && val <= r.second){
            return true;
        }
    }
    
    return false;
}