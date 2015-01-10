#include "stdafx.h"
#include <assert.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Camera.h"
#include "DeserializeData.h"

static const int PLANE_WIDTH = 10;
static const int PLANE_HEIGHT = 10;
static const int PLANE_DEPTH = -10;
static const double FOCAL_DISTANCE = 1;


Camera::Camera()
:WorldObject(WorldType::CT_Camera)
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

	assert(column < maxColumn);
	assert(row < maxRow);

	const double width = m_nearPlane.GetWidth();
	const double height = m_nearPlane.GetHeight();
	const double fovX = 3.14159 / 3;
	const double fovY = ((height/2) / (width/2))*fovX;
	const double tanFovX = tan(fovX);
	const double tanFovY = tan(fovY);

	const double invWidth = 1 / width;
	const double invHeight = 1 / height;
	const double fov = 90;
	const double aspectratio = width / height;				//defining field of view angle and aspect ratio
	const double fovDist = tan(3.14159 * 0.5 * fov / 180);	//Calculates half screen width / perpendicular distance to the camera position

	double xx = (2 * ((column + 0.5) * invWidth) - 1) * fovDist * aspectratio;
	double yy = (1 - 2 * ((row + 0.5) * invHeight)) * fovDist;//Calculate the y position


	// calculate point on the view plane
	// calc x (row)
	const double columnPer = width / maxColumn;
	
	// calc y (column)
	const double rowPer = height / maxRow;

	// get direction vector
	Vector3d dir = m_nearPlane.GetUpperLeft();

	double scaleX = tan(fovX);
	double scaleY = tan(fovY / (width / height));

	dir.x = scaleX*(1 * column - width) / width;
	dir.y = scaleY*(1 * row - height) / height;

	//dir.x += ((2*column - width*2) / (width*2))*tanFovX;
	//dir.y += ((2*row - height*2) / (height*2))*tanFovY;
	//dir.x = xx;
	//dir.y = yy;
	//dir.z = -1;
	//dir.x += columnPer*column+columnPer / 2;
	//dir.y += rowPer*row+rowPer / 2;
	//dir.z = dir.z; //- m_position.z;

	dir -= m_position;
	dir.NormalizeVector();

	returnValue.Init(m_position, dir);

	return returnValue;
}


/*template<typename T>
void render(const std::vector<Sphere<double> *> &spheres)
{
int width = 800, height = 800;//define width and height of the screen
Vector3d<double> *image = new Vector3d<double>[width * height], *pixel = image;
double invWidth = 1 / double(width), invHeight = 1 / double(height);
double fov = 90, aspectratio = width / double(height);//defining field of view angle and aspect ratio
double fovDist = tan(M_PI * 0.5 * fov / double(180));//Calculates half screen width / perpendicular distance to the camera position
// For each ray crossing a pixel on the view screen.
for (int y = 0; y < height; ++y) //For each scan line
{
for (int x = 0; x < width; ++x, ++pixel) //for each pixel on a scan line
{
//Calculate the x position using centre of the pixel.
/*By simple trig (width/2)/perpendicular distance to camera = tan (fov/2)
=>width = distance * tan (fov/2)

*/
/*double xx = (2 * ((x + 0.5) * invWidth) - 1) * fovDist * aspectratio;
double yy = (1 - 2 * ((y + 0.5) * invHeight)) * fovDist;//Calculate the y position
Vector3d<double> raydir(xx, yy, -1);
raydir.normalize();
/*pixel = trace(Vector3d<T>(0), raydir, spheres, 0);
		}
	}
*/

TEST(CreateRay, Camera)
{
	Camera test;

	//@ TODO set 
	test.Init(Vector3d(0, 0, 0), Vector3d(0, 0, -10).Normalize(), Plane());

	Ray test1;
	Ray test2;
	Ray test3;
	Ray test4;

	const double HALF_PIXEL_WIDTH = .1;
	const double HALF_PIXEL_HEIGHT = .1;
	test1.Init(Vector3d(0, 0, 0), Vector3d(-PLANE_WIDTH + .0 + HALF_PIXEL_WIDTH, -PLANE_HEIGHT + .0 + HALF_PIXEL_HEIGHT, PLANE_DEPTH + 0).Normalize());
	test2.Init(Vector3d(0, 0, 0), Vector3d(-PLANE_WIDTH + .2 + HALF_PIXEL_WIDTH, -PLANE_HEIGHT + .0 + HALF_PIXEL_HEIGHT, PLANE_DEPTH + 0).Normalize());
	test3.Init(Vector3d(0, 0, 0), Vector3d(-PLANE_WIDTH + .0 + HALF_PIXEL_WIDTH, -PLANE_HEIGHT + .2 + HALF_PIXEL_HEIGHT, PLANE_DEPTH + 0).Normalize());
	test4.Init(Vector3d(0, 0, 0), Vector3d(-PLANE_WIDTH + .4 + HALF_PIXEL_WIDTH, -PLANE_HEIGHT + .4 + HALF_PIXEL_HEIGHT, PLANE_DEPTH + 0).Normalize());

	EXPECT_EQ(test.CreateRay(0, 0, 100, 100), test1);
	EXPECT_EQ(test.CreateRay(1, 0, 100, 100), test2);

	EXPECT_EQ(test.CreateRay(0, 1, 100, 100), test3);
	EXPECT_EQ(test.CreateRay(2, 2, 100, 100), test4);
}