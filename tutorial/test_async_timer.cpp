﻿
#include <chrono>
#include <iostream>
#include <string>
#include <conio.h>
#include <thread>

#include "librf.h"

using namespace resumef;

void resumable_main_timer()
{
	using namespace std::chrono;

	auto th = g_scheduler.timer()->add_handler(system_clock::now() + 5s, 
		[](bool bValue) 
	{
		if (bValue)
			std::cout << "timer canceled." << std::endl;
		else
			std::cout << "timer after 5s." << std::endl;
	});

	auto th2 = g_scheduler.timer()->add_handler(1s, 
		[&th](bool)
	{
		std::cout << "timer after 1s." << std::endl;
		th.stop();
	});

	g_scheduler.run_until_notask();


	th2.stop();	//but th2 is invalid
}
