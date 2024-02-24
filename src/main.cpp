
// System includes
#include <iostream>

// Local includes
#include "main.h"
#include "MinotaurBirthdayParty.h"
#include "MinotaurCrystalVase.h"

int main()
{

	// ...
	int return_value;

	// Execute the problem to solve
	switch (Problems::get_problem_to_solve())
	{

		case Problems::Name::Minotaur_Birthday_Party:
			return_value = MinotaurBirthdayParty::main();
			break;

		case Problems::Name::Minotaur_Crystal_Vase:
			return_value = MinotaurCrystalVase::main();
			break;

		default:
			return_value = 0;
			break;

	}

	// Give user time to see output prompts
	std::cout << "\nPress any key to exit " << "\"" << Problems::to_string(Problems::get_problem_to_solve()) << "\"..." << std::endl;
	std::cin.get();

	// Exit
	return return_value;

}

std::string Problems::to_string(Problems::Name problem_name)
{

	switch (problem_name)
	{

		case Problems::Name::Minotaur_Birthday_Party:
			return std::string("Minotaur's Birthday Party");

		case Problems::Name::Minotaur_Crystal_Vase:
			return std::string("Minotaur's Crystal Vase");

		default:
			return std::string("Name not found");

	}

}

size_t Problems::get_number_of_guests()
{

	return n_guests;

}

Problems::Name Problems::get_problem_to_solve()
{

	return problem_to_solve;

}
