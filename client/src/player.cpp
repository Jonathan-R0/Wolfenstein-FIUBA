#include "player.h"
#include "clientprotocol.h"
#include <math.h>
#include <iostream>

bool Player::hasKey() {
  return true;
  //return this->hasTheKey;
}

bool Player::isSprite() {
  return false;
}

static bool sameSign(double a, double b) {
  return ((a <= 0 && b <= 0) || (a > 0 && b > 0));
}

double Player::calculateDist(Player* other) {
  return sqrt(pow(this->x - other->x,2) + pow(this->y - other->y,2));
}

double Player::calculateDist(int otherx, int othery) {
  return sqrt(pow(this->x - otherx,2) + pow(this->y - othery,2));
}

int Player::getSoldierId(double x, double y, double dirX, double dirY) {
  double angle = atan2(this->y - y, this->x - x) * 180 / PI;
  return 1;
}

bool Player::hasThisUniqueId(int otherid){
  return false;
}

bool Player::isShooting() {
  return this->shooting;
}

bool Player::isMoving() {
  return this->moving;
}

void Player::stopMoving() {
  this->moving = false;
}

Player::Player(PlayerData& info) {
  this->x = info.posX;
  this->y = info.posY;
  this->weaponId = info.weaponID;
  this->dirX = info.dirX;
  this->dirY = info.dirY;
  this->id = 3;
  this->planeX = 0;
  this->planeY = 0;
  this->playerID = info.playerID;
  this->lives = info.lives;
  this->health = info.health;
  this->bullets = info.bullets;
  //this->score = info.score;
  this->score = 99999;
}

void Player::update(PlayerData& info) {
  this->moving = (this->x != info.posX || this->y != info.posX);
  this->healthdown = (this->health > info.health);
  this->x = info.posX;
  this->y = info.posY;
  this->dirX = info.dirX;
  this->dirY = info.dirY;
  this->lives = info.lives;
  this->health = info.health;
  this->weaponId = info.weaponID;
  this->bullets = info.bullets;
  //this->score = info.score;
  this->score /= 2;

  double oldPlaneX = planeX;
  double cosVal = cos(info.rotSpeed);
  double sinVal = sin(info.rotSpeed);

  this->planeX = (this->planeX * cosVal) - (this->planeY * sinVal);
  this->planeY = (oldPlaneX * sinVal) + (this->planeY * cosVal);
}

void Player::update(double posX, double posY, double dirX, double dirY) {
  this->x = posX;
  this->y = posY;
  this->dirX = dirX;
  this->dirY = dirY;
}

void Player::draw(TextureManager& manager, double posX, double posY, double dirX,
                  double dirY, double planeX, double planeY, double* zBuffer) {

  int width, height;
  manager.getWindowSize(&width, &height);

  double spriteX = this->x - posX;
  double spriteY = this->y - posY;

  double invDet = 1.0 / (planeX * dirY - dirX * planeY);

  double transformX = invDet * (dirY * spriteX - dirX * spriteY);
  double transformY = invDet * (-planeY * spriteX + planeX * spriteY);

  int spriteScreenX = int((width >> 1) * (1 + transformX / transformY));

  int spriteHeight = abs(int(height / (transformY)));

  int drawStartY = (height - spriteHeight) >> 1;
  if (drawStartY < 0) drawStartY = 0;
  int drawEndY = (spriteHeight + height) >> 1;
  if (drawEndY >= height) drawEndY = height - 1;

  int spriteWidth = abs(int (height / (transformY)));
  int drawStartX = (spriteScreenX - spriteWidth) >> 1;
  if (drawStartX < 0) drawStartX = 0;
  int drawEndX = spriteWidth / 2 + spriteScreenX;
  if (drawEndX >= width) drawEndX = width - 1;

  int spriteId = 3;
  /*double angle = atan2(this->dirY - dirY, this->dirX - dirX);
  if (angle < 2*PI) angle += PI;
  if (angle > 0 && angle < PI) spriteId = 10;*/

  bool sameSignX = sameSign(this->dirX, dirX);
  bool sameSignY = sameSign(this->dirY, dirY);
  bool diffSignX = !sameSignX;
  bool diffSignY = !sameSignY;


  getSoldierId(posX, posY, dirX, dirY);


  if (diffSignX && diffSignY)
    spriteId = 11;
  else if (sameSignX && diffSignY)
    spriteId = 8;
  else if (diffSignX && sameSignY)
    spriteId = 9;
  else
    spriteId = 10;

  for (int stripe = drawStartX; stripe < drawEndX; stripe++){
    int texX = int((((stripe - (spriteScreenX - (spriteWidth >> 1))) << 6) << 8) / spriteWidth) >> 8;

    if (transformY > 0 && stripe > 0 && stripe < width && transformY < zBuffer[stripe]){
      srcArea.update(texX, 0, 1, (spriteHeight < BLOCKSIZE) ? BLOCKSIZE : spriteHeight);
      destArea.update(stripe, (height - spriteHeight) >> 1, 1, spriteHeight);
      manager.render(spriteId, srcArea, destArea);
    }
  }
}

void Player::startShooting() {
  this->shooting = true;
}

void Player::stopShooting() {
  this->shooting = false;
}
