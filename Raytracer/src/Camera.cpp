#include "stdafx.h"
#include <assert.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Camera.h"
#include "DeserializeData.h"
#include "Ray.h"

using namespace std;

static const int PLANE_WIDTH = 10;
static const int PLANE_HEIGHT = 10;
static const int PLANE_DEPTH = 0;


Camera::Camera()
:Object(ObjectType::CT_Camera)
{}

Camera::~Camera()
{
}

void Camera::Init(const DeserializeData& data)
{
	Plane inNearPlane;
	inNearPlane.Init(data.m_mapVector.at(DeserializeData::PLANE1), data.m_mapVector.at(DeserializeData::PLANE2));

	Init(data.m_mapVector.at(DeserializeData::POSITION), data.m_mapVector.at(DeserializeData::DIRECTION),
		inNearPlane);
}

void Camera::Init(const Vector3d& inPos, const Vector3d& inDir, const Plane& inNearPlane)
{
	m_position = inPos;
	m_direction = inDir;

	// TODO: Don't hardcode farplane
	//m_nearPlane = inNearPlane;
	m_nearPlane.Init(Vector3d(-PLANE_WIDTH + m_position.x, -PLANE_HEIGHT + m_position.y, m_position.z + PLANE_DEPTH),
		Vector3d(PLANE_WIDTH + m_position.x, PLANE_HEIGHT + m_position.y, m_position.z + PLANE_DEPTH));
}

Ray Camera::CreateRay(int column, int row, int maxColumn, int maxRow)
{
	Ray returnValue;
	Vector3d planePosition;

	assert(column < maxColumn);
	assert(row < maxRow);

	const double width = m_nearPlane.GetWidth();
	const double height = m_nearPlane.GetHeight();
	const double halfWidth = width *.5;
	const double halfHeight = height *.5;
	const double halfPixelHeight = (width/static_cast<double>(maxRow))*.5;
	const double halfPixelWidth = (height /static_cast<double>(maxColumn))*.5;

	const double xPos = ((static_cast<double>(column) / static_cast<double>(maxColumn))*height - halfHeight) + halfPixelWidth;
	const double yPos = ((static_cast<double>(row) / static_cast<double>(maxRow))*width - halfWidth) + halfPixelHeight;

	planePosition.x = xPos;
	planePosition.y = yPos;

	planePosition -= m_position;
	planePosition.NormalizeVector();
	returnValue.SetDirection(planePosition);
	returnValue.SetPosition(m_position);
	return returnValue;
}


TEST(CreateRay, Camera)
{
	Camera cameraTest;
	vector<Ray> createdResults;

	//@ TODO set through testfile
	cameraTest.Init(Vector3d(0, 0, 0), Vector3d(0, 0, -10).Normalize(), Plane());

	Ray test1;
	Ray test2;
	Ray test3;
	Ray test4;
	
	const double HALF_PIXEL_WIDTH = .1;
	const double HALF_PIXEL_HEIGHT = .1;
	const double MAX_COLUMN = 100;
	const double MAX_ROW = 100;
	const double PER_PIXEL_HEIGHT = (PLANE_WIDTH*2)/MAX_COLUMN;
	const double PER_PIXEL_WIDTH = (PLANE_HEIGHT * 2) / MAX_ROW;
	test1.Init(Vector3d(0, 0, 0), Vector3d(-PLANE_WIDTH + (PER_PIXEL_WIDTH * 0) + HALF_PIXEL_WIDTH, -PLANE_HEIGHT + (PER_PIXEL_HEIGHT * 0) + HALF_PIXEL_HEIGHT, PLANE_DEPTH + 0).Normalize());	// 0, 0
	test2.Init(Vector3d(0, 0, 0), Vector3d(-PLANE_WIDTH + (PER_PIXEL_WIDTH * 1) + HALF_PIXEL_WIDTH, -PLANE_HEIGHT + (PER_PIXEL_HEIGHT * 0) + HALF_PIXEL_HEIGHT, PLANE_DEPTH + 0).Normalize());	// 1, 0
	test3.Init(Vector3d(0, 0, 0), Vector3d(-PLANE_WIDTH + (PER_PIXEL_WIDTH * 0) + HALF_PIXEL_WIDTH, -PLANE_HEIGHT + (PER_PIXEL_HEIGHT * 1) + HALF_PIXEL_HEIGHT, PLANE_DEPTH + 0).Normalize());	// 0, 1
	test4.Init(Vector3d(0, 0, 0), Vector3d(-PLANE_WIDTH + (PER_PIXEL_WIDTH * 2) + HALF_PIXEL_WIDTH, -PLANE_HEIGHT + (PER_PIXEL_HEIGHT * 2) + HALF_PIXEL_HEIGHT, PLANE_DEPTH + 0).Normalize());	// 2, 2

	createdResults.push_back(cameraTest.CreateRay(0, 0, 100, 100));
	createdResults.push_back(cameraTest.CreateRay(1, 0, 100, 100));
	createdResults.push_back(cameraTest.CreateRay(0, 1, 100, 100));
	createdResults.push_back(cameraTest.CreateRay(2, 2, 100, 100));

	EXPECT_EQ(createdResults[0].GetDirection(), test1.GetDirection());
	EXPECT_EQ(createdResults[0].GetPosition(), test1.GetPosition());
	EXPECT_EQ(createdResults[1].GetDirection(), test2.GetDirection());
	EXPECT_EQ(createdResults[1].GetPosition(), test2.GetPosition());

	EXPECT_EQ(createdResults[2].GetDirection(), test3.GetDirection());
	EXPECT_EQ(createdResults[2].GetPosition(), test3.GetPosition());
	EXPECT_EQ(createdResults[3].GetDirection(), test4.GetDirection());
	EXPECT_EQ(createdResults[3].GetPosition(), test4.GetPosition());
}