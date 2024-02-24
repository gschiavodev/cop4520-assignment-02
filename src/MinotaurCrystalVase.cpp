
// System includes
#include <iostream>

// Local includes
#include "MinotaurCrystalVase.h"
#include "MCSLock.h"
#include "main.h"

// Static class attributes
MCSLock MinotaurCrystalVase::vase_room;
std::vector<std::unique_ptr<PartyGuest02>> MinotaurCrystalVase::party_guests;
std::mutex MinotaurCrystalVase::set_lock;
std::unordered_set<size_t> MinotaurCrystalVase::guests_that_viewed_vase;
std::atomic<bool> PartyGuest02::party_is_over(false);

int MinotaurCrystalVase::main()
{

	// ..
	size_t n_guests = Problems::get_number_of_guests();

	// The guests have arrived!
	for (size_t i = 0; i < n_guests; i++)
		party_guests.emplace_back(std::make_unique<PartyGuest02>(i));

	// Wait for guests' to view the vase!
	while (MinotaurCrystalVase::guest_set_size() != n_guests) {}

	// End the party!
	std::cout << "\"Ok glad y'all liked it, now get out!\" - Minotaur" << std::endl;
	PartyGuest02::party_is_over.store(true);

	// Let the guests leave
	for (size_t i = 0; i < n_guests; i++)
	{

		// ..
		std::thread& thread = party_guests.at(i)->get_thread();

		if (thread.joinable())
			thread.join();

	}

	// ..
	return 0;

}

void MinotaurCrystalVase::guest_set_insert(size_t id)
{

	// Safe insert into guest set
	std::lock_guard<std::mutex> lock_guard(set_lock);
	guests_that_viewed_vase.insert(id);

}

size_t MinotaurCrystalVase::guest_set_size()
{

	// Safe size check of guest set
	std::lock_guard<std::mutex> lock_guard(set_lock);
	return guests_that_viewed_vase.size();

}

PartyGuest02::State::State(size_t id) : id(id)
{

}

PartyGuest02::PartyGuest02(size_t id) :

	state(std::make_unique<State>(id)),
	thread(&PartyGuest02::have_fun_at_the_party, this)

{

}

PartyGuest02::PartyGuest02(PartyGuest02&& other) noexcept :

	state(std::move(other.state)),
	thread(std::move(other.thread))

{

}

PartyGuest02::~PartyGuest02()
{

	if (thread.joinable())
		thread.join();

}

void PartyGuest02::have_fun_at_the_party()
{

	while (!party_is_over.load())
	{
		
		// Queue to enter the vase room
		MCSLock::Node lock_node;
		MinotaurCrystalVase::vase_room.lock(&lock_node);

		// Wow, what a nice vase!
		MinotaurCrystalVase::guest_set_insert(state->id);

		// Exit the vase room
		MinotaurCrystalVase::vase_room.unlock(&lock_node);

	}

}

std::thread& PartyGuest02::get_thread()
{

	// Return thread by reference
	return thread;

}
