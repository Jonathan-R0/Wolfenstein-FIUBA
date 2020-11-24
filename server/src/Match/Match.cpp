#include "../../includes/Match/Match.h"

#include "../Server/ClientCommunication.h"

Match::Match(int lobbyID) {
  this->lobbyID = lobbyID;
  this->playerCount = 0;
  this->running = true;
}

bool Match::hasID(int lobbyID) { return this->lobbyID = lobbyID; }

void Match::addPlayerToMatch(ClientCommunication* player) {
  this->playerCount++;

  this->players[player->ID()] = player;
  // TODO -> Agregarle al jugador la queue de comandos y de notificaciones de
  // este match
  // TODO -> Agregar a la lista de notificaciones a enviar que se añadio un
  // jugador.
}

void run() {
  // TODO -> Procesar los comandos del jugador para crear la notificacion
  // apropiada.

  // Deberia correr mientras haya jugadores vivos y/o hasta que se acabe el
  // tiempo.
}

bool Match::hasEnded() { return !running; }