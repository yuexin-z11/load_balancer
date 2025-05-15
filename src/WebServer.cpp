/// \file WebServer.cpp
/// \brief Implements the WebServer class, which processes one Request at a time.
#include "WebServer.h"

using namespace std;

/// \brief Default constructor. Initializes the server to an idle state.
WebServer::WebServer() : busy(false) {}

/// \brief Assign a new request to this server.
/// \param req The Request object to process.
///
/// Marks the server as busy and stores the request as current.
void WebServer::assign(const Request &req){
    current = req;
    busy = true;
}

/// \brief Advance the server by one time cycle.
///
/// If the server is busy, decrements the remainingTime of the current request.
/// When remainingTime reaches zero or below, marks the server as idle.
void WebServer::cycle() {
    if (!busy) return;
    current.remainingTime--;
    if (current.remainingTime <= 0) busy = false;
}

/// \brief Check whether the server is currently idle.
/// \return True if the server is not processing a request; otherwise false.
bool WebServer::isIdle() const {
    return !busy;
}

/// \brief Retrieve the completed request after processing.
/// \return The Request that has just finished processing.
///
/// The caller should only invoke this if the server was busy and has just
/// completed processing (i.e., isIdle() returned false before the last cycle).
Request WebServer::retrieveCompleted() {
    return current;
}