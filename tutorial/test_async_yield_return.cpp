﻿
#include <chrono>
#include <iostream>
#include <string>
#include <conio.h>
#include <thread>

#include "librf.h"

using namespace resumef;

//std::experimental::generator<int>
auto test_yield_int()
{
	std::cout << "1 will yield return" << std::endl;
	co_yield 1;
	std::cout << "2 will yield return" << std::endl;
	co_yield 2;
	std::cout << "3 will yield return" << std::endl;
	co_yield 3;
	std::cout << "4 will return" << std::endl;
	return 4;

	std::cout << "5 will never yield return" << std::endl;
	co_yield 5;
}

/*不能编译*/
/*
auto test_yield_void()
{
	std::cout << "1 will yield return" << std::endl;
	co_yield ;
	std::cout << "2 will yield return" << std::endl;
	co_yield ;
	std::cout << "3 will yield return" << std::endl;
	co_yield ;
	std::cout << "4 will return" << std::endl;
	co_return ;

	std::cout << "5 will never yield return" << std::endl;
	co_yield ;
}
*/

#define co_yield_void co_yield nullptr
#define co_return_void co_return nullptr

auto test_yield_void()
{
	std::cout << "block 1 will yield return" << std::endl;
	co_yield_void;
	std::cout << "block 2 will yield return" << std::endl;
	co_yield_void;
	std::cout << "block 3 will yield return" << std::endl;
	co_yield_void;
	std::cout << "block 4 will return" << std::endl;
	co_return_void;

	std::cout << "block 5 will never yield return" << std::endl;
	co_yield_void;
}

void resumable_main_yield_return()
{
	go test_yield_int();
	g_scheduler.run_until_notask();

	go test_yield_void();
	g_scheduler.run_until_notask();
}
