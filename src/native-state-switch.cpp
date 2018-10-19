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

#define WINDOW_W 1280
#define WINDOW_H 720

/*******************
* Private methods *
*******************/

/******************
 * Public methods *
 ******************/

NativeStateSwitch::~NativeStateSwitch()
{
    if (xdpy_)
    {
        xdpy_ = false;
        xwin_ = false;
    }
}

bool
NativeStateSwitch::init_display()
{
    if (!xdpy_)
    {
        // Uncomment below to disable error checking and save CPU time (useful for production):
        setenv("MESA_NO_ERROR", "1", 1);

        // Uncomment below to enable Mesa logging:
        //setenv("EGL_LOG_LEVEL", "debug", 1);
        //setenv("MESA_VERBOSE", "all", 1);
        //setenv("NOUVEAU_MESA_DEBUG", "1", 1);

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
            xwin_ = false;
        }
        else
        {
            return true;
        }
    }

    /* Set desired attributes */
    properties_ = WindowProperties(WINDOW_W, WINDOW_H, 1, properties.visual_id);

    xwin_ = true;
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


