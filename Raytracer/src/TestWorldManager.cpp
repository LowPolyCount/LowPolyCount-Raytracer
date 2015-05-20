#include "stdafx.h"
#include "TestWorldManager.h"
#include <gtest\gtest.h>
#include "RendererSDL.h"
#include "YamlFileLoader.h"
#include "Ray.h"

using namespace std;


TestWorldManager::TestWorldManager()
{
}


TestWorldManager::~TestWorldManager()
{
}

TEST(init, WorldManager)
{
	TestWorldManager test;
	std::unique_ptr<IFileLoader> loader(new YamlFileLoader);

	test.InitSystems(loader);
	EXPECT_TRUE(test.Init("unittest.yaml"));

	EXPECT_EQ(test.GetCamera()->GetDirection(), Vector3d(1, 1, 1));
	EXPECT_EQ(test.GetCamera()->GetPosition(), Vector3d(1, 1, 1));
//	EXPECT_EQ(test.GetCamera()->GetNearPlane(), Vector3d(0, 1, 2));
//	EXPECT_EQ(test.GetCamera()->GetFarPlane(), Vector3d(2, 1, 0));
	EXPECT_EQ(test.GetCamera()->GetPosition(), Vector3d(1, 1, 1));
	EXPECT_EQ(test.GetImage()->GetWidth(), 25);
	EXPECT_EQ(test.GetImage()->GetHeight(), 64);

	EXPECT_EQ(test.TestGetObjects().size(), 3);
	EXPECT_EQ(test.TestGetLights().size(), 3);
}

// TODO: Enable one day
/*TEST(initFail, WorldManager)
{
	TestWorldManager test;
	EXPECT_FALSE(test.Init("doesnotexist"));
	EXPECT_EQ(test.TestGetObjects().size(), 0);
}*/

TEST(Render, WorldManager)
{
	TestWorldManager testWorld;
	std::unique_ptr<IFileLoader> file(new YamlFileLoader());
	testWorld.InitSystems(file);
	EXPECT_TRUE(testWorld.Init("unittest.yaml"));

	testWorld.TestUpdateRays();
	const vector<vector<Ray>>& scene = testWorld.GetCurrentScene();

	EXPECT_EQ(scene.size(), testWorld.GetImage()->GetWidth());
	EXPECT_EQ(scene[0].size(), testWorld.GetImage()->GetHeight());
}

TEST(LightHit, WorldManager)
{
	TestWorldManager testWorld;
	std::unique_ptr<IFileLoader> file(new YamlFileLoader());
	testWorld.InitSystems(file);
	EXPECT_TRUE(testWorld.Init("unittest.yaml"));

	const Vector3d rayStart(5, 5, 2.9);
	Ray test1;
	Ray test2;
	Ray test3;
	test1.Init(rayStart, (testWorld.TestGetLights()[0]->GetPosition() - rayStart).Normalize());
	test2.Init(rayStart, (testWorld.TestGetLights()[1]->GetPosition() - rayStart).Normalize());
	test3.Init(rayStart, (testWorld.TestGetLights()[2]->GetPosition() - rayStart).Normalize());

	EXPECT_TRUE(testWorld.TestLightCollision(testWorld.TestGetLights()[0], test1));
	EXPECT_FALSE(testWorld.TestLightCollision(testWorld.TestGetLights()[1], test2));
	EXPECT_TRUE(testWorld.TestLightCollision(testWorld.TestGetLights()[2], test3));
}