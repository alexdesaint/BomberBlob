#include <BlobJump/BlobJump.hpp>

#include <Core/DynamicCube.hpp>
#include <Core/StaticCube.hpp>
#include <deque>
#include <memory>
#include <unordered_set>

using namespace Blob;

struct Body : public DynamicCube, private Core::KeyboardEvents {
    Materials::PBRSingleColor material;

    explicit Body(b2World &world) : DynamicCube(world, {0.0f, 4.0f}, 1, material, 0) {}

    void keyboardUpdate(const Core::Keyboard &keyboard) final {
        speed = 0;

        if (keyboard.RIGHT)
            speed.x++;
        if (keyboard.LEFT)
            speed.x--;
        if (keyboard.UP)
            speed.y++;
        if (keyboard.DOWN)
            speed.y--;
    }
};

BlobJump::BlobJump(Core::Window &window, std::map<int, Player> &players)
    : Game(window, players, {{0, 0, 50}, {0, 0, 0}, {0, 1, 0}}), world({0, -10.f}) {}

void BlobJump::load() {
    window.setCamera(camera);
    float cameraAngle = PI / 4;
    window.setAngle(cameraAngle);
    window.setRange(10, 500);

    Materials::PBR::light.position = {0, 10, 4};

    staticCubes.emplace_back(world, Maths::Vec2<float>{4, 4}, 1, assetManager.shapes.materials.defaultM, 1);
    staticCubes.emplace_back(world, Maths::Vec2<float>{-4, 4}, 1, assetManager.shapes.materials.defaultM, 1);
    staticCubes.emplace_back(world, Maths::Vec2<float>{0, -10}, 5, assetManager.shapes.materials.defaultM, 1);

    for (auto &sc : staticCubes)
        scene.addShape(sc);

    loaded = true;
}

void BlobJump::run() {

    // Body
    Body body(world);
    scene.addShape(body);

    // ?
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    float timeStep = 0;

    while (window.isOpen()) {
        world.Step(timeStep, velocityIterations, positionIterations);

        body.update();
        window.draw(scene);
        timeStep = window.display();
    }
}