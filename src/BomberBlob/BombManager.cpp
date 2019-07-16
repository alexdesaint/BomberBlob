#include <BomberBlob/BombManager.hpp>

#include <BomberBlob/Player.hpp>

using namespace Blob;
using namespace Blob::Time;

BombManager::BombManager(Blob::Vec2f pos, Player &player, Textures &textures) : player(player), textures(textures) {
	bomb = new Bomb(pos, textures.bomb);

	addRenderable(bomb);

	start = now();
}

bool BombManager::update() {
	Duration flow = now() - start;
	if(bomb == nullptr) {
		if(exUP != nullptr && !exUP->isActive()) {
			removeRenderable(exUP);
			delete exUP;
			exUP = nullptr;
		}

		if(exDO != nullptr && !exDO->isActive()) {
			removeRenderable(exDO);
			delete exDO;
			exDO = nullptr;
		}

		if(exLE != nullptr && !exLE->isActive()) {
			removeRenderable(exLE);
			delete exLE;
			exLE = nullptr;
		}

		if(exRI != nullptr && !exRI->isActive()) {
			removeRenderable(exRI);
			delete exRI;
			exRI = nullptr;
		}

		return exUP == nullptr && exDO == nullptr && exRI == nullptr && exLE == nullptr;
	} else if(flow.count() > bombDelay || bomb->isDestroyed()) {
		player.bombPosed--;

        exRI = new Explosion(bomb->position, Vec2f(0, 1), player.bombPower, textures.explostion);
        exLE = new Explosion(bomb->position, Vec2f(0, -1), player.bombPower, textures.explostion);
        exDO = new Explosion(bomb->position, Vec2f(1, 0), player.bombPower, textures.explostion);
        exUP = new Explosion(bomb->position, Vec2f(-1, 0), player.bombPower, textures.explostion);

		addRenderable(exRI);
		addRenderable(exLE);
		addRenderable(exDO);
		addRenderable(exUP);

		removeRenderable(bomb);
		delete bomb;
		bomb = nullptr;
	}

	return false;
}

Bomb *BombManager::getBomb() const {
	return bomb;
}

BombManager::~BombManager() {
	if(exUP != nullptr) {
		removeRenderable(exUP);
		delete exUP;
	}

	if(exDO != nullptr) {
		removeRenderable(exDO);
		delete exDO;
	}

	if(exLE != nullptr) {
		removeRenderable(exLE);
		delete exLE;
	}

	if(exRI != nullptr) {
		removeRenderable(exRI);
		delete exRI;
	}

	if(bomb != nullptr) {
		removeRenderable(bomb);
		delete bomb;
	}
}
