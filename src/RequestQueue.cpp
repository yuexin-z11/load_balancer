/// \file RequestQueue.cpp
/// \brief Implements a simple FIFO queue for Request objects.
#include "RequestQueue.h"

using namespace std;

/// \brief Enqueue a request into the back of the queue.
/// \param req The Request object to add.
void RequestQueue::enqueue(const Request &req){
    q.push(req);
}

/// \brief Dequeue the front request from the queue.
/// \return The Request that was at the front of the queue.
/// \throws std::out_of_range if the queue is empty.
Request RequestQueue::dequeue() {
    Request front = q.front();
    q.pop();
    return front;
}

/// \brief Check if the queue is empty.
/// \return True if there are no requests in the queue; otherwise false.
bool RequestQueue::empty() const {
    return q.empty();
}

/// \brief Get the number of requests currently in the queue.
/// \return The count of enqueued Request objects.
size_t RequestQueue::size() const {
    return q.size();
}