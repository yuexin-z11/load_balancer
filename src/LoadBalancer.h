// LoadBalancer.h
#pragma once

#include <vector>
#include "WebServer.h"
#include "RequestQueue.h"

class LoadBalancer {
public:
    LoadBalancer(int initialServers, int t);

    void run(int duration);

    void prefill();

private:
    vector<WebServer> servers;
    RequestQueue queue;
    int maxTime;
    int currentCycle;

    void dispatch(); // assgin request to any idle server
    void allCycles(); // call cycle on each webserver
    void scale(); // compare queue size to server size 
    void generateArrivals(int arrivalsPerCycle);
};