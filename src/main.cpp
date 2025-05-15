/// \file main.cpp
/// \brief Entry point for the load balancer simulation program.
///
/// Prompts the user for configuration parameters, sets up the load balancer,
/// applies IP blocking rules, prefills the request queue, and runs the simulation.

#include <iostream>
#include "LoadBalancer.h"

using namespace std; 

/// \brief Program entry point.
///
/// Prompts for the initial number of servers, maximum processing time per request,
/// and total simulation duration in time units. Then it constructs a LoadBalancer,
/// configures firewall CIDR blocks, prefills the queue, and runs the simulation.
///
/// \return Exit code (0 for success).
int main() {
    int initialServers;    ///< Number of servers to start with.
    int maxProcessTime;    ///< Maximum processing time for any request.
    int duration;          ///< Total simulation duration in time units.

    // get user inputs
    cout << "Enter inital number of web servers: ";
    cin >> initialServers;

    cout << "Enter maximum processing time for any request: ";
    cin >> maxProcessTime;

    cout << "Enter total simulation duration (in time units): ";
    cin >> duration;

    // construct the loadbalancer
    LoadBalancer lb(initialServers, maxProcessTime);

    // run the simulation for the specified time
    lb.blockCidr("10.0.0.0/8");         ///< Block private 10.x.x.x addresses.
    lb.blockCidr("203.0.113.0/24");     ///< Block example-test addresses.
    
    // Prefill queue and run the simulation
    lb.prefill();
    lb.run(duration);

    cout << "Simulation complete after " << duration << " time cycles. \n";
}