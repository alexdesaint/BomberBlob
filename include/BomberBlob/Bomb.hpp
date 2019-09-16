#pragma once

#include <Blob/Collision/CollisionDetector.hpp>
#include <Blob/GL/Shapes.hpp>

#include <BomberBlob/UserData.hpp>

class Player;

class Bomb : public Blob::Collision::RectStatic, public Blob::GL::Shapes::Cube {
private:

	bool destroyed = false;

public:
	explicit Bomb(Blob::Vec2f pos, Blob::GL::Texture &texture);

    void hit(int objectType, Object &object) final;

	bool isDestroyed();
};
