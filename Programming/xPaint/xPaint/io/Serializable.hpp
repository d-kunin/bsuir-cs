#pragma once

class Serializer;

class Serializable
{
public:
  virtual void WriteTo(Serializer *) const = 0;
};
