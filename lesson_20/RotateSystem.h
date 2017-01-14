#pragma once
#include "Components.h"
#include <anax/System.hpp>
#include "TimeController.h"
#include "SceneLoader.h"

class CRotateSystem
	: public anax::System<anax::Requires<CTransformComponent, CRotateComponent>>
{
public:
	CRotateSystem() = default;

	void Update();

private:
};


void CreateHeart(anax::World &m_world, const CModelPool &m_pool, const glm::vec3 &position);