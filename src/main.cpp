// ask for input how many servers you want
// how many requests do you want 

#include <iostream>
#include "LoadBalancer.h"

using namespace std; 

int main() {
    int initialServers;
    int maxProcessTime;
    int duration;

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
    lb.blockCidr("10.0.0.0/8");
    lb.blockCidr("203.0.113.0/24");
    
    lb.prefill();
    lb.run(duration);

    cout << "Simulation complete after " << duration << " time cycles. \n";
}