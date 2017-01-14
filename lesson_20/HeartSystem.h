#pragma once
#include "Components.h"
#include <anax/System.hpp>
#include "SceneLoader.h"

void CreateHeart(anax::World &m_world, const CModelPool &m_pool, const glm::vec3 &position);


class CHeartSystem
	: public anax::System<anax::Requires<CTransformComponent, CHeartComponent>>
{
public:

	void Update(float deltaSec, anax::World &m_world);

private:
};