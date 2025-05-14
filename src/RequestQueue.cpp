// first in, first out container for holding requests that are not served
#include "RequestQueue.h"

using namespace std;

void RequestQueue::enqueue(const Request &req){
    q.push(req);
}

Request RequestQueue::dequeue() {
    Request front = q.front();
    q.pop();
    return front;
}

bool RequestQueue::empty() const {
    return q.empty();
}

size_t RequestQueue::size() const {
    return q.size();
}