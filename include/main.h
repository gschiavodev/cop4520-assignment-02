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

};

