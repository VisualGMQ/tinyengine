#include "engine/physics/physics_system.hpp"

namespace engine {

void PhysicsSystem::Update(Entity* entity) {
    auto rigid = entity->GetComponent<RigidBodyComponent>();
    if (!rigid) return;

    rigid->acceleration += (rigid->force / rigid->mass);
    rigid->acceleration -= Normalize(rigid->acceleration) * rigid->damping * rigid->mass;
    if (Dot(rigid->acceleration, rigid->force) < 0) rigid->acceleration.Set(0, 0);

    double elapse = Timer::GetElapse() / 1000.0;

    rigid->velocity = rigid->acceleration * elapse;
    float maxSpeed = std::min(maxSpeed_, rigid->maxSpeed);
    if (Length2(rigid->velocity) > maxSpeed * maxSpeed) {
        rigid->velocity = Normalize(rigid->velocity) * maxSpeed_;
    }

    if (auto node2d = entity->GetComponent<Node2DComponent>(); node2d) {
        node2d->position += rigid->velocity * elapse + 0.5 * rigid->acceleration * elapse * elapse;
    }

    rigid->force.Set(0, 0);
}

constexpr int MaxIterCount = 100;

void CollideSystem::Update() {
    for (int i = 0; i < entities_.size(); i++) {
        for (int j = i + 1; j < entities_.size(); j++) {
            auto entity1 = entities_[i];
            auto entity2 = entities_[j];

            auto box1 = entity1->GetComponent<BoxColliderComponent>(),
                 box2 = entity2->GetComponent<BoxColliderComponent>();
            auto node1 = entity1->GetComponent<Node2DComponent>(),
                 node2 = entity2->GetComponent<Node2DComponent>();
            auto rigid1 = entity1->GetComponent<RigidBodyComponent>(),
                 rigid2 = entity2->GetComponent<RigidBodyComponent>();
            if (node1 && node2 && box1 && box2 && (box1->layer & box2->layer) &&
                isCollide(box1, node1->position, box2, node2->position)) {
                auto behavior1 = entity1->GetBehavior();
                auto behavior2 = entity2->GetBehavior();
                if (behavior1) behavior1->BeforeCollide(box2);
                if (behavior2) behavior2->BeforeCollide(box1);
                if (rigid1 && rigid2) {
                    int iterCount = MaxIterCount;
                    do {
                        doCollideIter(box1, box2, rigid1, rigid2, node1, node2);
                    } while (iterCount > 0 && isCollide(box1, node1->position, box2, node2->position));
                }
                if (behavior1) behavior1->AfterCollide(box2);
                if (behavior2) behavior2->AfterCollide(box1);
            }
        }
    }
}

void CollideSystem::doCollideIter(BoxColliderComponent* box1, BoxColliderComponent* box2,
                                  RigidBodyComponent* rigid1, RigidBodyComponent* rigid2,
                                  Node2DComponent* node1, Node2DComponent* node2) {
    float xOffset = std::min(node1->position.x + box1->offset.x + box1->halfWidth,
                            node2->position.x + box2->offset.x + box2->halfWidth) -
                    std::max(node1->position.x + box1->offset.x - box1->halfWidth,
                            node2->position.x + box2->offset.x - box2->halfWidth);
    float yOffset = std::min(node1->position.y + box1->offset.y + box1->halfHeight,
                            node2->position.y + box2->offset.y + box2->halfHeight) -
                    std::max(node1->position.y + box1->offset.y - box1->halfHeight,
                            node2->position.y + box2->offset.y - box2->halfHeight);
    if (xOffset > 0 && xOffset < yOffset) {
        node1->position.x -= Sign(rigid1->velocity.x) * xOffset;
        rigid1->velocity.x = 0;
        rigid1->acceleration.x = 0;
    } else if (yOffset > 0) {
        node1->position.y -= Sign(rigid1->velocity.y) * yOffset;
        rigid1->velocity.y = 0;
        rigid1->acceleration.y = 0;
    }
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

    auto center1 = box1->offset + pos1;
    auto center2 = box2->offset + pos2;

    return !(center1.x - box1->halfWidth  >= center2.x + box2->halfWidth  ||
             center1.y - box1->halfHeight >= center2.y + box2->halfHeight ||
             center1.x + box1->halfWidth  <= center2.x - box2->halfWidth  ||
             center1.y + box1->halfHeight <= center2.y - box2->halfHeight);
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