# Load Balancer Simulation

A discrete-event simulation of a load-balancing system, built in C++.

## Overview

This project models a simplified web-request load-balancer architecture:

* **Request**: source/destination IP, processing time, type (streaming or processing).
* **RequestQueue**: FIFO buffer of pending requests.
* **WebServer**: processes one request at a time; tracks busy/idle state.
* **IpBlocker**: firewall that blocks requests based on CIDR ranges.
* **LoadBalancer**: orchestrates request arrivals, dispatch, server cycles, dynamic scaling.

## Features

* Initial queue seed of `20 × initialServers` requests.
* Randomized arrival model (Bernoulli trials with configurable slots).
* Dynamic scaling thresholds (`upThresh` and `downThresh`).
* IP-range blocking to drop unwanted traffic.
* Console-based debug output showing ticks, dispatch, scaling events, and drops.

## Prerequisites

* C++17 compiler (e.g. `g++` or `clang++`)
* [Doxygen](http://www.doxygen.nl/) (optional, for generating API docs)

## Directory Structure

```
project/
├── src/                   # Source code (.cpp, .h)
├── obj/                   # Compiled object files (generated)
├── bin/                   # Executable (generated)
├── docs/                  # Doxygen output (generated)
│   └── html/
├── Makefile               # Build rules
└── README.md              # This file
```

## Build Instructions

```bash
# From the project root:
make        # compiles into bin/loadbalancer
```

Or, manually:

```bash
g++ -std=c++17 -Wall -Wextra src/*.cpp -o bin/loadbalancer
```

## Running the Simulation

```bash
# Launch the program
./bin/loadbalancer

# Sample input:
Enter initial number of web servers: 3
Enter max processing time: 5
Enter total simulation duration: 50
```

The simulation will print per-tick stats, dispatch events, scaling actions, and dropped requests.

## Generating API Documentation

```bash
# Ensure Doxygen and (optionally) Graphviz are installed
# Customize the Doxyfile in the project root, then run:
doxygen Doxyfile
# Browse docs/html/index.html in your browser.
```

## Metrics & Extensions

* Extend `LoadBalancer` to record throughput, average wait time, peak queue length, and server utilization.
* Adjust arrival probability, slots range, and scaling thresholds to experiment with different traffic patterns.
