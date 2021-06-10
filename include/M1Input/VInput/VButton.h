#if !defined(V_BUTTON_H)
#define V_BUTTON_H

class VButton {
public:
  virtual ~VButton() {}
  virtual bool isPressed() = 0;
  virtual bool isClicked() = 0;
  virtual void check() = 0;
};

#endif // V_BUTTON_H
