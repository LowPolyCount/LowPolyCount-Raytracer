#pragma once

struct DeserializeData;
class Object
{
public:
	enum ObjectType
	{
		// types that can collide with each other
		CT_Sphere = 0,
		CT_Point,
		CT_Ray,
		CT_Plane,
		CT_InfinitePlane,

		// other types of objects
		CT_Image,
		CT_Camera,
		CT_Error,
		CT_Unknown
	};

	explicit Object(ObjectType inType);
	virtual ~Object();
	virtual void Init(const DeserializeData& data) = 0;
	inline ObjectType GetType() const { return m_type; }
private:
	ObjectType m_type;
};

