

// Local includes
#include "main.h"
#include "MinotaurBirthdayParty.h"
#include "MinotaurCrystalVase.h"

// Constants
constexpr Problems::Name problem_to_solve { Problems::Name::Minotaur_Birthday_Party };

int main()
{

	switch (problem_to_solve)
	{

		case Problems::Name::Minotaur_Birthday_Party:
			return MinotaurBirthdayParty::main();

		case Problems::Name::Minotaur_Crystal_Vase:
			return MinotaurCrystalVase::main();

		default:
			return 0;

	}

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
