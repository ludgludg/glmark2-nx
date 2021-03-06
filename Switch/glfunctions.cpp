
#include "log.h"
#define GL_GLES_PROTOTYPES 0
#include <EGL/egl.h>
#include <GLES2/gl2.h>

//#define NULL (void*)0

PFNGLCLEARDEPTHFPROC glClearDepthf;

PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
PFNGLBINDTEXTUREPROC glBindTexture;
PFNGLBLENDFUNCPROC glBlendFunc;
PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLBUFFERSUBDATAPROC glBufferSubData;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
PFNGLCLEARPROC glClear;
PFNGLCLEARCOLORPROC glClearColor;
PFNGLCOLORMASKPROC glColorMask;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLCULLFACEPROC glCullFace;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLDELETETEXTURESPROC glDeleteTextures;
PFNGLDEPTHFUNCPROC glDepthFunc;
PFNGLDEPTHMASKPROC glDepthMask;
PFNGLDISABLEPROC glDisable;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLDRAWARRAYSPROC glDrawArrays;
PFNGLDRAWELEMENTSPROC glDrawElements;
PFNGLENABLEPROC glEnable;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLFINISHPROC glFinish;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
PFNGLGENTEXTURESPROC glGenTextures;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLGETBOOLEANVPROC glGetBooleanv;
PFNGLGETINTEGERVPROC glGetIntegerv;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSTRINGPROC glGetString;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLISENABLEDPROC glIsEnabled;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLREADPIXELSPROC glReadPixels;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLTEXIMAGE2DPROC glTexImage2D;
PFNGLTEXPARAMETERIPROC glTexParameteri;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLUNIFORM2FVPROC glUniform2fv;
PFNGLUNIFORM3FVPROC glUniform3fv;
PFNGLUNIFORM4FVPROC glUniform4fv;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLVIEWPORTPROC glViewport;

//------------------------------------------------------------
#define LOAD_FUNCTION(p, f)              \
  f = (p)eglGetProcAddress(#f);          \
  if (f == NULL)                      \
  {                                   \
    Log::error("load function " #f "\n"); Log::flush(); \
    error = 1;                         \
  }

GL_APICALL void GL_APIENTRY empty_glClearDepthf(GLfloat d)
{

}
/*
EGLAPI EGLBoolean EGLAPIENTRY eglReleaseThread(void)
{
    return true;
}
*/
//------------------------------------------------------------
int OpenGLLoadFunctions(void)
{
    int error = GL_NO_ERROR;

    LOAD_FUNCTION(PFNGLCLEARDEPTHFPROC, glClearDepthf)

    LOAD_FUNCTION(PFNGLACTIVETEXTUREPROC, glActiveTexture)
    LOAD_FUNCTION(PFNGLATTACHSHADERPROC, glAttachShader)
    LOAD_FUNCTION(PFNGLBINDBUFFERPROC, glBindBuffer)
    LOAD_FUNCTION(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer)
    LOAD_FUNCTION(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer)
    LOAD_FUNCTION(PFNGLBINDTEXTUREPROC, glBindTexture)
    LOAD_FUNCTION(PFNGLBLENDFUNCPROC, glBlendFunc)
    LOAD_FUNCTION(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate)
    LOAD_FUNCTION(PFNGLBUFFERDATAPROC, glBufferData)
    LOAD_FUNCTION(PFNGLBUFFERSUBDATAPROC, glBufferSubData)
    LOAD_FUNCTION(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatus)
    LOAD_FUNCTION(PFNGLCLEARPROC, glClear)
    LOAD_FUNCTION(PFNGLCLEARCOLORPROC, glClearColor)
    LOAD_FUNCTION(PFNGLCOLORMASKPROC, glColorMask)
    LOAD_FUNCTION(PFNGLCOMPILESHADERPROC, glCompileShader)
    LOAD_FUNCTION(PFNGLCREATEPROGRAMPROC, glCreateProgram)
    LOAD_FUNCTION(PFNGLCREATESHADERPROC, glCreateShader)
    LOAD_FUNCTION(PFNGLCULLFACEPROC, glCullFace)
    LOAD_FUNCTION(PFNGLDELETEBUFFERSPROC, glDeleteBuffers)
    LOAD_FUNCTION(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers)
    LOAD_FUNCTION(PFNGLDELETEPROGRAMPROC, glDeleteProgram)
    LOAD_FUNCTION(PFNGLDELETERENDERBUFFERSPROC, glDeleteRenderbuffers)
    LOAD_FUNCTION(PFNGLDELETESHADERPROC, glDeleteShader)
    LOAD_FUNCTION(PFNGLDELETETEXTURESPROC, glDeleteTextures)
    LOAD_FUNCTION(PFNGLDEPTHFUNCPROC, glDepthFunc)
    LOAD_FUNCTION(PFNGLDEPTHMASKPROC, glDepthMask)
    LOAD_FUNCTION(PFNGLDISABLEPROC, glDisable)
    LOAD_FUNCTION(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray)
    LOAD_FUNCTION(PFNGLDRAWARRAYSPROC, glDrawArrays)
    LOAD_FUNCTION(PFNGLDRAWELEMENTSPROC, glDrawElements)
    LOAD_FUNCTION(PFNGLENABLEPROC, glEnable)
    LOAD_FUNCTION(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray)
    LOAD_FUNCTION(PFNGLFINISHPROC, glFinish)
    LOAD_FUNCTION(PFNGLFRAMEBUFFERRENDERBUFFERPROC, glFramebufferRenderbuffer)
    LOAD_FUNCTION(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D)
    LOAD_FUNCTION(PFNGLGENBUFFERSPROC, glGenBuffers)
    LOAD_FUNCTION(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers)
    LOAD_FUNCTION(PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffers)
    LOAD_FUNCTION(PFNGLGENTEXTURESPROC, glGenTextures)
    LOAD_FUNCTION(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap)
    LOAD_FUNCTION(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation)
    LOAD_FUNCTION(PFNGLGETBOOLEANVPROC, glGetBooleanv)
    LOAD_FUNCTION(PFNGLGETINTEGERVPROC, glGetIntegerv)
    LOAD_FUNCTION(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog)
    LOAD_FUNCTION(PFNGLGETPROGRAMIVPROC, glGetProgramiv)
    LOAD_FUNCTION(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog)
    LOAD_FUNCTION(PFNGLGETSHADERIVPROC, glGetShaderiv)
    LOAD_FUNCTION(PFNGLGETSTRINGPROC, glGetString)
    LOAD_FUNCTION(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation)
    LOAD_FUNCTION(PFNGLISENABLEDPROC, glIsEnabled)
    LOAD_FUNCTION(PFNGLLINKPROGRAMPROC, glLinkProgram)
    LOAD_FUNCTION(PFNGLREADPIXELSPROC, glReadPixels)
    LOAD_FUNCTION(PFNGLRENDERBUFFERSTORAGEPROC, glRenderbufferStorage)
    LOAD_FUNCTION(PFNGLSHADERSOURCEPROC, glShaderSource)
    LOAD_FUNCTION(PFNGLTEXIMAGE2DPROC, glTexImage2D)
    LOAD_FUNCTION(PFNGLTEXPARAMETERIPROC, glTexParameteri)
    LOAD_FUNCTION(PFNGLUNIFORM1FPROC, glUniform1f)
    LOAD_FUNCTION(PFNGLUNIFORM1IPROC, glUniform1i)
    LOAD_FUNCTION(PFNGLUNIFORM2FVPROC, glUniform2fv)
    LOAD_FUNCTION(PFNGLUNIFORM3FVPROC, glUniform3fv)
    LOAD_FUNCTION(PFNGLUNIFORM4FVPROC, glUniform4fv)
    LOAD_FUNCTION(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv)
    LOAD_FUNCTION(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv)
    LOAD_FUNCTION(PFNGLUSEPROGRAMPROC, glUseProgram)
    LOAD_FUNCTION(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer)
    LOAD_FUNCTION(PFNGLVIEWPORTPROC, glViewport)

    glClearDepthf = empty_glClearDepthf;
    return error;
}
