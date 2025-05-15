// ipBlocker.h

#pragma once

#include <string>
#include <vector>
#include <cstdint>

using namespace std;

/// \class ipBlocker
/// \brief Manages CIDR-based IP blocking rules and checks IPs against them.
///
/// Stores a list of IP ranges (in numeric form) derived from CIDR strings
/// and provides methods to add new blocks and test if an IP is blocked.
class ipBlocker{
public:
    /// \brief Add a CIDR block to the internal list of blocked IP ranges.
    /// \param cidr The CIDR notation string representing the block (e.g., "192.168.0.0/24").
    void addBlock(const string &cidr);

    /// \brief Check whether a given IP address is blocked.
    /// \param ip A dotted-quad IPv4 address string to test (e.g., "10.0.0.1").
    /// \return True if the IP lies within any previously added CIDR block; otherwise false.
    bool isBlocked(const string &ip) const; // check is the ip address is in blocked range

private:
    vector<pair<uint32_t, uint32_t>> range; ///< Stored start/end IP ranges.

    /// \brief Convert a dotted IPv4 string into a 32-bit integer.
    /// \param ip The IPv4 address string "a.b.c.d" to convert.
    /// \return The 32-bit integer representation: (a<<24)|(b<<16)|(c<<8)|d.
    /// \throws std::invalid_argument If the IP format is invalid.
    static uint32_t ipToInt(const string &ip);

    /// \brief Convert a CIDR notation string to an inclusive IP address range.
    /// \param cidr The CIDR block string (e.g., "10.0.0.0/8").
    /// \return A pair {start, end} of 32-bit integers for the block range.
    /// \throws std::invalid_argument If the CIDR format is invalid.
    static pair<uint32_t, uint32_t>cidrToRange(const string &cidr);
};