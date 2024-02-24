#pragma once

// System includes
#include <string>

class Problems
{

public:

	enum Name
	{

		Minotaur_Birthday_Party,
		Minotaur_Crystal_Vase

	};

	static std::string to_string(Name);
	static size_t get_number_of_guests();
	static Name get_problem_to_solve();

private:
	static constexpr size_t n_guests { 16 };
	static constexpr Name problem_to_solve { Name::Minotaur_Birthday_Party };

};
