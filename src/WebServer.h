// WebServer.h
#pragma once

#include "Request.h"

/// \brief Simulates a basic web server handling requests.
class WebServer {
public:
    /// \brief Constructs a new WebServer object in an idle state.
    WebServer();

    /// \brief Assigns a new request to the server for processing.
    /// \param req The request to assign to the server.
    void assign(const Request &req);

    /// \brief Simulates a processing cycle on the current request.
    void cycle();

    /// \brief Checks whether the server is currently idle.
    /// \return true if the server is idle, false otherwise.
    bool isIdle() const;

    /// \brief Retrieves a completed request after processing.
    /// \return The request that was completed.
    Request retrieveCompleted();

private:
    bool busy;        ///< Indicates whether the server is currently processing a request.
    Request current;  ///< The current request being processed by the server.
};