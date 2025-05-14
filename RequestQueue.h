// RequestQueue.h
#pragma once

#include <queue>
#include "Request.h"

using namespace std;

class RequestQueue {
public:
    void enqueue(const Request &req);

    Request dequeue();

    bool empty() const;

    size_t size() const;

private:
    queue<Request> q;
}