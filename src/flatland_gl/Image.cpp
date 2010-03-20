#include "Image.h"
#include "soil/SOIL.h"

#if defined (__APPLE__)
  #import <OpenGL/OpenGL.h>
#elif defined ( __linux )
  #include <GL/gl.h>
#endif

//------------------------------------------------------------------------------

Image::Image()
  : _image( 0 )
{
}

//------------------------------------------------------------------------------

Image::Image( const std::string & filename )
  : _image( SOIL_load_OGL_texture(
  		filename.c_str(),
  		SOIL_LOAD_RGBA,
  		SOIL_CREATE_NEW_ID, 0//SOIL_FLAG_MULTIPLY_ALPHA
      // SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS
  	) )
{
}

//------------------------------------------------------------------------------

Image::~Image()
{  
  if ( _image != 0 ) {
    glDeleteTextures( 1, &_image );
  }
} 

//------------------------------------------------------------------------------

void 
Image::fromBuffer( const uint8_t * buffer, size_t size )
{
  _image = SOIL_load_OGL_texture_from_memory(
  		buffer,
  		size,
  		0,
  		0,
  		0
  	);
}

//------------------------------------------------------------------------------

int 
Image::index() const
{
  return _image;
}

//------------------------------------------------------------------------------

Flatland::ImageBase *
newImage()
{
  return new Image();
}

//------------------------------------------------------------------------------

Flatland::ImageBase *
newImageFromFile( const std::string & filename )
{
  return new Image( filename );
}

// /*
//  * This code was created by Jeff Molofee '99
//  * (ported to Linux/SDL by Ti Leggett '01)
//  *
//  * If you've found this code useful, please let me know.
//  *
//  * Visit Jeff at http://nehe.gamedev.net/
//  *
//  * or for port-specific comments, questions, bugreports etc.
//  * email to leggett@eecs.tulane.edu
//  */
// 
// #include <stdio.h>
// #include <stdlib.h>
// 
// #include <SDL/SDL.h>
// #include <SDL/SDL_opengles.h>
// 
// /* Include partial OpenGL ES 1.0 GLU port header */
// #define __USE_SDL_GLES__
// #include "glues.h"
// 
// /* screen width, height, and bit depth */
// #define WINDOW_WIDTH  640
// #define WINDOW_HEIGHT 480
// #define WINDOW_BPP     16
// 
// GLfloat xrot; /* X Rotation ( NEW ) */
// GLfloat yrot; /* Y Rotation ( NEW ) */
// GLfloat zrot; /* Z Rotation ( NEW ) */
// 
// GLuint texture[1]; /* Storage For One Texture ( NEW ) */
// 
// /* Array for all available keys */
// SDL_bool pressedkeys[SDL_NUM_SCANCODES];
// 
// /* SDL window */
// SDL_WindowID window;
// /* SDL GL ES context, binded to SDL window */
// SDL_GLContext glcontext=NULL;
// 
// /* function to release/destroy our resources and restoring the old desktop */
// void Quit(int returnCode)
// {
//     /* clean up the window */
//     SDL_GL_DeleteContext(glcontext);
//     SDL_DestroyWindow(window);
// 
//     SDL_Quit();
// 
//     /* and exit appropriately */
//     exit(returnCode);
// }
// 
// /* function to load in bitmap as a GL texture */
// SDL_bool LoadGLTextures()
// {
//     /* Status indicator */
//     SDL_bool status=SDL_FALSE;
// 
//     /* Create storage space for the texture */
//     SDL_Surface* TextureImage[1]; 
// 
//     /* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
//     if ((TextureImage[0]=SDL_LoadBMP( "data/nehe.bmp")))
//     {
//         /* Since OpenGL ES 1.0/1.1 has no BGRA extension we must swap R & B */
//         {
//             GLuint it;
//             GLuint jt;
// 
//             for (jt=0; jt<TextureImage[0]->h; jt++)
//             {
//                 for (it=0; it<TextureImage[0]->w; it++)
//                 {
//                     switch (TextureImage[0]->format->BytesPerPixel)
//                     {
//                         case 3: /* 24 bpp */
//                              {
//                                  unsigned char rvalue;
//                                  unsigned char bvalue;
// 
//                                  rvalue=*((unsigned char*)TextureImage[0]->pixels+
//                                      jt*TextureImage[0]->pitch+it*TextureImage[0]->format->BytesPerPixel);
//                                  bvalue=*((unsigned char*)TextureImage[0]->pixels+
//                                      jt*TextureImage[0]->pitch+it*TextureImage[0]->format->BytesPerPixel+2);
//                                  /* Convert RGB to BGR and vice versa */
//                                  *((unsigned char*)TextureImage[0]->pixels+
//                                      jt*TextureImage[0]->pitch+it*TextureImage[0]->format->BytesPerPixel)=bvalue;
//                                  *((unsigned char*)TextureImage[0]->pixels+
//                                      jt*TextureImage[0]->pitch+it*TextureImage[0]->format->BytesPerPixel+2)=rvalue;
//                              }
//                              break;
//                         case 4: /* 32 bpp */
//                              {
//                                  unsigned long rgbvalue;
// 
//                                  rgbvalue=*(unsigned long*)((unsigned char*)TextureImage[0]->pixels+
//                                      jt*TextureImage[0]->pitch+it*TextureImage[0]->format->BytesPerPixel);
//                                  /* Convert ARGB to ABGR and vice versa */
//                                  rgbvalue=(rgbvalue & 0xFF00FF00) | ((rgbvalue<<16) & 0x00FF0000) |
//                                           ((rgbvalue>>16) & 0x000000FF);
//                                  *(unsigned long*)((unsigned char*)TextureImage[0]->pixels+
//                                      jt*TextureImage[0]->pitch+it*TextureImage[0]->format->BytesPerPixel)=rgbvalue;
//                              }
//                              break;
//                     }
//                 }
//             }
//         }
// 
//         /* Set the status to true */
//         status=SDL_TRUE;
// 
//         /* Create The Texture */
//         glGenTextures(1, &texture[0]);
// 
//         /* Typical Texture Generation Using Data From The Bitmap */
//         glBindTexture(GL_TEXTURE_2D, texture[0]);
// 
//         /* Generate The Texture */
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureImage[0]->w,
//                      TextureImage[0]->h, 0, GL_RGB,
//                      GL_UNSIGNED_BYTE, TextureImage[0]->pixels);
// 
//         /* Linear Filtering */
//         glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//         glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     }
// 
//     /* Free up any memory we may have used */
//     if (TextureImage[0])
//     {
//         SDL_FreeSurface(TextureImage[0]);
//     }
// 
//     return status;
// }
// 
// /* function to reset our viewport after a window resize */
// SDL_bool resizeWindow(int width, int height)
// {
//     /* Height / width ration */
//     GLfloat ratio;
// 
//     /* Protect against a divide by zero */
//     if (height==0)
//     {
//         height = 1;
//     }
// 
//     ratio=(GLfloat)width/(GLfloat)height;
// 
//     /* Setup our viewport. */
//     glViewport(0, 0, (GLint)width, (GLint)height);
// 
//     /*
//      * change to the projection matrix and set
//      * our viewing volume.
//      */
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
// 
//     /* Set our perspective */
//     gluPerspective(45.0f, ratio, 0.1f, 100.0f);
// 
//     /* Make sure we're chaning the model view and not the projection */
//     glMatrixMode(GL_MODELVIEW);
// 
//     /* Reset The View */
//     glLoadIdentity();
// 
//     return SDL_TRUE;
// }
// 
// /* function to handle key press events */
// void handleKeyPress(SDL_keysym* keysym, SDL_bool pressed)
// {
//     if (pressed==SDL_TRUE)
//     {
//        pressedkeys[keysym->scancode]=SDL_TRUE;
//     }
//     else
//     {
//        pressedkeys[keysym->scancode]=SDL_FALSE;
//     }
// 
//     /* Handle key presses only for these keys */
//     if ((pressedkeys[SDL_SCANCODE_ESCAPE]) && (pressed))
//     {
//         Quit(0);
//     }
// }
// 
// void handleRepeatedKeys()
// {
// }
// 
// /* general OpenGL initialization function */
// SDL_bool initGL(GLvoid)
// {
//     /* Load in the texture */
//     if (!LoadGLTextures())
//     {
//         return SDL_FALSE;
//     }
// 
//     /* Enable Texture Mapping ( NEW ) */
//     glEnable(GL_TEXTURE_2D);
// 
//     /* Enable smooth shading */
//     glShadeModel(GL_SMOOTH);
// 
//     /* Set the background black */
//     glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
// 
//     /* Depth buffer setup */
//     glClearDepthf(1.0f);
// 
//     /* Enables Depth Testing */
//     glEnable(GL_DEPTH_TEST);
// 
//     /* The Type Of Depth Test To Do */
//     glDepthFunc(GL_LEQUAL);
// 
//     /* Really Nice Perspective Calculations */
//     glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
// 
//     return SDL_TRUE;
// }
// 
// /* Here goes our drawing code */
// int drawGLScene(GLvoid)
// {
//     /* These are to calculate our fps */
//     static GLint T0=0;
//     static GLint Frames=0;
//     GLfloat texcoords[4][2];
//     GLfloat vertices[4][3];
//     GLubyte indices[4]={0, 1, 3, 2}; /* QUAD to TRIANGLE_STRIP conversion; */
// 
//     /* Clear The Screen And The Depth Buffer */
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 
//     /* Move Into The Screen 5 Units */
//     glLoadIdentity();
//     glTranslatef(0.0f, 0.0f, -5.0f);
// 
//     glRotatef(xrot, 1.0f, 0.0f, 0.0f); /* Rotate On The X Axis */
//     glRotatef(yrot, 0.0f, 1.0f, 0.0f); /* Rotate On The Y Axis */
//     glRotatef(zrot, 0.0f, 0.0f, 1.0f); /* Rotate On The Z Axis */
// 
//     /* Select Our Texture */
//     glBindTexture(GL_TEXTURE_2D, texture[0]);
// 
//     /* Set pointers to vertices and texcoords */
//     glVertexPointer(3, GL_FLOAT, 0, vertices);
//     glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
// 
//     /* Enable vertices and texcoords arrays */
//     glEnableClientState(GL_VERTEX_ARRAY);
//     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
// 
//     /* Front Face */
//     texcoords[0][0]=1.0f; texcoords[0][1]=0.0f;
//     vertices[0][0]=-1.0f; vertices[0][1]=-1.0f; vertices[0][2]=1.0f;
//     texcoords[1][0]=0.0f; texcoords[1][1]=0.0f;
//     vertices[1][0]=1.0f;  vertices[1][1]=-1.0f; vertices[1][2]=1.0f;
//     texcoords[2][0]=0.0f; texcoords[2][1]=1.0f;
//     vertices[2][0]=1.0f;  vertices[2][1]=1.0f; vertices[2][2]=1.0f;
//     texcoords[3][0]=1.0f; texcoords[3][1]=1.0f;
//     vertices[3][0]=-1.0f; vertices[3][1]=1.0f; vertices[3][2]=1.0f;
// 
//     /* Draw one textured plane using two stripped triangles */
//     glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
// 
//     /* Back Face */
//     /* Normal Pointing Away From Viewer */
//     texcoords[0][0]=0.0f; texcoords[0][1]=0.0f;
//     vertices[0][0]=-1.0f; vertices[0][1]=-1.0f; vertices[0][2]=-1.0f;
//     texcoords[1][0]=0.0f; texcoords[1][1]=1.0f;
//     vertices[1][0]=-1.0f; vertices[1][1]=1.0f; vertices[1][2]=-1.0f;
//     texcoords[2][0]=1.0f; texcoords[2][1]=1.0f;
//     vertices[2][0]=1.0f;  vertices[2][1]=1.0f; vertices[2][2]=-1.0f;
//     texcoords[3][0]=1.0f; texcoords[3][1]=0.0f;
//     vertices[3][0]=1.0f; vertices[3][1]=-1.0f; vertices[3][2]=-1.0f;
// 
//     /* Draw one textured plane using two stripped triangles */
//     glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
// 
//     /* Top Face */
//     texcoords[0][0]=1.0f; texcoords[0][1]=1.0f;
//     vertices[0][0]=-1.0f; vertices[0][1]=1.0f; vertices[0][2]=-1.0f;
//     texcoords[1][0]=1.0f; texcoords[1][1]=0.0f;
//     vertices[1][0]=-1.0f; vertices[1][1]=1.0f; vertices[1][2]=1.0f;
//     texcoords[2][0]=0.0f; texcoords[2][1]=0.0f;
//     vertices[2][0]=1.0f;  vertices[2][1]=1.0f; vertices[2][2]=1.0f;
//     texcoords[3][0]=0.0f; texcoords[3][1]=1.0f;
//     vertices[3][0]=1.0f;  vertices[3][1]=1.0f; vertices[3][2]=-1.0f;
// 
//     /* Draw one textured plane using two stripped triangles */
//     glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
// 
//     /* Bottom Face */
//     texcoords[0][0]=0.0f; texcoords[0][1]=1.0f;
//     vertices[0][0]=-1.0f; vertices[0][1]=-1.0f; vertices[0][2]=-1.0f;
//     texcoords[1][0]=1.0f; texcoords[1][1]=1.0f;
//     vertices[1][0]=1.0f;  vertices[1][1]=-1.0f; vertices[1][2]=-1.0f;
//     texcoords[2][0]=1.0f; texcoords[2][1]=0.0f;
//     vertices[2][0]=1.0f;  vertices[2][1]=-1.0f; vertices[2][2]=1.0f;
//     texcoords[3][0]=0.0f; texcoords[3][1]=0.0f;
//     vertices[3][0]=-1.0f; vertices[3][1]=-1.0f; vertices[3][2]=1.0f;
// 
//     /* Draw one textured plane using two stripped triangles */
//     glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
// 
//     /* Right face */
//     texcoords[0][0]=0.0f; texcoords[0][1]=0.0f;
//     vertices[0][0]=1.0f;  vertices[0][1]=-1.0f; vertices[0][2]=-1.0f;
//     texcoords[1][0]=0.0f; texcoords[1][1]=1.0f;
//     vertices[1][0]=1.0f;  vertices[1][1]=1.0f; vertices[1][2]=-1.0f;
//     texcoords[2][0]=1.0f; texcoords[2][1]=1.0f;
//     vertices[2][0]=1.0f;  vertices[2][1]=1.0f; vertices[2][2]=1.0f;
//     texcoords[3][0]=1.0f; texcoords[3][1]=0.0f;
//     vertices[3][0]=1.0f;  vertices[3][1]=-1.0f; vertices[3][2]=1.0f;
// 
//     /* Draw one textured plane using two stripped triangles */
//     glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
// 
//     /* Left Face*/
//     texcoords[0][0]=1.0f; texcoords[0][1]=0.0f;
//     vertices[0][0]=-1.0f; vertices[0][1]=-1.0f; vertices[0][2]=-1.0f;
//     texcoords[1][0]=0.0f; texcoords[1][1]=0.0f;
//     vertices[1][0]=-1.0f; vertices[1][1]=-1.0f; vertices[1][2]=1.0f;
//     texcoords[2][0]=0.0f; texcoords[2][1]=1.0f;
//     vertices[2][0]=-1.0f; vertices[2][1]=1.0f; vertices[2][2]=1.0f;
//     texcoords[3][0]=1.0f; texcoords[3][1]=1.0f;
//     vertices[3][0]=-1.0f; vertices[3][1]=1.0f; vertices[3][2]=-1.0f;
// 
//     /* Draw one textured plane using two stripped triangles */
//     glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
// 
//     /* Disable texcoords and vertices arrays */
//     glDisableClientState(GL_NORMAL_ARRAY);
//     glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//     glDisableClientState(GL_VERTEX_ARRAY);
// 
//     /* Flush all drawings */
//     glFinish();
// 
//     /* Gather our frames per second */
//     Frames++;
//     {
//         GLint t=SDL_GetTicks();
//         if (t-T0>=5000)
//         {
//             GLfloat seconds=(t-T0)/1000.0f;
//             GLfloat fps=Frames/seconds;
//             printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
//             T0=t;
//             Frames=0;
//         }
//     }
// 
//     xrot+=0.3f; /* X Axis Rotation */
//     yrot+=0.2f; /* Y Axis Rotation */
//     zrot+=0.4f; /* Z Axis Rotation */
// 
//     return SDL_TRUE;
// }
// 
// int main(int argc, char** argv)
// {
//     int status;
// 
//     /* main loop variable */
//     SDL_bool done=SDL_FALSE;
//     /* used to collect events */
//     SDL_Event event;
//     /* whether or not the window is active */
//     SDL_bool isActive=SDL_TRUE;
// 
//     status=SDL_Init(SDL_INIT_VIDEO);
//     if (status<0)
//     {
//         fprintf(stderr, "Can't init default SDL video driver: %s\n", SDL_GetError());
//         exit(-1);
//     }
// 
//     /* Select first display */
//     status=SDL_SelectVideoDisplay(0);
//     if (status<0)
//     {
//         fprintf(stderr, "Can't attach to first display: %s\n", SDL_GetError());
//         exit(-1);
//     }
// 
//     /* Sets up OpenGL ES double buffering and visual parameters */
//     SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//     SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
//     SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
//     SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
//     SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
// 
//     window=SDL_CreateWindow("Nehe: SDL/OpenGL ES Tutorial, Lesson 06",
//         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//         WINDOW_WIDTH, WINDOW_HEIGHT,
//         SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
//     if (window==0)
//     {
//         fprintf(stderr, "Can't create window: %s\n", SDL_GetError());
//         Quit(1);
//     }
// 
//     glcontext=SDL_GL_CreateContext(window);
//     if (glcontext==NULL)
//     {
//         fprintf(stderr, "Can't create OpenGL ES context: %s\n", SDL_GetError());
//         Quit(1);
//     }
// 
//     status=SDL_GL_MakeCurrent(window, glcontext);
//     if (status<0)
//     {
//         fprintf(stderr, "Can't set current OpenGL ES context: %s\n", SDL_GetError());
//         Quit(1);
//     }
// 
//     /* Enable swap on VSYNC */
//     SDL_GL_SetSwapInterval(1);
// 
//     /* initialize OpenGL */
//     initGL();
// 
//     /* resize the initial window */
//     resizeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
// 
//     /* wait for events */
//     while (!done)
//     {
//         /* handle the events in the queue */
//         while (SDL_PollEvent(&event))
//         {
//             switch (event.type)
//             {
//                 case SDL_WINDOWEVENT:
//                      switch (event.window.event)
//                      {
//                          case SDL_WINDOWEVENT_CLOSE:
//                               done=SDL_TRUE;
//                               break;
//                          case SDL_WINDOWEVENT_HIDDEN:
//                               isActive=SDL_FALSE;
//                               break;
//                          case SDL_WINDOWEVENT_SHOWN:
//                               isActive=SDL_TRUE;
//                               break;
//                          case SDL_WINDOWEVENT_RESIZED:
//                               resizeWindow(event.window.data1, event.window.data2);
//                               break;
//                      }
//                      break;
//                 case SDL_KEYDOWN:
//                      /* handle key presses */
//                      handleKeyPress(&event.key.keysym, SDL_TRUE);
//                      break;
//                 case SDL_KEYUP:
//                      /* handle key presses */
//                      handleKeyPress(&event.key.keysym, SDL_FALSE);
//                      break;
//                 case SDL_QUIT:
//                      /* handle quit requests */
//                      done=SDL_TRUE;
//                      break;
//                 default:
//                      break;
//             }
//         }
// 
//         /* draw the scene */
//         if (isActive)
//         {
//            handleRepeatedKeys();
//            drawGLScene();
//            SDL_GL_SwapWindow(window);
//         }
//     }
// 
//     /* clean ourselves up and exit */
//     Quit(0);
// 
//     /* Should never get here */
//     return 0;
// }
