#include "Serializer.hpp"

#include <fstream>

class TextFileSerializer : public Serializer
{
public:

  TextFileSerializer(string const & filename);

  void Write(painter::RectDrawable const *) override;
  void Write(painter::EllipseDrawable const *) override;
  void Write(painter::LineDrawable const *) override;
  void Write(painter::PolylineDrawable const *) override;
  void Write(painter::Scene const *) override;
  void Write(painter::Paint const *) override;
  void Write(painter::Color const *) override;

private:
  string _fileName;
  std::ofstream _file;

  const string VERSION = "1";
};
