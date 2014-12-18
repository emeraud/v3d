#include "Camera.hpp"


Camera::Camera(Vec3Df pos, Vec3Df dir, Vec3Df up, Vec3Df right) : _pos(pos), _dir(dir), _up(up), _right(right) {
  _dir.normalize();
  _up.normalize();
  _right.normalize();
}

Vec3Df Camera::getUp() {
  return _up;
}

Vec3Df Camera::getRight() {
  return _right;
}

Vec3Df Camera::getPos() {
  return _pos;
}

Vec3Df Camera::getDir() {
  return _dir;
}

void Camera::setUp(Vec3Df up) {
  _up = up;
  _up.normalize();
}

void Camera::setRight(Vec3Df right) {
  _right = right;
  _right.normalize();
}

void Camera::setPos(Vec3Df pos) {
  _pos = pos;
}

void Camera::setDir(Vec3Df dir) {
  _dir = dir;
  _dir.normalize();
}

