#include "engine/physics/physics_system.hpp"

namespace engine {

void PhysicsSystem::Update(Entity* entity) {
    auto rigid = entity->GetComponent<RigidBodyComponent>();
    if (!rigid) return;

    Vec2 acceleration = (rigid->force / rigid->mass);
    acceleration -= Normalize(acceleration) * rigid->damping;
    if (Dot(acceleration, rigid->force) <= 0) acceleration.Set(0, 0);

    double elapse = Timer::GetElapse() / 1000.0;

    rigid->velocity = acceleration * elapse;
    float maxSpeed = std::min(maxSpeed_, rigid->maxSpeed);
    if (Length2(rigid->velocity) > maxSpeed * maxSpeed) {
        rigid->velocity = Normalize(rigid->velocity) * maxSpeed_;
    }

    if (auto node2d = entity->GetComponent<Node2DComponent>(); node2d) {
        node2d->position += rigid->velocity * elapse + 0.5 * acceleration * elapse * elapse;
    }

    rigid->force.Set(0, 0);
}


void CollideSystem::Update() {
    // TODO not finish
}

void CollideSystem::AddEntity(Entity* entity) {
    entities_.push_back(entity);
}

void CollideSystem::RemoveEntity(Entity* entity) {
    auto it = entities_.begin();
    while (it != entities_.end() && *it != entity) {
        it ++;
    }

    if (it != entities_.end()) {
        entities_.erase(it);
    }
}

bool CollideSystem::isCollide(BoxColliderComponent* box1, const Vec2& pos1, BoxColliderComponent* box2, const Vec2& pos2) {
    if (!box1 || !box2) {
        return false;
    }

    auto center1 = box1->offset + pos1,
         center2 = box2->offset + pos2;

    return !(center1.x - box1->halfWidth  > center2.x + box2->halfWidth  ||
             center1.y - box1->halfHeight > center2.y + box2->halfHeight ||
             center1.x + box1->halfWidth  < center2.x - box2->halfWidth  ||
             center1.y + box1->halfHeight < center2.y - box2->halfHeight);
}

void ColliderCollectSystem::Update(Entity* entity) {
    if (!collideSystem_) return;

    if (auto boxCollider = entity->GetComponent<BoxColliderComponent>(); boxCollider) {
        if (!boxCollider->pushedInLayer_) {
            boxCollider->pushedInLayer_ = true;
            collideSystem_->AddEntity(entity);
        }
    }
}

}