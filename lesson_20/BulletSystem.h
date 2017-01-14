#pragma once
#include "Components.h"
#include <anax/System.hpp>
#include "TimeController.h"
#include "SceneLoader.h"

void CreateFriendBullet(anax::World &m_world, const CModelPool &m_pool, const glm::vec3 &position);
void CreateEnemyBullet(anax::World &m_world, const CModelPool &m_pool, const glm::vec3 &position);


class CBulletSystem
	: public anax::System<anax::Requires<CTransformComponent, CBulletComponent>>
{
public:
	CBulletSystem() = default;

	void Update(float deltaSec);
};

class CFriendBulletSystem
	: CBulletSystem, anax::System<anax::Requires<CFriendComponent>>
{
};

class CEnemyBulletSystem
	: CBulletSystem, anax::System<anax::Requires<CEnemyComponent>>
{
};