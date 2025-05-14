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
    lb.prefill();
    lb.run(duration);

    cout << "Simulation complete after " << duration << " time cycles. \n";
}