#include "entity.h"

void Entity::debug() {
    std::printf("entity: (%d, %d)\n", this->pos.x(), this->pos.y());
}

void Player::debug() {
    std::printf("player: (%d, %d)\n", this->pos.x(), this->pos.y());
}

void Gray::debug() {
    std::printf("gray: (%d, %d)\n", this->pos.x(), this->pos.y());
}

void Hal::debug() {
    std::printf("hal: (%d, %d)\n", this->pos.x(), this->pos.y());
}

void Sniper::debug() {
    std::printf("sniper: (%d, %d)\n", this->pos.x(), this->pos.y());
}
