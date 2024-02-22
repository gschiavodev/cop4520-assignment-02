
// System includes
#include <iostream>

// Local includes
#include "main.h"
#include "MinotaurBirthdayParty.h"
#include "MinotaurCrystalVase.h"

// Constants
constexpr Problems::Name problem_to_solve { Problems::Name::Minotaur_Birthday_Party };

int main()
{

	// ...
	int return_value;

	// Execute the problem to solve
	switch (problem_to_solve)
	{

		case Problems::Name::Minotaur_Birthday_Party:
			return_value = MinotaurBirthdayParty::main();

		case Problems::Name::Minotaur_Crystal_Vase:
			return_value = MinotaurCrystalVase::main();

		default:
			return_value = 0;

	}

	// Give user time to see output prompts
	std::cout << "\nPress any key to exit " << "\"" << Problems::to_string(problem_to_solve) << "\"..." << std::endl;
	std::cin.get();

	// Exit
	return return_value;

}

std::string Problems::to_string(Problems::Name problem_name)
{

	switch (problem_to_solve)
	{

		case Problems::Name::Minotaur_Birthday_Party:
			return std::string("Minotaur's Birthday Party");

		case Problems::Name::Minotaur_Crystal_Vase:
			return std::string("Minotaur's Crystal Vase");

		default:
			return std::string("Name not found");

	}

}
