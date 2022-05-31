#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <implot.h>
#include <imnodes.h>
#include <string>
#include <map>
#include "BrokerConfig.h"
//#include "Native.h"
#include "Fonts/Fonts.h"
//#include "Helpers.h"

//#include <cxxopts.hpp>

/// Macro to disable console on Windows
#if defined(_WIN32) && defined(APP_NO_CONSOLE)
    #pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

// Barebones Application Framework
class App
{
public:
    // Constructor.
    App(std::string title, int w, int h, int argc, char const *argv[]);
    // Destructor.
    virtual ~App();
    // Called at top of run
    virtual void start() { }
    // Update, called once per frame.
    virtual void update() { /*implement me*/ }
    // Runs the app.
    void run();
    // Get window size
    ImVec2 getWindowSize() const;
private:
    ImVec4 _clearColor;                    // background clear color
    GLFWwindow* _window;                   // GLFW window handle
    std::map<std::string,ImFont*> _fonts;  // font map
};