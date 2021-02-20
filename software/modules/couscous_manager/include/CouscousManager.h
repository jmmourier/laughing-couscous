#ifndef COUSCOUS_MANAGER_H
#define COUSCOUS_MANAGER_H

#include <thread>

#include "Hali.h"
#include "Posi.h"

class CouscousManager {
   public:
    explicit CouscousManager(std::shared_ptr<Hali> hali);
    void start();

   private:
    std::shared_ptr<Posi> posi_;
    std::shared_ptr<Hali> hali_;
};

#endif  // COUSCOUS_MANAGER_H