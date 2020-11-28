#ifndef WEAPON_H
#define WEAPON_H

#include "../../Player/Player.h"
class Player;

class Weapon {
 public:
  virtual void attack() = 0;
  void pickUp(Player& player);
  bool canBePickedUpBy(Player& player);
};

#endif