// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <gtest\gtest.h>
#include <iostream>
#include <memory>
#include "WorldManager.h"
#include "YamlFile.h"

using namespace std;

int main(int argc, char **argv) 
{
	// unit tests
	::testing::InitGoogleTest(&argc, argv);
	const int returnValue = RUN_ALL_TESTS();


	// do stuff
	WorldManager world;

	//auto tt = make_unique<YamlFile>();
	//std::unique_ptr<IFileLoader> loadertt = tt;
	std::unique_ptr<IFileLoader> loader(new YamlFile());
	char t = ' ';

	world.InitSystems(loader);
	world.Init("Object.yaml");
	world.Render(true);
	while (t != 'x')
	{
		world.Render(false);
		std::cin >> t;
	}

	//delete loader;

	return returnValue;
}
