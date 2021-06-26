#if !defined(M1_VIEW_H)
#define M1_VIEW_H

#include "M1Output/DronInterface.h"
#include "ObsSubj/Observer.h"

class M1Controller;

class M1View : public Observer {
private:
  M1Controller *_mController;
  // M1Model *model;
  DronInterface *_mDi;
  // MenuManager *viewManager;

public:
  M1View() {}
  explicit M1View(M1Controller *c);
  ~M1View() {}

  void listen();

  // Observer
  void update() override;
};

#include "M1Controller.h"

#endif // M1_VIEW_H