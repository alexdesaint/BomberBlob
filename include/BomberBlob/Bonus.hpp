#ifndef PROJECT_EXTRABOMB_HPP
#define PROJECT_EXTRABOMB_HPP

#include <Blob/Collision/CollisionDetector.hpp>
#include <Blob/GL/Shapes.hpp>
#include <Blob/Time.hpp>

#include <BomberBlob/UserData.hpp>

#include <BomberBlob/Textures.hpp>

class Bonus : public Blob::Collision::RectStatic, public Blob::GL::Shapes::Cube {
private:
	bool destroyed = false;
public:
	explicit Bonus(Blob::Vec2f pos, Textures &textures);

    void hit(int objectType, Object &object) final;

	bool update();
};


#endif //PROJECT_EXTRABOMB_HPP
