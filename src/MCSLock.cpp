
// Local includes
#include "MCSLock.h"

MCSLock::MCSLock() : tail(nullptr)
{

}

MCSLock::Node::Node()
{

    // Initialize the new node
    next.store(nullptr);
    locked.store(true);

}

void MCSLock::lock(Node* new_node)
{

    // Exchange tail pointer with current node (add to end of queue)
    Node* prev_node = tail.exchange(new_node);

    // Only node in queue?
    if (prev_node != nullptr) 
    {

        // Wait for the preceeding node to unlock the new node
        prev_node->next.store(new_node);
        while (new_node->locked.load()) {}

    }

}

void MCSLock::unlock(Node* head_node)
{

    // Only node in the queue?
    if (head_node->next.load() == nullptr)
    {

        // ...
        Node* expected = head_node;

        // If no new node arrived and node is only one left in the queue then just exit
        if (tail.compare_exchange_strong(head_node, nullptr))
            return;

        // Wait for the next node to arrive
        while (head_node->next.load() == nullptr) {}

    }


	// Unlock the next node in the queue
	head_node->next.load()->locked.store(false);

}
