#pragma once
#include <iostream>
#include <chrono>
#include <thread>

struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	float stop(const char* msg)
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float s = duration.count();
		std::wcout << msg << " " << s << "s" << std::endl;

		return s;
	}


};