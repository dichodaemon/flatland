#include "ChipmunkPainter.h"
#include <flatland/Body.h>
#include <flatland/CircleShape.h>
#include <flatland/Color.h>
#include <flatland/Constraint.h>
#include <flatland/GraphicsContext.h>
#include <flatland/PolygonShape.h>
#include <flatland/SegmentShape.h>


//------------------------------------------------------------------------------

void
Flatland::ChipmunkPainter::paint(
  GraphicsContext & graphics,
  ChipmunkObject & object
)
{
  if( CircleShape * circle = dynamic_cast< CircleShape * >( &object ) )
  {
    paint( graphics, *circle );
  }
  else if ( SegmentShape * segment = dynamic_cast< SegmentShape * >( &object ) )
  {
    paint( graphics, *segment );
  }
  else if ( PolygonShape * polygon = dynamic_cast< PolygonShape * >( &object ) )
  {
    paint( graphics, *polygon );
  }
  else if ( Body * body = dynamic_cast< Body * >( &object ) )
  {
    paint( graphics, *body );
  }
  else if ( Constraint * constraint = dynamic_cast< Constraint * >( &object ) )
  {
    paint( graphics, *constraint );
  }
}

//------------------------------------------------------------------------------

void
Flatland::ChipmunkPainter::paint( GraphicsContext & graphics, Body & body )
{
  graphics.fillCircle( body.x(), body.y(), 0.1, Color( 0, 0, 255 ) );
  graphics.drawCircle( body.x(), body.y(), 0.1, Color( 100, 100, 100 ), 1 );
}

//------------------------------------------------------------------------------

void
Flatland::ChipmunkPainter::paint(
  GraphicsContext & graphics,
  CircleShape & circle
)
{
  Vector2D center = circle.worldOffset();
  graphics.drawCircle(
    center.x(), center.y(), circle.radius(), Color( 255, 255, 255 )
  );
}

//------------------------------------------------------------------------------

void
Flatland::ChipmunkPainter::paint(
  GraphicsContext & graphics,
  SegmentShape & segment
)
{
  Vector2D v1 = segment.worldV1();
  Vector2D v2 = segment.worldV2();
  graphics.drawLine( v1.x(), v1.y(), v2.x(), v2.y(), Color( 255, 255, 255 ) );
}

//------------------------------------------------------------------------------

void
Flatland::ChipmunkPainter::paint(
  GraphicsContext & graphics,
  PolygonShape & polygon
)
{
  for ( int i = 0; i < polygon.size(); ++i )
  {
    Vector2D v1 = polygon.body().toWorld( polygon.vertex( i ) );
    Vector2D v2 = polygon.body().toWorld( polygon.vertex( ( i + 1 ) % polygon.size() ) );
    graphics.drawLine( v1.x(), v1.y(), v2.x(), v2.y(), Color( 255, 255, 255 ) );
  }
}

//------------------------------------------------------------------------------

void
Flatland::ChipmunkPainter::paint(
  GraphicsContext & graphics,
  Constraint & constraint
)
{
  Vector2D v1 = constraint.body1().position();
  Vector2D v2 = constraint.body2().position();
  graphics.drawLine( v1.x(), v1.y(), v2.x(), v2.y(), Color( 255, 255, 0 ) );
}
