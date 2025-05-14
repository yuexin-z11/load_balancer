// Request.h
#pragma once

#include <string>
using namespace std;

struct Request {
    string ipIn; // where the ip address come from 
    string ipOut; // where the address is heading to 
    int remainingTime; // how much time does it need
    char type; // the two job catagories
};

Request makeRandomRequest(int maxProcessTime);