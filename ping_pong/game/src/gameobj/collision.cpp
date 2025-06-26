#include <iostream>
#include <vector>
#include <cmath>
#include "assets.hpp"

class Collider {
public:
    Vector2D offset;
    bool isTrigger = false;

    virtual bool checkCollision(const Collider* other, Vector2D position, Vector2D otherPosition) const = 0;
    virtual ~Collider() {}
};

class CircleCollider : public Collider {
public:
    float radius;

    CircleCollider(float r) : radius(r) {}

    bool checkCollision(const Collider* other, Vector2D position, Vector2D otherPosition) const override {
        // Приведение другого коллайдера к CircleCollider (простейший вариант)
        if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(other)) {
            Vector2D delta = (position + offset) - (otherPosition + circle->offset);
            float distance = delta.magnitude();
            return distance < (radius + circle->radius);
        }
        // Здесь можно добавить проверки с другими типами коллайдеров
        return false;
    }
};

struct Transform {
    Vector2D position;
    //float rotation = 0;
    Size2D size;
};

class GameObject {
public:
    Transform transform;
    Collider* collider = nullptr;

    ~GameObject() {
        delete collider;
    }
};

class PhysicsSystem {
public:
    std::vector<GameObject*> objects;

    void addObj(GameObject* obj) {
        objects.push_back(obj);
    }

    void update() {
        for (size_t i = 0; i < objects.size(); ++i) {
            for (size_t j = i + 1; j < objects.size(); ++j) {
                GameObject* a = objects[i];
                GameObject* b = objects[j];

                if (a->collider && b->collider) {
                    if (a->collider->checkCollision(b->collider, a->transform.position, b->transform.position)) {
                        std::cout << "Collision detected between objects " << i << " and " << j << std::endl;

                        // Простейшая обработка коллизии (отталкивание)
                        //if (a->rigidbody && b->rigidbody) {
                        //    Vector2D dir = (b->transform.position - a->transform.position).normalized();
                        //    a->rigidbody->addForce(dir * -50.0f);
                        //    b->rigidbody->addForce(dir * 50.0f);
                        //}
                    }
                }
            }
        }
    }
};

//int main() {
//    PhysicsSystem physics;
//
//    GameObject* ball1 = new GameObject();
//    ball1->transform.position = Vector2D(0, 0);
//    ball1->collider = new CircleCollider(1.0f);
//    physics.addObj(ball1);
//
//    GameObject* ball2 = new GameObject();
//    ball2->transform.position = Vector2D(3, 0);
//    ball2->collider = new CircleCollider(1.0f);
//    physics.addObj(ball2);
//
//    for (int i = 0; i < 60; ++i) {
//        physics.update();
//
//        std::cout << "Ball1: (" << ball1->transform.position.x << ", " << ball1->transform.position.y << ") ";
//        std::cout << "Ball2: (" << ball2->transform.position.x << ", " << ball2->transform.position.y << ")" << std::endl;
//    }
//
//    delete ball1;
//    delete ball2;
//
//    return 0;
//}
