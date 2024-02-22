

// System includes
#include <iostream>

// Local includes
#include "MinotaurBirthdayParty.h"

std::mutex MinotaurBirthdayParty::labyrinth;
std::vector<PartyGuest> MinotaurBirthdayParty::party_guests;
std::atomic<bool> MinotaurBirthdayParty::all_guests_visited_the_labyrinth(false);
bool MinotaurBirthdayParty::cupcake_is_on_plate(true);

int MinotaurBirthdayParty::main()
{

	// Reserve space for guests
	party_guests.reserve(n_guests);

	// The guests have arrived!
	for (size_t i = 0; i < n_guests; i++)
	{

		bool is_the_counter = i == 0 ? true : false;
		party_guests.emplace_back(i, is_the_counter);

	}

	// Wait for guests' announcement!
	while (!all_guests_visited_the_labyrinth.load()) {}

	// End the party!
	std::cout << "\"Ok perfect, now get out!\" - Minotaur" << std::endl;
	PartyGuest::party_is_over.store(true);

	// ..
	return 0;

}

size_t MinotaurBirthdayParty::get_number_of_guests()
{

	return n_guests;

}

void MinotaurBirthdayParty::guest_announcement() 
{

	// End the party!
	std::cout << "\"We have all visited the labyrinth at least once!\" - Guest(s)" << std::endl;
	all_guests_visited_the_labyrinth.store(true);

}

bool MinotaurBirthdayParty::is_there_a_cupcake()
{

	return cupcake_is_on_plate;

}

void MinotaurBirthdayParty::request_another_cupcake()
{

	cupcake_is_on_plate = true;

}

void MinotaurBirthdayParty::eat_the_cupcake()
{

	cupcake_is_on_plate = false;

}

std::atomic<bool> PartyGuest::party_is_over(false);

PartyGuest::State::State(size_t id, bool is_the_counter) :

	id(id),
	ate_a_cupcake(false),
	is_the_counter(is_the_counter),
	count(0)

{

}

PartyGuest::PartyGuest(size_t id, bool is_the_counter) :

	state(std::make_shared<State>(id, is_the_counter)),
	thread(&PartyGuest::have_fun_at_the_party, this)

{

}

PartyGuest::PartyGuest(PartyGuest&& other) noexcept :

	state(other.state),
	thread(std::move(other.thread))

{

}

PartyGuest::~PartyGuest()
{

	if (thread.joinable())
		thread.join();

}

void PartyGuest::count_party_guest()
{

	state->count++;

}

void PartyGuest::have_fun_at_the_party()
{

	while (!party_is_over.load()) 
	{

		// Guest has entered the labyrinth
		MinotaurBirthdayParty::labyrinth.lock();

		// If the guest has not had a cupcake and there is one, eat it!
		if (!state->ate_a_cupcake && MinotaurBirthdayParty::is_there_a_cupcake())
		{

			MinotaurBirthdayParty::eat_the_cupcake();
			state->ate_a_cupcake = true;

		}

		// If there is no cupcake and you are the counter, count another guest,
		// and request another cupcake.
		if (state->is_the_counter && !MinotaurBirthdayParty::is_there_a_cupcake())
		{

			// Request another cupcake and count another party guest.
			MinotaurBirthdayParty::request_another_cupcake();
			count_party_guest();

			// If the guest counting, counts that all guests ate, 
			// announce that all guest entered the labyrinth at least once
			if (state->count == MinotaurBirthdayParty::get_number_of_guests())
			{

				MinotaurBirthdayParty::guest_announcement();

			}

		}

		// Unlock and leave the labyrinth
		MinotaurBirthdayParty::labyrinth.unlock();

	}

}

std::thread& PartyGuest::get_thread() 
{
	
	// Return thread by reference
	return thread;

}
