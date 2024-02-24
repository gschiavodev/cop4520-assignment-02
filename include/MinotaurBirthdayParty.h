#pragma once

// System includes
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
#include <memory>

// Forward declarations
class MinotaurBirthdayParty;
class PartyGuest01;

class MinotaurBirthdayParty
{

public:
	static std::mutex labyrinth;

private:
	static std::vector<std::unique_ptr<PartyGuest01>> party_guests;
	static std::atomic<bool> all_guests_visited_the_labyrinth;
	static bool cupcake_is_on_plate;

public:

	static int main();

	static void guest_announcement();

	static bool is_there_a_cupcake();
	static void request_another_cupcake();
	static void eat_the_cupcake();

};

class PartyGuest01
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

	std::unique_ptr<State> state;
	std::thread thread;

	void count_party_guest();
	void have_fun_at_the_party();

public:

	PartyGuest01(size_t id, bool is_the_counter);
	PartyGuest01(PartyGuest01&& other) noexcept;
	~PartyGuest01();

	std::thread& get_thread();

};
