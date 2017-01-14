#pragma once
#include "libscene/StaticModel3D.h"
#include "libgeometry/Transform.h"
#include <anax/Component.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

const float FLANK_BOUND = 14.f;

class CMeshComponent
        : public anax::Component
{
public:
    enum Category
    {
        // Объект заднего плана, сливающийся с окружением.
        Environment,
        // Объект переднего плана.
        Foreground,
    };

    Category m_category;
    CStaticModel3DPtr m_pModel;
};

class CTransformComponent
        : public anax::Component
        , public CTransform3D
{
public:
	CTransformComponent();

	glm::vec3 startOrientation;
	glm::vec3 prim_orientation; //because precision
	unsigned life = 1;
};

class CCanShootComponent
	: public  anax::Component
{
public:
	bool m_canShoot = true;
};

class CControlComponent
	: public anax::Component
{
};

class CSadSackComponent
	: public anax::Component
{
};

class CShootEnemyComponent
	: public anax::Component
{
};

class CEnemyComponent
	: public anax::Component
{
};

class CFriendComponent
	: public anax::Component
{
};

class CBulletComponent
	: public anax::Component
{
public:
	float velocity;
};

class CRotateComponent
	: public anax::Component
{
public:
	glm::vec3 velocity;
};

class CHeartComponent
	:public anax::Component
{
public:
	float knockStart;
	float knockFinish;
	float currentTime;
	float startSize;
};

class CTrooperComponent
	: public anax::Component
{
public:
	float velocity_x;
	float velocity_z;
	float interval_x;
	float start_x;
};


void AddMesh(anax::Entity &body, const CStaticModel3DPtr &model);
void AddTransform(anax::Entity &body, const glm::vec3 &size, const glm::vec3 &pos, const glm::vec3 &eulerAngles);
void AddControl(anax::Entity &body);
void AddEnemy(anax::Entity &body);
void AddBullet(anax::Entity &body, float velocity);
void AddCanShoot(anax::Entity &body);
void AddFriend(anax::Entity &body);
void AddSadSack(anax::Entity &body);
void AddShootEnemy(anax::Entity &body);
void AddTrooper(anax::Entity &body, float velocity_x, float velocity_z, float interval_x, float start_x);
void AddHeart(anax::Entity &body, float knockStart, float knockFinish, float startSize);
void AddRotate(anax::Entity &body, const glm::vec3 &velocity);