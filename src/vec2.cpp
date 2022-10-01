#include "vec2.h"

Vec2::Vec2(){
    x = 0;
    y = 0;
}

Vec2::Vec2(float x, float y){
    this->x = x;
    this->y = y;
}

Vec2::~Vec2(){
}

Vec2 Vec2::operator+(Vec2 New_vec){
    Vec2 result;
    result.x = this->x + New_vec.x;
    result.y = this->y + New_vec.y;
    return result;
}