#include "../../../includes/Control/Command/PlayerADown.h"
#include "../../../includes/Control/Notification/Notification.h"


PlayerADown::PlayerADown(int ID) {
  this->playerID = ID;

}

void PlayerADown::execute(WaitingQueue<Notification*>& notifications, Game& game) {
  double rotSpeed = 0.25;
  game.updatePlayerRotationSpeed(this->playerID, rotSpeed);
}