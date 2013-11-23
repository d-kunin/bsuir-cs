#pragma once

#include "../gem_lib/Painter/Scene.hpp"

class Deserializer
{
public:
  virtual painter::Scene * ReadScene() = 0;

  virtual ~Deserializer() {}
};
