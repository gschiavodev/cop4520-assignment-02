

// System includes
#include <iostream>

// Local includes
#include "MinotaurBirthdayParty.h"

int MinotaurBirthdayParty::main()
{

	// ..


	// ..
	return 0;

}

PartyGuest::PartyGuest(size_t id)
{

	PartyGuest(id, false);

}

PartyGuest::PartyGuest(size_t id, bool is_counter)
{

	this->id = id;
	this->part_is_over = false;
	this->ate_cupcake = false;
	this->is_the_counter = is_counter;
	this->count = 0;

	have_fun_at_the_party();

}

void PartyGuest::count_party_guest()
{

	if (is_the_counter)
		count++;
	else
		std::cerr << "Guest is an imposter!" << std::endl;

}


void PartyGuest::have_fun_at_the_party()
{

	while (!part_is_over) 
	{

		// ..


	}

}