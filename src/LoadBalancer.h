// LoadBalancer.h
#pragma once

#include <vector>
#include "WebServer.h"
#include "RequestQueue.h"
#include "ipBlocker.h"

/// \class LoadBalancer
/// \brief Simulates a load balancer that dispatches web requests across servers,
///        auto-scales server count, and filters requests via CIDR-based blocking.
class LoadBalancer {
public:
    /// \brief Constructs a LoadBalancer with a starting server pool and max request time.
    /// \param initialServers Number of servers to initialize.
    /// \param t Maximum processing time (in cycles) for randomly generated requests.
    LoadBalancer(int initialServers, int t);

    /// \brief Runs the load balancer simulation for a given number of cycles.
    /// \param duration Number of simulation cycles to execute.
    void run(int duration);

    /// \brief Prefills the request queue based on the initial server count.
    ///        Enqueues 20 requests per server using random parameters.
    void prefill();

    /// \brief Adds a CIDR block to the firewall to drop matching source IPs.
    /// \param cidr The CIDR notation (e.g., "192.168.0.0/24") to block.
    void blockCidr(const std::string &cidr);

private:
    vector<WebServer> servers;        ///< Active pool of web servers.
    RequestQueue queue;               ///< Queue of pending requests.
    int maxTime;                      ///< Max processing time for random requests.
    int currentCycle;                 ///< Current simulation cycle.
    ipBlocker firewall;               ///< IP blocker for filtering incoming requests.

    /// \brief Dispatches queued requests to idle servers.
    void dispatch(); 

    /// \brief Advances all servers by one cycle (processing time decrement).
    void allCycles(); 

    /// \brief Auto-scales servers based on queue length relative to server count.
    void scale();  

    /// \brief Generates new random arrivals and enqueues them if not blocked.
    /// \param arrivalsPerCycle Max processing time for each generated request.  
    void generateArrivals(int arrivalsPerCycle);
};