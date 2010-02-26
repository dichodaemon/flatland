class Plot
{
public:
  Plot(
    size_t x,
    size_t y,
    size_t width,
    size_t height,
    double amplitude,
    const Color & color
  ) : _x( x ),
      _y( y ),
      _width( width ),
      _height( height ),
      _amplitude( amplitude ),
      _color( color ),
      _current( 0 ),
      _queue( width )
  {
    for ( size_t i = 0; i < _width; ++i )
    {
      _queue[i] = 0;
    }
  }

  void onPlot( const TypedEvent<double> & event )
  {
    _queue[_current] = event();
    _current = ( _current + 1 ) % _width;
  }

  void paint( GraphicsContext & graphics )
  {
    graphics.clear( Color( 0, 0, 0 ) );
    for ( size_t i = 0; i < _width; ++i )
    {
      size_t x1 = ( _current + i ) % _width;
      size_t x2 = ( _current + i + 1 ) % _width;
      double y1 = _y + _queue[x1] * _height / ( 2.0 * _amplitude );
      double y2 = _y + _queue[x2] * _height / ( 2.0 * _amplitude );
      graphics.drawLine( i, y1, i + 1, y2, _color );
    }
  }

private:
  typedef std::vector<double> Queue;

  size_t _x;
  size_t _y;
  size_t _width;
  size_t _height;
  double _amplitude;
  Color  _color;
  size_t _current;
  Queue  _queue;
};

