// process one request at a time taking the time into consideration
#include "WebServer.h"

using namespace std;

WebServer::WebServer() : busy(false) {}

void WebServer::assign(const Request &req){
    current = req;
    busy = true;
}

void WebServer::cycle() {
    if (!busy) return;
    current.remainingTime--;
    if (current.remainingTime <= 0) busy = false;
}

bool WebServer::isIdle() const {
    return !busy;
}

Request WebServer::retrieveCompleted() {
    return current;
}