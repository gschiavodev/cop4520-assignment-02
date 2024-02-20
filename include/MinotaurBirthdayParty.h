#pragma once

class MinotaurBirthdayParty
{

public:

	static int main();

};

class PartyGuest
{

private:

	static size_t id;
	bool part_is_over;
	bool ate_cupcake;
	bool is_the_counter;
	size_t count;

public:

	PartyGuest(size_t id);
	PartyGuest(size_t id, bool is_counter);

	void count_party_guest();
	void have_fun_at_the_party();

};
