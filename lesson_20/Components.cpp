#pragma once
#include "stdafx.h"
#include "Components.h"


void AddMesh(anax::Entity &body, const CStaticModel3DPtr &model)
{
	auto &mesh = body.addComponent<CMeshComponent>();
	mesh.m_category = CMeshComponent::Foreground;
	mesh.m_pModel = model;
}

void AddTransform(anax::Entity &body, const glm::vec3 &size, const glm::vec3 &pos, const glm::vec3 &eulerAngles)
{
	auto &com = body.addComponent<CTransformComponent>();
	com.m_sizeScale = size;
	com.m_position = pos;
	com.prim_orientation = eulerAngles;
	com.m_orientation = glm::quat(eulerAngles);
	com.startOrientation = eulerAngles;
}

void AddControl(anax::Entity &body)
{
	body.addComponent<CControlComponent>();
}

void AddEnemy(anax::Entity &body)
{
	body.addComponent<CEnemyComponent>();
}

void AddBullet(anax::Entity &body, float velocity)
{
	auto &com = body.addComponent<CBulletComponent>();
	com.velocity = velocity;
}

void AddCanShoot(anax::Entity &body)
{
	body.addComponent<CCanShootComponent>();
}

void AddFriend(anax::Entity & body)
{
	body.addComponent<CFriendComponent>();
}

void AddSadSack(anax::Entity & body)
{
	body.addComponent<CSadSackComponent>();
}

void AddShootEnemy(anax::Entity & body)
{
	body.addComponent<CShootEnemyComponent>();
}

void AddTrooper(anax::Entity & body, float velocity_x, float velocity_z, float interval_x, float start_x)
{
	auto &com = body.addComponent<CTrooperComponent>();
	com.velocity_x = velocity_x;
	com.velocity_z = velocity_z;
	com.interval_x = interval_x;
	com.start_x = start_x;
}

void AddHeart(anax::Entity & body, float knockStart, float knockFinish, float startSize)
{
	auto &com = body.addComponent<CHeartComponent>();
	com.knockStart = knockStart;
	com.knockFinish = knockFinish;
	com.currentTime = 0.f;
	com.startSize = startSize;
}

void AddRotate(anax::Entity & body, const glm::vec3 & velocity)
{
	auto &com = body.addComponent<CRotateComponent>();
	com.velocity = velocity;
}

CTransformComponent::CTransformComponent()
	: startOrientation(startOrientation)
{
}
