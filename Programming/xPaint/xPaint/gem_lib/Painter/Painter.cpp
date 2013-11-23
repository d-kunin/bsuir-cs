#include "Paint.hpp"
#include "../../io/Serializer.hpp"

void painter::Paint::WriteTo(Serializer * serializer) const
{
  serializer->Write(this);
}
