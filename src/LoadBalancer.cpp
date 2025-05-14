// LoadBalancer.cpp
#include "LoadBalancer.h"
#include "Request.h"
#include "ipBlocker.h"
#include <algorithm>
#include <iostream>
#include <random>

using namespace std;

LoadBalancer::LoadBalancer(int initialServers, int t)
     : servers(initialServers)
     , queue()
     , maxTime(t)
     , currentCycle(0)
     , firewall(){};

void LoadBalancer::blockCidr(const string &cidr){
    firewall.addBlock(cidr);
}

void LoadBalancer::run(int duration) {
    for (currentCycle = 0; currentCycle < duration; currentCycle++) {
        static thread_local mt19937 rng{random_device{}()};
        uniform_int_distribution<int> randomSlots(1, 30);

        cout << "Cycle " << currentCycle << "\n";
        cout << "Queue size: " << queue.size() << "\n";

        int arrivalsPerCycle = randomSlots(rng);
        generateArrivals(arrivalsPerCycle);
        dispatch();
        allCycles();
        scale();
    }
}

void LoadBalancer::prefill() {
    int initialCount = static_cast<int>(servers.size()) * 20;
    for (int i = 0; i < initialCount; i++) {
        queue.enqueue(makeRandomRequest(maxTime));
    }
    cout << "Prefilled queue with " << initialCount 
              << " requests (" << servers.size() 
              << " servers × 20)." << endl;
}

void LoadBalancer::generateArrivals(int arrivalsPerCycle) {
    int slots = servers.size();
    bernoulli_distribution arrive(0.1); 
    static thread_local std::mt19937 rng{std::random_device{}()};
    for (int i = 0; i < slots; ++i) {
        if (arrive(rng)) {
            queue.enqueue(makeRandomRequest(arrivalsPerCycle));
            auto req = makeRandomRequest(arrivalsPerCycle);
            if (firewall.isBlocked(req.ipIn)){
                cout << "  [Dropped request from blocked IP " << req.ipIn << "]\n";
            }
        }
    }
}

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

void LoadBalancer::allCycles() {
    for(auto &srv : servers) srv.cycle();
}

void LoadBalancer::scale() {
    const size_t q_size = queue.size();
    const size_t n = servers.size();
    const double upThresh = 5.0, downThresh = 0.2;

    if (q_size > n * upThresh) {
        servers.emplace_back();
        std::cout << "  ** Scaling UP: queue ("<< q_size <<") > " 
                  << n << " * " << upThresh 
                  << " → now " << servers.size() << " servers\n";
    }
    else if (n > 1 && q_size < n * downThresh) {
        servers.pop_back();
        std::cout << "  ** Scaling DOWN: queue ("<< q_size <<") < " 
                  << n << " * " << downThresh 
                  << " → now " << servers.size() << " servers\n";
    }
}