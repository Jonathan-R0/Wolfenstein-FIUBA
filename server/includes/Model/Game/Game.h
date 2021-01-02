#ifndef __GAME_H__
#define __GAME_H__

#include <map>
#include <string>

#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../../../../common/includes/Queue/WaitingQueue.h"
#include "../../Control/Notification/Notification.h"
#include "../../../../common/includes/PlayerData.h"

class Game {
 private:
  std::map<int, Player*> players;
  Map map;

  // Deberia tener una estructura que maneje los datos del configFile de YAML

 public:
  Game(std::string mapFile, std::string configFile);

  // Agrega un jugador al mapa de los jugadores
  void addPlayer(int playerID);

  void sendUpdateMessages(WaitingQueue<Notification*>& notis);

  // Elimina a un jugador del mapa de jugadores. Tambien deberia pedirle al mapa que lo borre en sus coordenadas.
  void removePlayer(int playerID);

  void updatePositions();

  void updatePlayerMoveSpeed(int playerID, double moveSpeed);
  void updatePlayerRotationSpeed(int playerID, double rotSpeed);

  // Dispara, si colisiona con un jugador le aplica el daño.
  void playerShoot(int playerID);

  // Devuelve el ID de la pared que cambio de estado, -1 si no se modifico nada.
  int moveDoor(int playerID);

  // Comienza el juego.

  void start();

  // Termina el juego.
  void end();

  ~Game();
};

#endif
