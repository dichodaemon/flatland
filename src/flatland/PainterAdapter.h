#ifndef FLATLAND_PAINTER_ADAPTER_H
#define FLATLAND_PAINTER_ADAPTER_H


#include "Painter.h"


namespace Flatland
{


class GraphicsContext;


template < class T >
class PainterAdapter : public Painter
{
public:
  typedef void (T::*MemberFunction)( GraphicsContext & );

  PainterAdapter( T & instance, MemberFunction handler );

  virtual void paint( GraphicsContext & graphics );

private:
  friend class PaintQueue;
  
  T &            _object;
  MemberFunction _handler;

};


}


#include "PainterAdapter.tpp"


#endif //FLATLAND_PAINTER_ADAPTER_H
