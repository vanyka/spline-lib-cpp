// A simple program that computes the square root of a number
#include <iostream>
#include <string.h>

#include <app/config.h>
#include <vanyka.hpp>
#include "segg.h"

void PrintAppVersion() {
    std::cout << "App v" << APP_VERSION_MAJOR << '.' << APP_VERSION_MINOR << '.' << APP_VERSION_PATCH << std::endl;
}

bool ProcessArgs(int argc, char* argv[]) {
	constexpr char* versions[] = { "-v", "--version", "-V" };
	for (int i = 1; i < argc; ++i) {
		for (char* v : versions) {
			if (std::strcmp(v, argv[i]) == 0) {
				PrintAppVersion();
				return true;
			}
		}
	}
	return false;
}

int main(int argc, char* argv[])
{
	if (ProcessArgs(argc, argv)) 
		return 0;
	
	//Calling Functions from a lib
	vanyka::PrintHelloWorld();

	//Using project internal files
	Segg seggem;
	std::cout << "Seggem Szaga: ";
	switch (seggem.Szagol())
	{
	case Segg::Budos: std::cout << "Budos. uhh"; break;
	case Segg::Illatos: std::cout << "Illatos."; break;
	}
	std::cout << std::endl;
	seggem.Befosik();
	std::cout << "Seggem Szaga: ";
	switch (seggem.Szagol())
	{
	case Segg::Budos: std::cout << "Budos. uhh"; break;
	case Segg::Illatos: std::cout << "Illatos."; break;
	}
	std::cout << std::endl;
	return 0;
}
