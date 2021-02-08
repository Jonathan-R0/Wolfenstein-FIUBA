#ifndef __MATCH_LIST_H__
#define __MATCH_LIST_H__

#include <map>
#include <mutex>

#include "../Server/ClientCommunication.h"
#include "../Server/ConnectionHandler.h"
#include "Match.h"

class ClientCommunication;
class Match;

typedef std::map<int, Match*>::iterator iterator_t;

/**
 * @section DESCRIPTION
 * Class that represents the current list of matches the server is hosting.
 */
class MatchList {
 private:
  std::map<int, Match*> matches;
  void forceShutdown();
  void matchCleanup();
  std::mutex lock;

 public:
  MatchList();

  /**
   * <Tries to join a match, creates it if not found>
   *
   * @param player The clients ClientCommunication
   * @param lobbyID The lobby ID
   * @return The connection handler of the client, NULL if not possible
   */
  ConnectionHandler* joinOrCreate(ClientCommunication* player, int lobbyID);

  ~MatchList();
};

#endif
