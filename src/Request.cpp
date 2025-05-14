// generate random ip address with requests and random running time 
// how often do you want the request to come 

#include "Request.h"
#include <random>
#include <sstream>
#include <array>

using namespace std;

// generate random IP address
static mt19937 rng{ random_device{}() };

static string generateRandomIP() {
    uniform_int_distribution<int> distOctat(0, 255);
    ostringstream out;
    out << distOctat(rng) << '.'
        << distOctat(rng) << '.'
        << distOctat(rng) << '.'
        << distOctat(rng);
    return out.str();
}

Request makeRandomRequest(int maxProcessTime) {
    uniform_int_distribution<int> distTime(1, maxProcessTime);
    bernoulli_distribution distType(0.8);

    Request req;
    req.ipIn = generateRandomIP();
    req.ipOut = "192.168.0.1";
    req.remainingTime = distTime(rng);
    req.type = distType(rng) ? 'S' : 'P';
    return req;
}