#include "PaintQueue.h"
#include "GraphicsContext.h"
#include "Painter.h"

using namespace Flatland;
using namespace std;

//------------------------------------------------------------------------------

Flatland::PaintQueue::PaintQueue()
{
}

//------------------------------------------------------------------------------

Flatland::PaintQueue::~PaintQueue()
{
  Painters::iterator i;
  Painters::iterator end = _adapters.end();
  for ( i = _adapters.begin(); i != end; ++i )
  {
    delete *i;
  }
}

//------------------------------------------------------------------------------

void
Flatland::PaintQueue::addPainter( Painter & painter, double depth )
{
  _depth[&painter] = depth;
  _queue[depth].insert( &painter );
}

//------------------------------------------------------------------------------

void
Flatland::PaintQueue::removePainter( Painter & painter )
{
  double depth = _depth[&painter];
  _depth.erase( &painter );
  _queue[depth].erase( &painter );
}

//------------------------------------------------------------------------------

void
Flatland::PaintQueue::paint( GraphicsContext & context )
{
  Queue::iterator i;
  Queue::iterator iend = _queue.end();
  for ( i = _queue.begin(); i != iend; ++i ) {
    Painters::iterator j;
    Painters::iterator jend = i->second.end();
    for ( j = i->second.begin(); j != jend; ++j ) {
      (*j)->paint( context );
    }
  }
}
