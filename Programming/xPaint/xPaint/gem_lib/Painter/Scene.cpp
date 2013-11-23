#include "Scene.hpp"
#include "../../io/Serializer.hpp"


namespace painter
{

void Scene::WriteTo(Serializer * serializer) const
{
  serializer->Write(this);
}

}
