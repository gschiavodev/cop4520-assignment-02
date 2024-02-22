#pragma once

// System includes
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>

class PartyGuest;

class MinotaurBirthdayParty
{

public:
	static std::mutex labyrinth;

private:
	static constexpr size_t n_guests { 20 };
	static std::vector<PartyGuest> party_guests;
	static std::atomic<bool> all_guests_visited_the_labyrinth;
	static bool cupcake_is_on_plate;

public:

	static int main();

	static size_t get_number_of_guests();
	static void guest_announcement();

	static bool is_there_a_cupcake();
	static void request_another_cupcake();
	static void eat_the_cupcake();

};

class PartyGuest
{

public:
	static std::atomic<bool> party_is_over;

private:

	struct State
	{

		size_t id;
		bool ate_a_cupcake;
		bool is_the_counter;
		size_t count;

		State(size_t id, bool is_the_counter);

	};

	std::shared_ptr<State> state;
	std::thread thread;

	void count_party_guest();
	void have_fun_at_the_party();

public:

	PartyGuest(size_t id, bool is_the_counter);
	PartyGuest(PartyGuest&& other) noexcept;
	~PartyGuest();

	std::thread& get_thread();

};
