#pragma once

#include "Drawable.hpp"
#include "../Commons.hpp"
#include "../../io/Serializable.hpp"

namespace painter {

class Scene: public Drawable,
             public Serializable
{

private:
  vector<Drawable*> _drawables;

public:

  void WriteTo(Serializer *) const override;

  vector<Drawable*> & Drawables()
  {
    return _drawables;
  }

  vector<Drawable *> const & Drawables() const
  {
    return _drawables;
  }

  void Draw(Painter * painter) override
  {
    for (Drawable * drawable : _drawables)
      drawable->Draw(painter);
  }

  RectF BoundingRect() const override
  {
    RectF bRect = _drawables.front()->BoundingRect();

    for (Drawable * draw : _drawables)
      bRect.Inflate(draw->BoundingRect());

    return bRect;
  }

  Drawable * FindDrawableForPoint(PointF const & p)
  {
    if (_drawables.size() > 0)
    {
      for (int i = _drawables.size() - 1; i >= 0; --i)
      {
        Drawable * drawable = _drawables[i];
        if (drawable->Contains(p))
          return drawable;
      }
    }
    return NULL;
  }

  void Remove(Drawable * drawable)
  {
    _drawables.erase(std::remove(_drawables.begin(), _drawables.end(), drawable), _drawables.end());
  }

  ~Scene()
  {
    for (Drawable * drawable : _drawables)
      delete drawable;
  }
};

}
