#ifndef FLATLAND_PAINTER_H
#define FLATLAND_PAINTER_H


namespace Flatland
{


class GraphicsContext;


class Painter
{
public:
  virtual ~Painter();
  virtual void paint( GraphicsContext & graphics ) = 0;
};


}


#endif //FLATLAND_PAINTER_H
