#ifndef FLATLAND_CHIPMUNK_PAINTER_H
#define FLATLAND_CHIPMUNK_PAINTER_H


namespace Flatland
{


class ChipmunkObject;
class Body;
class CircleShape;
class Constraint;
class GraphicsContext;
class PolygonShape;
class SegmentShape;


class ChipmunkPainter
{
public:
  static void paint( GraphicsContext & graphics, ChipmunkObject & object );
  static void paint( GraphicsContext & graphics, Body & body );
  static void paint( GraphicsContext & graphics, CircleShape & circle );
  static void paint( GraphicsContext & graphics, SegmentShape & segment );
  static void paint( GraphicsContext & graphics, PolygonShape & polygon );
  static void paint( GraphicsContext & graphics, Constraint & constraint );
};


}


#endif //FLATLAND_CHIPMUNK_PAINTER_H
