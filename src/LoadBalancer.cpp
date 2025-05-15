// LoadBalancer.cpp
#include "LoadBalancer.h"
#include "Request.h"
#include "ipBlocker.h"
#include <algorithm>
#include <iostream>
#include <random>

using namespace std;

/// \brief Construct a LoadBalancer with an initial number of servers and a max request time.
/// \param initialServers Number of servers to start with.
/// \param t Maximum processing time for randomly generated requests.
LoadBalancer::LoadBalancer(int initialServers, int t)
     : servers(initialServers)
     , queue()
     , maxTime(t)
     , currentCycle(0)
     , firewall(){};

/// \brief Add a CIDR block to the load balancer's firewall.
/// \param cidr The CIDR notation string to block (e.g., "192.168.1.0/24").
void LoadBalancer::blockCidr(const string &cidr){
    firewall.addBlock(cidr);
}

/// \brief Run the load balancer simulation for a set number of cycles.
///
/// In each cycle, prints status, generates random arrivals, dispatches
/// requests to idle servers, advances all servers one cycle, and scales capacity.
/// \param duration Number of cycles (time units) to simulate.
void LoadBalancer::run(int duration) {
    for (currentCycle = 0; currentCycle < duration; currentCycle++) {
        static thread_local mt19937 rng{random_device{}()};
        uniform_int_distribution<int> randomSlots(1, 30);

        if (currentCycle % 100 == 0){
            cout << "Cycle " << currentCycle << "\n";
            cout << "Queue size: " << queue.size() << "\n";
        }
        
        int arrivalsPerCycle = randomSlots(rng);
        generateArrivals(arrivalsPerCycle);
        dispatch();
        allCycles();
        scale();
    }
}

/// \brief Prefill the request queue based on current server count.
///
/// Enqueues 20 requests per server with random parameters.
void LoadBalancer::prefill() {
    int initialCount = static_cast<int>(servers.size()) * 20;
    for (int i = 0; i < initialCount; i++) {
        queue.enqueue(makeRandomRequest(maxTime));
    }
    cout << "Prefilled queue with " << initialCount 
              << " requests (" << servers.size() 
              << " servers × 20)." << endl;
    cout << "\n";
}

/// \brief Generate and enqueue new requests for this cycle.
///
/// Each server slot has a 10% chance of generating a request.
/// Blocked source IPs are dropped.
/// \param arrivalsPerCycle Maximum processing time for each new request.
void LoadBalancer::generateArrivals(int arrivalsPerCycle) {
    int slots = servers.size();
    bernoulli_distribution arrive(0.1); 
    static thread_local std::mt19937 rng{std::random_device{}()};
    for (int i = 0; i < slots; ++i) {
        if (arrive(rng)) {
            queue.enqueue(makeRandomRequest(arrivalsPerCycle));
            auto req = makeRandomRequest(arrivalsPerCycle);
            if (firewall.isBlocked(req.ipIn)){
                cout << "  [Dropped request from blocked IP " << req.ipIn;
            }
        }
    }
}

/// \brief Dispatch queued requests to idle servers.
///
/// Iterates servers and assigns the next request to each idle server if available.
void LoadBalancer::dispatch() {
    for(auto &srv : servers){
        if (srv.isIdle() && !queue.empty()){
            Request r = queue.dequeue();
            srv.assign(r);
            // cout << "  → Dispatched request ("
            //           << r.ipIn << " → " << r.ipOut 
            //           << ", time=" << r.remainingTime 
            //           << ", type=" << r.type 
            //           << ") to server #" 
            //           << (&srv - &servers[0])  // index
            //           << "\n";
        }
    }
}

/// \brief Advance all servers by one time cycle.
///
/// Decrements remaining time on active requests and marks servers idle when done.
void LoadBalancer::allCycles() {
    for(auto &srv : servers) {
        srv.cycle();
        bool wasB = !srv.isIdle();
        srv.cycle();
        if (wasB && srv.isIdle()){
            totalProcessed ++;
        }
    }
}

/// \brief Auto-scale the number of servers based on queue length.
///
/// Scales up if queue > 5× servers, scales down if queue < 0.2× servers (min 1 server).
void LoadBalancer::scale() {
    const size_t q_size = queue.size();
    const size_t n = servers.size();
    const double upThresh = 5.0, downThresh = 0.2;

    if (q_size > n * upThresh) {
        servers.emplace_back();
        totalScaleUps++;
        cout << "  ** Scaling UP: queue ("<< q_size <<") > " 
             << n << " * " << upThresh 
             << " → now " << servers.size() << " servers\n";
    }
    else if (n > 1 && q_size < n * downThresh) {
        servers.pop_back();
        totalScaleDowns++;
        cout << "  ** Scaling DOWN: queue ("<< q_size <<") < " 
             << n << " * " << downThresh 
             << " → now " << servers.size() << " servers\n";
    }
}