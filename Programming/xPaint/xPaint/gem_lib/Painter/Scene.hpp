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

  void Draw(Painter * painter) override;

  RectF BoundingRect() const override;

  Drawable * FindDrawableForPoint(PointF const & p);

  void Add(Drawable * drawable);

  void Remove(Drawable * drawable);

  void MoveToFront(Drawable * drawable);

  void MoveToBack(Drawable * drawable);

  ~Scene();
};

}
