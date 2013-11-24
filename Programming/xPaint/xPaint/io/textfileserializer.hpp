#include "Serializer.hpp"
#include "Deserializer.hpp"

#include <fstream>
#include <string>

using std::string;
using std::fstream;
using std::istream;

class TextFileSerializer : public Serializer,
                           public Deserializer
{
public:

  TextFileSerializer(string const & filename);
  ~TextFileSerializer() {}

  void Write(painter::RectDrawable const *) override;
  void Write(painter::EllipseDrawable const *) override;
  void Write(painter::LineDrawable const *) override;
  void Write(painter::PolylineDrawable const *) override;
  void Write(painter::Scene const *) override;
  void Write(painter::Paint const *) override;
  void Write(painter::Color const *) override;
  void Write(painter::ImageDrawable const *) override;

  painter::Scene * ReadScene() override;

private:
  string  _fileName;
  fstream _file;

  painter::Paint ParsePaint(istream & in);
};
