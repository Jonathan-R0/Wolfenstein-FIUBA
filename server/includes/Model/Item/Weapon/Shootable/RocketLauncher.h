#include "Shootable.h"

class RocketLauncher : public Shootable {
 public:
  RocketLauncher(int newAmmo);
  ~RocketLauncher();
  unsigned int shoot();
  bool outOfAmmo();
};