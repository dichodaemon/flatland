#include "Bus.h"

//------------------------------------------------------------------------------

Flatland::Bus::~Bus()
{
  HandlerMap::iterator i;
  HandlerMap::iterator iend = _handlers.end();
  for ( i = _handlers.begin(); i != iend; ++i ) {
    HandlerList::iterator j;
    HandlerList::iterator jend = i->second.end();
    for ( j = i->second.begin(); j != jend; ++j ) {
      delete *j;
    }
  }
  NamedHandlerMap::iterator j;
  NamedHandlerMap::iterator jend = _namedHandlers.end();
  for ( j = _namedHandlers.begin(); j != jend; ++j ) {
    NamedHandlerList::iterator k;
    NamedHandlerList::iterator kend = j->second.end();
    for ( k = j->second.begin(); k != kend; ++k ) {
      HandlerList::iterator l;
      HandlerList::iterator lend = k->second.end();
      for ( l = k->second.begin(); l != lend; ++l ) {
        delete *l;
      }
    }
  }
}
