#include "stdafx.h"
#include "PlayerSystem.h"
#include "BulletSystem.h"

using namespace std;

float SHOOT_INTERVAL_TIME = 1.f;

void CreatePlayer(anax::World &m_world, const CModelPool &m_pool)
{
	anax::Entity body = m_world.createEntity();
	AddMesh(body, m_pool.GetModel("player"));
	AddTransform(body, glm::vec3(1.f), { 0.f, 0.f, 8.f }, { 1.57f, 0.f, 3.14f });
	CTransformComponent& transform = body.getComponent<CTransformComponent>();
	transform.life = 3;
	transform.startOrientation = transform.prim_orientation = glm::vec3(1.57f, 0.f, 3.14f);
	AddControl(body);
	AddCanShoot(body);
	AddFriend(body);
	body.activate();
}

bool ShouldTrackKeyPressed(const SDL_Keysym &key)
{
	switch (key.sym)
	{
	case SDLK_LEFT:
	case SDLK_RIGHT:
	case SDLK_UP:
	case SDLK_DOWN:
	case SDLK_w:
	case SDLK_a:
	case SDLK_s:
	case SDLK_d:
	case SDLK_SPACE:
		return true;
	}
	return false;
}

using namespace glm;


vec3 GetMoveDirection(const std::set<unsigned> & keysPressed)
{
	vec3 direction;
	if (keysPressed.count(SDLK_RIGHT) || keysPressed.count(SDLK_d))
	{
		direction.x = 0.3f;
	}
	else if (keysPressed.count(SDLK_LEFT) || keysPressed.count(SDLK_a))
	{
		direction.x = -0.3f;
	}

	return direction;
}


void CPlayerSystem::Update(float deltaSec, anax::World &m_world, const CModelPool &m_pool)
{
	auto move = GetMoveDirection(m_keysPressed);
	auto entities = getEntities();
	for (auto &entity : entities) {
		if (entity.getComponent<CTransformComponent>().life <= 0)
		{
			entity.kill();
			continue;
		}
		CTransformComponent& transform = entity.getComponent<CTransformComponent>();
		transform.m_position += move;
		if (move.x < 0)
		{
			transform.prim_orientation.z = transform.startOrientation.z + 0.5;
		}
		else if (move.x > 0)
		{
			transform.prim_orientation.z = transform.startOrientation.z - 0.5;
		}
		else
		{
			transform.prim_orientation.z = transform.startOrientation.z;
		}
		transform.m_orientation = glm::quat(transform.prim_orientation);

		if (abs(transform.m_position.x) > FLANK_BOUND)
		{
			transform.m_position.x = -transform.m_position.x / abs(transform.m_position.x) * FLANK_BOUND;
		}

		CCanShootComponent& canShoot = entity.getComponent<CCanShootComponent>();

		if (canShoot.m_canShoot)
		{
			if (m_keysPressed.count(SDLK_SPACE))
			{
				canShoot.m_canShoot = false;
				CreateFriendBullet(m_world, m_pool, transform.m_position);
			}
		}
		else
		{
			m_lastShootTime += deltaSec;
			if (m_lastShootTime > SHOOT_INTERVAL_TIME)
			{
				m_lastShootTime = 0.f;
				canShoot.m_canShoot = true;
			}
		}
	}
}


bool CPlayerSystem::OnKeyDown(const SDL_KeyboardEvent &event)
{
	if (ShouldTrackKeyPressed(event.keysym))
	{
		m_keysPressed.insert(unsigned(event.keysym.sym));
		return true;
	}
	return false;
}

bool CPlayerSystem::OnKeyUp(const SDL_KeyboardEvent &event)
{
	if (ShouldTrackKeyPressed(event.keysym))
	{
		m_keysPressed.erase(unsigned(event.keysym.sym));
		return true;
	}
	return false;
}

