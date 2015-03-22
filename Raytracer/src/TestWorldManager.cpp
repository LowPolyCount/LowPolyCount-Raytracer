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
	EXPECT_EQ(test.GetImage()->GetWidth(), 256);
	EXPECT_EQ(test.GetImage()->GetHeight(), 640);

	EXPECT_EQ(test.TestGetObjects().size(), 2);
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
	TestWorldManager test;
	std::unique_ptr<IFileLoader> file(new YamlFileLoader());
	test.InitSystems(file);
	EXPECT_TRUE(test.Init("unittest.yaml"));

	test.Render(false);
	const vector<vector<Ray>>& scene = test.GetCurrentScene();

	EXPECT_EQ(scene.size(), test.GetImage()->GetWidth());
	EXPECT_EQ(scene[0].size(), test.GetImage()->GetHeight());
}