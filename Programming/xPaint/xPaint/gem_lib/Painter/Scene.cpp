#include "Scene.hpp"
#include "../../io/Serializer.hpp"


namespace painter
{

void Scene::WriteTo(Serializer * serializer) const
{
  serializer->Write(this);
}

void Scene::Draw(Painter * painter)
{
  for (Drawable * drawable : _drawables)
    drawable->Draw(painter);
}

RectF Scene::BoundingRect() const
{
  RectF bRect = _drawables.front()->BoundingRect();

  for (Drawable * draw : _drawables)
    bRect.Inflate(draw->BoundingRect());

  return bRect;
}

Drawable * Scene::FindDrawableForPoint(const PointF & p)
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

void Scene::Add(Drawable * drawable)
{
  _drawables.push_back(drawable);
}

void Scene::Remove(Drawable * drawable)
{
  _drawables.erase(std::remove(_drawables.begin(), _drawables.end(), drawable), _drawables.end());
}

void Scene::MoveToFront(Drawable * drawable)
{
  // front is back of vector
  Remove(drawable);
  _drawables.push_back(drawable);
}

void Scene::MoveToBack(Drawable * drawable)
{
  // back is front of vector
  Remove(drawable);
  _drawables.insert(_drawables.begin(), drawable);
}

Scene::~Scene()
{
  for (Drawable * drawable : _drawables)
    delete drawable;
}

}
