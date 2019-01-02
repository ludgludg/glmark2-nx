/*
 * Copyright © 2010-2011 Linaro Limited
 * Copyright © 2013 Canonical Ltd
 *
 * This file is part of the glmark2 OpenGL (ES) 2.0 benchmark.
 *
 * glmark2 is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * glmark2 is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * glmark2.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *  Alexandros Frantzis
 */
#include "native-state-switch.h"
#include "log.h"

// define the folowing to redirect stdout and stderr to ethernet
//#define DEBUG_SOCKET_PORT 1962
//#define DEBUG_SOCKET_ADDR "192.168.0.100"

#define WINDOW_W 1280
#define WINDOW_H 720

/*******************
* Private methods *
*******************/
#ifdef DEBUG_SOCKET_PORT
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h> 

static int std_captured, stdout_sock, saved_stdout, saved_stderr;
#endif
//----------------------------------------------------------
// return 0 on success
static int CaptureStdout()
{
#ifdef DEBUG_SOCKET_PORT
    struct sockaddr_in srv_addr;

    if (std_captured > 0)
        return 1;

    stdout_sock = saved_stdout = saved_stderr = -1;
    if (R_FAILED(socketInitializeDefault()))
        return 1;

    stdout_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (!stdout_sock)
    {
        socketExit();
        return 1;
    }

    std_captured += 1;

    bzero(&srv_addr, sizeof srv_addr);
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = inet_addr(DEBUG_SOCKET_ADDR);
    srv_addr.sin_port = htons(DEBUG_SOCKET_PORT);

    if (connect(stdout_sock, (struct sockaddr *) &srv_addr, sizeof(srv_addr)) != 0)
    {
        close(stdout_sock);
        return 1;
    }

    // redirect stdout
    fflush(stdout);
    saved_stdout = dup(STDOUT_FILENO);
    dup2(stdout_sock, STDOUT_FILENO);
    // redirect stderr
    fflush(stderr);
    saved_stderr = dup(STDERR_FILENO);
    dup2(stdout_sock, STDERR_FILENO);
#endif

    return 0;
}

static void RestoreStdout()
{
#ifdef DEBUG_SOCKET_PORT
    struct linger linger;

    if (--std_captured)
        return;

    fflush(stdout);
    if (saved_stdout >= 0)
    {
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        saved_stdout = -1;
    }
    if (saved_stderr >= 0)
    {
        dup2(saved_stderr, STDERR_FILENO);
        close(saved_stderr);
        saved_stderr = -1;
    }
    if (stdout_sock >= 0)
    {
        shutdown(stdout_sock, SHUT_WR);

        /* set linger to 0 */
        linger.l_onoff = 1;
        linger.l_linger = 0;
        setsockopt(stdout_sock, SOL_SOCKET, SO_LINGER, &linger, sizeof(linger));

        //delay(100);
        close(stdout_sock);
        stdout_sock = -1;

        //delay(100);
        socketExit();
    }
#endif
}

/******************
 * Public methods *
 ******************/

NativeStateSwitch::NativeStateSwitch()
{
    xwin_ = 0;
    xdpy_ = false;
    properties_ = WindowProperties();
    CaptureStdout();
}

NativeStateSwitch::~NativeStateSwitch()
{
    if (xdpy_)
    {
        xdpy_ = false;
        xwin_ = 0;
    }
    RestoreStdout();
}

bool
NativeStateSwitch::init_display()
{
    if (!xdpy_)
    {
        // Uncomment below to disable error checking and save CPU time (useful for production):
        setenv("MESA_NO_ERROR", "1", 1);

        // Uncomment below to enable Mesa logging:
        setenv("EGL_LOG_LEVEL", "debug", 1);
        setenv("MESA_VERBOSE", "all", 1);
        setenv("NOUVEAU_MESA_DEBUG", "1", 1);

        // Uncomment below to enable shader debugging in Nouveau:
        //setenv("NV50_PROG_OPTIMIZE", "0", 1);
        //setenv("NV50_PROG_DEBUG", "1", 1);
        //setenv("NV50_PROG_CHIPSET", "0x120", 1); 

        xdpy_ = true;
    }
    return xdpy_;
}

void*
NativeStateSwitch::display()
{
    return EGL_DEFAULT_DISPLAY;
}

bool
NativeStateSwitch::create_window(WindowProperties const& properties)
{
    if (!xdpy_) {
        Log::error("Switch: Error: Display has not been initialized!\n");
        return false;
    }

    /* Recreate an existing window only if it has actually been resized */
    if (xwin_) {
        if (properties_.fullscreen != properties.fullscreen ||
            (properties.fullscreen == false &&
             (properties_.width != properties.width ||
              properties_.height != properties.height)))
        {
            xwin_ = 0;
        }
        else
        {
            return true;
        }
    }

    /* Set desired attributes */
    properties_ = WindowProperties(WINDOW_W, WINDOW_H, 1, properties.visual_id);

    xwin_ = nwindowGetDefault();
    return true;
}

void*
NativeStateSwitch::window(WindowProperties& properties)
{
    properties = properties_;
    return (void*)xwin_;
}

void
NativeStateSwitch::visible(bool visible)
{
//    if (visible)
//        XMapWindow(xdpy_, xwin_);
}

bool
NativeStateSwitch::should_quit()
{
u64 kDown;
    hidScanInput();
    kDown = hidKeysDown(CONTROLLER_P1_AUTO); //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame) 
    return (!appletMainLoop()) || (kDown & KEY_PLUS);
}


