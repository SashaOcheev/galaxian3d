#include "stdafx.h"
#include "BulletSystem.h"

void CreateFriendBullet(anax::World &m_world, const CModelPool &m_pool, const glm::vec3 &position)
{
	anax::Entity body = m_world.createEntity();
	AddMesh(body, m_pool.GetModel("bullet"));
	AddTransform(body, glm::vec3(0.03f), position, { 0.f, 0.f, 0.f });
	AddBullet(body, -0.3f);
	AddFriend(body);
	body.activate();
}

void CreateEnemyBullet(anax::World &m_world, const CModelPool &m_pool, const glm::vec3 &position)
{
	anax::Entity body = m_world.createEntity();
	AddMesh(body, m_pool.GetModel("bullet"));
	AddTransform(body, glm::vec3(0.03f), position, { 3.14f, 0.f, 0.f });
	AddBullet(body, 0.3f);
	AddEnemy(body);
	body.activate();
}

using namespace std;

void CBulletSystem::Update(float deltaSec)
{
	auto entities = getEntities();
	for (auto &entity : entities) {
		CTransformComponent& transform = entity.getComponent<CTransformComponent>();
		CBulletComponent& bullet = entity.getComponent<CBulletComponent>();
		transform.m_position.z += bullet.velocity;

		if (abs(transform.m_position.z) > 25.f)
		{
			entity.kill();
		}
	}
}
