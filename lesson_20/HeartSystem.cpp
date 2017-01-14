#include "stdafx.h"
#include "PlayerSystem.h"
#include "HeartSystem.h"

using namespace std;

void CreateHeart(anax::World &m_world, const CModelPool &m_pool, const glm::vec3 &position)
{
	anax::Entity body = m_world.createEntity();
	AddMesh(body, m_pool.GetModel("heart"));
	AddTransform(body, glm::vec3(0.1f), position, { 1.57f, 3.14f, 0.f });
	AddHeart(body, 0.8f, 1.f, 0.1f);
	body.activate();
}




void CHeartSystem::Update(float deltaSec, anax::World & m_world)
{
	auto entities = getEntities();
	for (auto &entity : entities)
	{
		CTransformComponent& transform = entity.getComponent<CTransformComponent>();
		CHeartComponent& heart = entity.getComponent<CHeartComponent>();
		heart.currentTime += deltaSec;
		if (heart.currentTime < heart.knockStart)
		{

		}
		else if (heart.currentTime > heart.knockFinish)
		{
			transform.m_sizeScale = glm::vec3(heart.startSize);
			heart.currentTime = 0.f;
		}
		else if (heart.currentTime > heart.knockStart && heart.currentTime < heart.knockStart + (heart.knockFinish - heart.knockStart) / 2)
		{
			transform.m_sizeScale += 0.01f;
		}
		else
		{
			transform.m_sizeScale -= 0.01f;
		}
	}

	auto allEntities = m_world.getEntities();
	for (auto &entity : allEntities)
	{
		if (entity.hasComponent<CControlComponent>())
		{
			if (entities.size() > entity.getComponent<CTransformComponent>().life)
			{
				entities.begin()->kill();
			}
		}
	}
}
