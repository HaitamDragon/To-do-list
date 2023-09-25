#ifndef UTILITY_H
#define UTILITY_H

#include <chrono>
#include <ctime>
#include <iostream>

namespace utility // to avoid variable identifier collision
{
	// a way to get the current time (copied from the internet)
	char* getTime()
	{
		const auto now = std::chrono::system_clock::now();
		const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
		return std::ctime(&t_c);
	}

	void handleIncorrectInput()
	{
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	void clearScreen()
	{
		std::cout << "\033[2J\033[1;1H"; // Copied from the internet, this clears the console.
	}
}
#endif
