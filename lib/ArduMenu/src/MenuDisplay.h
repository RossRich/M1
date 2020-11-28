#if !defined(ARDUMENU_H)
#define ARDUMENU_H

#include <inttypes.h>

struct Point2 {
  uint8_t x;
  uint8_t y;
};

class MenuDisplay {
private:
public:
  MenuDisplay() {}
  virtual ~MenuDisplay() = 0;

  virtual void print(const char *st) {}
  virtual void print(uint8_t val) {}
  virtual uint8_t getHeight() const = 0;
  virtual uint8_t getWidth() const = 0;
  virtual void setCursor(uint8_t x, uint8_t y) = 0;
  virtual void setCursor(Point2 &position) = 0;
  virtual void setCursor(Point2 *position) = 0;
  virtual void clear() = 0;
};

#endif // ARDUMENU_H