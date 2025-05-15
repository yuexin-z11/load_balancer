// generate random ip address with requests and random running time 
// how often do you want the request to come 

#include "Request.h"
#include <random>
#include <sstream>
#include <array>

using namespace std;

/// \brief Static random engine for IP and time distributions.
static mt19937 rng{ random_device{}() };

/// \brief Generate a random IPv4 address in dotted-quad notation.
///
/// Uses a uniform distribution over 0…255 for each octet.
/// \return A string of the form "a.b.c.d" with each octet randomized.
static string generateRandomIP() {
    uniform_int_distribution<int> distOctat(0, 255);
    ostringstream out;
    out << distOctat(rng) << '.'
        << distOctat(rng) << '.'
        << distOctat(rng) << '.'
        << distOctat(rng);
    return out.str();
}

/// \brief Create a Request with randomized fields.
///
/// \param maxProcessTime Upper bound (inclusive) for the request's processing time.
/// \return A Request struct populated with random source IP, fixed destination IP,
///         random remainingTime, and random type ('S' or 'P').
Request makeRandomRequest(int maxProcessTime) {
    uniform_int_distribution<int> distTime(1, maxProcessTime);
    // 80% chance for 'S' (streaming), otherwise 'P' (processing)
    bernoulli_distribution distType(0.8);

    Request req;
    req.ipIn = generateRandomIP();
    req.ipOut = "192.168.0.1"; ///< Fixed destination for demonstration
    req.remainingTime = distTime(rng);
    req.type = distType(rng) ? 'S' : 'P';
    return req;
}