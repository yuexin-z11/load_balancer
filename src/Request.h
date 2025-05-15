// Request.h
#pragma once

#include <string>
using namespace std;

/// \struct Request
/// \brief Represents a single web request for load balancing simulation.
///
/// Stores the source and destination IP addresses, remaining processing time,
/// and a job type flag ('S' or 'P').
struct Request {
    string ipIn;         ///< Source IPv4 address (dotted-quad)
    string ipOut;        ///< Destination IPv4 address
    int remainingTime;   ///< Processing time units remaining
    char type;           ///< Request type: 'S' = streaming, 'P' = processing
};

/// \brief Generate a randomized Request instance.
/// \param maxProcessTime Maximum processing time (inclusive) for the new request.
/// \return A Request with randomized ipIn, ipOut, remainingTime, and type.
Request makeRandomRequest(int maxProcessTime);