#pragma once

#include <atomic>
#include <vector>

class MCSLock
{

public:

    struct Node {

        std::atomic<Node*> next;
        std::atomic<bool> locked;

        Node();

    };

    MCSLock();

    void lock(Node* current_node);
    void unlock(Node* current_node);

private:

    std::atomic<Node*> tail;

};

