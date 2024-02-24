

// System includes
#include <iostream>

// Local includes
#include "MinotaurBirthdayParty.h"
#include "main.h"

// Static class attributes
std::mutex MinotaurBirthdayParty::labyrinth;
std::vector<std::unique_ptr<PartyGuest01>> MinotaurBirthdayParty::party_guests;
std::atomic<bool> MinotaurBirthdayParty::all_guests_visited_the_labyrinth(false);
bool MinotaurBirthdayParty::cupcake_is_on_plate(true);
std::atomic<bool> PartyGuest01::party_is_over(false);

int MinotaurBirthdayParty::main()
{

	// ..
	size_t n_guests = Problems::get_number_of_guests();

	// The guests have arrived!
	for (size_t i = 0; i < n_guests; i++)
	{

		bool is_the_counter = i == 0 ? true : false;
		party_guests.emplace_back(std::make_unique<PartyGuest01>(i, is_the_counter));

	}

	// Wait for guests' announcement!
	while (!all_guests_visited_the_labyrinth.load()) {}

	// End the party!
	std::cout << "\"Ok perfect, now get out!\" - Minotaur" << std::endl;
	PartyGuest01::party_is_over.store(true);

	// Let the guests leave
	for (size_t i = 0; i < n_guests; i++)
	{

		// ..
		std::thread& thread = party_guests.at(i)->get_thread();

		if (thread.joinable())
			thread.detach();
		
	}

	// ..
	return 0;

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

PartyGuest01::State::State(size_t id, bool is_the_counter) :

	id(id),
	ate_a_cupcake(false),
	is_the_counter(is_the_counter),
	count(0)

{

}

PartyGuest01::PartyGuest01(size_t id, bool is_the_counter) :

	state(std::make_unique<State>(id, is_the_counter)),
	thread(&PartyGuest01::have_fun_at_the_party, this)

{

}

PartyGuest01::PartyGuest01(PartyGuest01&& other) noexcept :

	state(std::move(other.state)),
	thread(std::move(other.thread))

{

}

PartyGuest01::~PartyGuest01()
{

	if (thread.joinable())
		thread.join();

}

void PartyGuest01::count_party_guest()
{

	state->count++;

}

void PartyGuest01::have_fun_at_the_party()
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
			if (state->count == Problems::get_number_of_guests())
				MinotaurBirthdayParty::guest_announcement();

		}

		// Unlock and leave the labyrinth
		MinotaurBirthdayParty::labyrinth.unlock();

	}

}

std::thread& PartyGuest01::get_thread()
{
	
	// Return thread by reference
	return thread;

}
