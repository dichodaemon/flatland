#ifndef FLATLAND_PAINT_QUEUE_H
#define FLATLAND_PAINT_QUEUE_H


#include "PainterAdapter.h"
#include <map>
#include <set>


namespace Flatland
{


class GraphicsContext;
class Painter;


class PaintQueue
{
public:
  PaintQueue();
  virtual ~PaintQueue();
  void addPainter( Painter & painter, double depth = 0 );
  void removePainter( Painter & painter );
  void paint( GraphicsContext & context );
  
  template < class T >
  void addPainter( T & instance, void (T::*method)( GraphicsContext & ), double depth = 0 );
  
  template < class T >
  void removePainter( T & instance, void (T::*method)( GraphicsContext & ) );

private:
  typedef std::map< Painter*, double > DepthIndex;
  typedef std::set< Painter * >        Painters;
  typedef std::map< double, Painters > Queue;
  typedef std::map< void *, Painters > AdapterIndex;
  DepthIndex   _depth;
  Queue        _queue;
  AdapterIndex _adapterIndex;
  Painters     _adapters;
};


}


#include "PaintQueue.tpp"


#endif //FLATLAND_PAINT_QUEUE_H