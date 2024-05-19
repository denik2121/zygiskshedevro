#ifndef NORKA_CHAMS
#define NORKA_CHAMS
#include <GLES2/gl2.h>
#include <dlfcn.h>
#include "Substrate/SubstrateHook.h"
#include "Substrate/CydiaSubstrate.h"
#include "Includes/Logger.h"
static void *handle;
static const char* shaderName;
static bool enableWallhack;
static bool enableWallhackW;
static bool enableWallhackG;
static bool enableWallhackO;
static bool enableRainbow;
static bool enableRainbow1;
static int w = 1;
static int a = 255;
bool chvms = false ;
ImVec4 clr;
bool ischamsenabled = false;
float red = 255.0f;
float gren = 0.0f;
float blue =0.0f;
float mi = 0.0f;
bool rgbchams = false;
static float r = 255.0f;
static float g = 0.0f;
static float b = 0.0f;
bool nightmode1 = false;
void SetR(int set){
    r = set;
}

void SetG(int set){
    g = set;
}

void SetB(int set){
    b = set;
}

float nightval = 0;


bool getRainbow1Enabled = false;

void setShader(const char* s) {
    handle = dlopen("libGLESv2.so", RTLD_LAZY);
    shaderName = s;
}

const char* getShader() {
    return shaderName;
}

int (*old_glGetUniformLocation)(GLuint, const GLchar *);
GLint new_glGetUniformLocation(GLuint program, const GLchar *name) {
    return old_glGetUniformLocation(program, name);
}

bool isCurrentShader(const char *shader) {
    GLint currProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
    return old_glGetUniformLocation(currProgram, shader) != -1;
}




static int selected_typechams = 0;
void (*old_glDrawElements)(GLenum mode, GLsizei count, GLenum type, const void *indices);
void new_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices) {
    old_glDrawElements(mode, count, type, indices);
    if (mode != GL_TRIANGLES || count < 1000) return;
    {
        GLint currProgram;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
        GLint id = old_glGetUniformLocation(currProgram, getShader());

        GLint currProgram2;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram2);
        GLint id2 = old_glGetUniformLocation(currProgram2, "_MainTex");

        if (id2 != -1 && id == -1) {
            if (mode != GL_TRIANGLES || count < 1) return;
            if (nightmode1) {
                glBlendColor(GLfloat(1 - float(nightval) / 100), GLfloat(1 - float(nightval) / 100),
                             GLfloat(1 - float(nightval) / 100), 0);
                glColorMask(1, 1, 1, 1);
                glEnable(GL_BLEND);
                glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
                old_glDrawElements(GL_TRIANGLES, count, type, indices);
            }
        }
        if (id == -1) {
            old_glDrawElements(mode, count, type, indices);
            return;
        }
        old_glDrawElements(mode, count, type, indices);
        if (chvms) {
            if (selected_typechams == 0) {
                glDepthRangef(1, 0.5);
                glBlendColor(GLfloat(clr.x), GLfloat(clr.z), GLfloat(clr.y), GLfloat(1));
                if (getRainbow1Enabled) {
                    glBlendColor(GLfloat(r / 255), GLfloat(g / 255), GLfloat(b / 255),
                                 GLfloat(a / 255));
                }
                glColorMask(1, 1, 1, 1);
                glEnable(GL_BLEND);
                glBlendFunc(GL_ONE_MINUS_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_ALPHA);
            }
            if (selected_typechams == 1) {
                if (chvms) {
                    glDepthRangef(1, 0.5);
                } else {
                    glDepthRangef(0.5, 1);
                }
                glBlendColor(GLfloat(clr.x), GLfloat(clr.z), GLfloat(clr.y), GLfloat(1));
                if (getRainbow1Enabled) {
                    glBlendColor(GLfloat(r / 255), GLfloat(g / 255), GLfloat(b / 255),
                                 GLfloat(a / 255));
                }
                glColorMask(1, 1, 1, 1);
                glEnable(GL_BLEND);
                glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
                glLineWidth(w);
                old_glDrawElements(GL_LINE_LOOP, count, type, indices);
            }

            if (selected_typechams == 2) {
                glEnable(GL_BLEND);
                glBlendColor(GLfloat(clr.x), GLfloat(clr.z), GLfloat(clr.y), GLfloat(1));
                if (getRainbow1Enabled) {
                    glBlendColor(GLfloat(r / 255), GLfloat(g / 255), GLfloat(b / 255),
                                 GLfloat(a / 255));
                }
                glColorMask(1, 1, 1, 1);
                glEnable(GL_BLEND);
                glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
                glLineWidth(15);

                glDepthRangef(0.5, 1);
                old_glDrawElements(GL_LINES, count, type, indices);
                glBlendColor(1, 1, 1, 1);
                glDepthRangef(1, 0.5);
                old_glDrawElements(GL_TRIANGLES, count, type, indices);
            }

            if (selected_typechams == 3) {
                glDepthRangef(1, 0.5);
                glLineWidth(20.0f);
                glEnable(GL_BLEND);
                glColorMask(1, 1, 1, 1);
                glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
                glBlendColor(0, 0, 0, 1);
                old_glDrawElements(GL_TRIANGLES, count, type, indices);
                glBlendColor(GLfloat(clr.x), GLfloat(clr.z), GLfloat(clr.y), GLfloat(1));
                if (getRainbow1Enabled) {
                    glBlendColor(GLfloat(r / 255), GLfloat(g / 255), GLfloat(b / 255),
                                 GLfloat(a / 255));
                }
                old_glDrawElements(GL_LINES, count, type, indices);
            }
            if (getRainbow1Enabled) {
                if (red == 255) {
                    if (blue == 0) {
                        if (gren == 255) {}
                        else {
                            gren = gren + 1;
                        }
                    }
                }
                if (gren == 255) {
                    if (red == 0) {}
                    else {
                        red = red - 1;
                    }
                }
                if (gren == 255) {
                    if (red == 0) {
                        if (blue == 255) {}
                        else {
                            blue = blue + 1;
                        }
                    }
                }
                if (blue == 255) {
                    if (gren == 0) {
                        mi = 1;
                        red = red + 1;
                    } else {
                        gren = gren - 1;
                    }
                }
                if (mi == 1) {
                    if (red == 255) {
                        if (blue == 0) {}
                        else {
                            blue = blue - 1;
                        }
                    }
                }
                SetR(red);
                SetG(gren);
                SetB(blue);
            }
        }
        old_glDrawElements(mode, count, type, indices);

        glDepthRangef(0.5, 1);

        glColorMask(1, 1, 1, 1);
        glDisable(GL_BLEND);
    }
}

bool mlovinit(){
    handle = NULL;
    handle = dlopen("libGLESv2.so", RTLD_LAZY);
    if(!handle){
        //LOGE("Cannot open library: %s", dlerror());
        return false;
    }
    return true;
}

void LogShaders(){
    auto p_glGetUniformLocation = (const void*(*)(...))dlsym(handle, "glGetUniformLocation");
    const char *dlsym_error = dlerror();
    if(dlsym_error){
        //LOGE("Cannot load symbol 'glGetUniformLocation': %s", dlsym_error);
        return;
    }else{
        MSHookFunction(reinterpret_cast<void*>(p_glGetUniformLocation), reinterpret_cast<void*>(new_glGetUniformLocation), reinterpret_cast<void**>(&old_glGetUniformLocation));
    }
}

void Wallhack(){
    auto p_glDrawElements = (const void*(*)(...))dlsym(handle, "glDrawElements");
    const char *dlsym_error = dlerror();
    if(dlsym_error){
        //LOGE("Cannot load symbol 'glDrawElements': %s", dlsym_error);
        return;
    }else{
        MSHookFunction(reinterpret_cast<void*>(p_glDrawElements), reinterpret_cast<void*>(new_glDrawElements), reinterpret_cast<void**>(&old_glDrawElements));
    }
}

#endif

