#include "SoundBuffer.h"

#if defined ( __APPLE__ )
  #include <AudioToolbox/AudioToolbox.h>
#endif


using namespace std;
using namespace Flatland;

//------------------------------------------------------------------------------

void loadBuffer( const std::string & filename, ALuint buffer );

//------------------------------------------------------------------------------

SoundBuffer::SoundBuffer( const std::string & filename )
{
  alGenBuffers( 1, &_buffer );
  loadBuffer( filename, _buffer );
}

//------------------------------------------------------------------------------

SoundBuffer::~SoundBuffer()
{
  alDeleteBuffers( 1, &_buffer );
}

//------------------------------------------------------------------------------
 
SoundBuffer::operator int() const
{
  return _buffer;
}

//------------------------------------------------------------------------------

int 
SoundBuffer::frequency() const
{
  ALint result;
  alGetBufferi( _buffer, AL_FREQUENCY, &result );
  return result;
}

//------------------------------------------------------------------------------

int 
SoundBuffer::size() const
{
  ALint result;
  alGetBufferi( _buffer, AL_SIZE, &result );
  return result;
}

//------------------------------------------------------------------------------

int 
SoundBuffer::bitsPerSample() const
{
  ALint result;
  alGetBufferi( _buffer, AL_BITS, &result );
  return result;
}

//------------------------------------------------------------------------------

int 
SoundBuffer::channels() const
{
  ALint result;
  alGetBufferi( _buffer, AL_CHANNELS, &result );
  return result;
}

//------------------------------------------------------------------------------

void loadBuffer( const std::string & filename, ALuint buffer )
{
#if defined( __APPLE__ )
  CFURLRef url = CFURLCreateWithFileSystemPath( 
    0, CFStringCreateWithCString( 0, filename.c_str(), 0 ), 0, false 
  );
  
  ExtAudioFileRef inputFile;
  ExtAudioFileOpenURL(url, &inputFile);

  AudioStreamBasicDescription inputFileFormat;
  
  UInt32 propSize = sizeof( AudioStreamBasicDescription );
  ExtAudioFileGetProperty( 
    inputFile, kExtAudioFileProperty_FileDataFormat, &propSize, &inputFileFormat 
  );

  AudioStreamBasicDescription outputFormat = {0};
  outputFormat.mSampleRate       = inputFileFormat.mSampleRate; 
  outputFormat.mFormatID         = kAudioFormatLinearPCM; 
  outputFormat.mFormatFlags      = kAudioFormatFlagsCanonical;
  outputFormat.mChannelsPerFrame = inputFileFormat.mChannelsPerFrame; 
  outputFormat.mBitsPerChannel   = 16;
  
  propSize = sizeof( AudioStreamBasicDescription ); 
  AudioFormatGetProperty( 
    kAudioFormatProperty_FormatInfo, 0, NULL, &propSize, &outputFormat
  );
  
  ExtAudioFileSetProperty( 
    inputFile, 
    kExtAudioFileProperty_ClientDataFormat, 
    sizeof( outputFormat ), 
    &outputFormat
  );
  
  SInt64 inputFileLengthInFrames; 
  propSize = sizeof(SInt64); 
  ExtAudioFileGetProperty(
    inputFile, 
    kExtAudioFileProperty_FileLengthFrames, 
    &propSize, 
    &inputFileLengthInFrames
  );
  
  UInt32 dataSize = ( inputFileLengthInFrames * outputFormat.mBytesPerFrame ); 
  void *theData = malloc( dataSize ); 
  AudioBufferList dataBuffer; 
  dataBuffer.mNumberBuffers = 1;
  dataBuffer.mBuffers[0].mDataByteSize = dataSize; 
  dataBuffer.mBuffers[0].mNumberChannels = outputFormat.mChannelsPerFrame;
  dataBuffer.mBuffers[0].mData = theData;
  ExtAudioFileRead( inputFile, (UInt32*)&inputFileLengthInFrames, &dataBuffer ); 
  ALenum format = ( outputFormat.mChannelsPerFrame > 1 ) ? 
                      AL_FORMAT_STEREO16 
                    : AL_FORMAT_MONO16; 
  alBufferData( buffer, format, theData, dataSize, outputFormat.mSampleRate );
  free( theData );
#endif
}
