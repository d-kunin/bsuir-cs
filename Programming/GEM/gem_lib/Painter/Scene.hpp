#pragma once

#include "Drawable.hpp"

namespace painter {

/**
 * @brief The Scene class, hold drawables
 */
class Scene: public Drawable {

private:
  vector<Drawable*> _drawables; // no depth for now, use vector order

public:

  /**
   * @todo this is temporal solution
   *
   * @brief Drawables
   * @return
   */
  vector<Drawable*> & Drawables() {
    return _drawables;
  }

  void Draw(Painter * painter) override {
    for (Drawable * drawable : _drawables)
      drawable->Draw(painter);
  }

  ~Scene() {
    for (Drawable * drawable : _drawables)
      delete drawable;
  }

};

}
