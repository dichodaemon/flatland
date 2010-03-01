#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <cstdio>
#include <cstdlib>
//Linux-specific
#include <termios.h>
#include <unistd.h>

using namespace std;

//------------------------------------------------------------------------------

int
getch()
{
  struct termios oldt,
  newt;
  int ch;
  tcgetattr( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
  return ch;
}

//------------------------------------------------------------------------------

int main( int argc, char * argv[] )
{
  ALuint buffer;
  ALuint source;
  ALfloat sourcePos[]   = { 0.0, 0.0, 0.0 };
  ALfloat sourceVel[]   = { 0.0, 0.0, 0.0 };
  ALfloat listenerPos[] = { 0.0, 0.0, 0.0 };
  ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
  ALfloat listenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

  ALenum format;
  ALsizei size;
  ALvoid * data;
  ALsizei freq;
  ALboolean loop;

  alutInit( &argc, argv );
  alGetError();


  alGenBuffers( 1, &buffer );
  if ( alGetError() != AL_NO_ERROR ) {
    fprintf( stderr, "Error creating AL buffers\n" );
    exit( 1 );
  }

  alutLoadWAVFile( "sound.wav", &format, &data, &size, &freq, &loop );
  alBufferData( buffer, format, data, size, freq );
  alutUnloadWAV( format, data, size, freq );

  alGenSources(1, &source);

  if ( alGetError() != AL_NO_ERROR ) {
    fprintf( stderr, "Error creating AL source\n" );
    exit( 1 );
  }

  alSourcei( source, AL_BUFFER, buffer );
  alSourcef( source, AL_PITCH, 1.0f );
  alSourcef( source, AL_GAIN, 1.0f );
  alSourcefv( source, AL_POSITION, sourcePos );
  alSourcefv( source, AL_VELOCITY, sourceVel );
  alSourcei( source, AL_LOOPING, loop );

  if ( alGetError() != AL_NO_ERROR )
  {
    fprintf( stderr, "Error binding AL buffer to source\n" );
    exit( 1 );
  }

  alListenerfv( AL_POSITION, listenerPos );
  alListenerfv( AL_VELOCITY, listenerVel );
  alListenerfv( AL_ORIENTATION, listenerOri );


  ALubyte c = ' ';

  while (c != 'q')
  {
    c = getch();
    switch ( c )
    {
      case 'p': alSourcePlay( source ); break;
      case 's': alSourceStop( source ); break;
      case 'h': alSourcePause( source ); break;
    };
  }


  alDeleteBuffers( 1, &buffer );
  alDeleteSources( 1, &source );
  alutExit();
}
