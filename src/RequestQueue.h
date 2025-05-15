/// \file RequestQueue.h
/// \brief Defines a FIFO queue for managing Request objects.
#pragma once

#include <queue>
#include "Request.h"

using namespace std;

/// \class RequestQueue
/// \brief A simple first-in, first-out queue for Request instances.
///
/// Provides enqueue and dequeue operations, along with
/// methods to inspect queue state and size.
class RequestQueue {
public:
    /// \brief Add a Request to the back of the queue.
    /// \param req The Request object to enqueue.
    void enqueue(const Request &req);

    /// \brief Remove and return the front Request from the queue.
    /// \return The Request at the front of the queue.
    /// \throws std::out_of_range if the queue is empty.
    Request dequeue();

    /// \brief Check whether the queue has no elements.
    /// \return True if the queue is empty; otherwise false.
    bool empty() const;

    /// \brief Get the current number of Requests in the queue.
    /// \return The number of enqueued Request objects.
    size_t size() const;

private:
    queue<Request> q;  ///< Underlying container storing queued requests.
};