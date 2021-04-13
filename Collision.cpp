#include "Collision.h"

CollisionManager* CollisionManager::s_pInstance = 0;
CollisionManager* CollisionManager::Instance() {
	if (s_pInstance == 0)
		s_pInstance = new CollisionManager();
	return s_pInstance;
}
