#include "stdafx.h"
#include "GameState.h"
#include "RotateSystem.h"

using namespace std;
using namespace glm;


void CRotateSystem::Update()
{
	auto entities = getEntities();
	for (auto &entity : entities)
	{
		CTransformComponent &transform = entity.getComponent<CTransformComponent>();
		CRotateComponent &rotate = entity.getComponent<CRotateComponent>();
		transform.prim_orientation += rotate.velocity;
		transform.m_orientation = quat(transform.prim_orientation);
	}
}
