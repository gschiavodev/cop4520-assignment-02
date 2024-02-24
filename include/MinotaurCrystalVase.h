#pragma once

// System includes
#include <unordered_set>
#include <vector>
#include <atomic>
#include <mutex>
#include <thread>
#include <memory>

// Local includes
#include "MCSLock.h"

// Forward declarations
class MinotaurBirthdayParty;
class PartyGuest02;

class MinotaurCrystalVase
{

public:

	static MCSLock vase_room;

private:

	static std::vector<std::unique_ptr<PartyGuest02>> party_guests;

	static std::mutex set_lock;
	static std::unordered_set<size_t> guests_that_viewed_vase;

	static size_t guest_set_size();

public:

	static int main();

	static void guest_set_insert(size_t id);
	
};

class PartyGuest02
{

public:
	static std::atomic<bool> party_is_over;

private:

	struct State
	{

		size_t id;

		State(size_t id);

	};

	std::unique_ptr<State> state;
	std::thread thread;

	void have_fun_at_the_party();

public:

	PartyGuest02(size_t id);
	PartyGuest02(PartyGuest02&& other) noexcept;
	~PartyGuest02();

	std::thread& get_thread();

};
