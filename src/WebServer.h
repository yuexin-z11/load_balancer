// WebServer.h
#pragma once

#include "Request.h"

class WebServer {
public:
    WebServer();

    void assign(const Request &req);

    void cycle();

    bool isIdle() const;

    Request retrieveCompleted();

private:
    bool busy;
    Request current; 
};