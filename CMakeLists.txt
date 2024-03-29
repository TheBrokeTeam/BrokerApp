cmake_minimum_required(VERSION 3.17)
project(BrokerApp)

set(CMAKE_CXX_STANDARD 17)

add_executable(BrokerApp
        Classes/Editor.cpp
        Classes/Editor.h
        Classes/Widgets/Widget.cpp
        Classes/Widgets/Widget.h
        Classes/Contexts/Context.cpp
        Classes/Contexts/Context.h
        Classes/Widgets/MainMenuBar.cpp
        Classes/Widgets/MainMenuBar.h
        Classes/Contexts/BackTestingContext.cpp
        Classes/Contexts/BackTestingContext.h
        Classes/Widgets/DataLoader.cpp
        Classes/Widgets/DataLoader.h
        Classes/Widget+Tickables/CandleChart.cpp
        Classes/Widget+Tickables/CandleChart.h
        Classes/Contexts/Contextualizable.cpp
        Classes/Contexts/Contextualizable.h
        Classes/Widgets/Chart.cpp
        Classes/Widgets/Chart.h
        Classes/Widgets/Indicators.cpp
        Classes/Widgets/Indicators.h
        Classes/Data/Symbol.cpp
        Classes/Data/Symbol.h
        Classes/Data/DataSource.cpp
        Classes/Data/DataSource.h
        Classes/Data/BarData.cpp
        Classes/Data/BarData.h
        Classes/Data/DataManager.cpp
        Classes/Data/DataManager.h
        Classes/Tickables/Tickable.cpp
        Classes/Tickables/Tickable.h
        Classes/Tickables/Indicators/Indicator.cpp
        Classes/Tickables/Indicators/Indicator.h
        Classes/Tickables/Strategies/Strategy.cpp
        Classes/Tickables/Strategies/Strategy.h
        Classes/Data/Position.cpp
        Classes/Data/Position.h
        Classes/Data/Order.cpp
        Classes/Data/Order.h
        Classes/Tickers/Ticker.cpp
        Classes/Tickers/Ticker.h
        Classes/Data/TickData.cpp
        Classes/Data/TickData.h
        Classes/Data/BarHistory.cpp
        Classes/Data/BarHistory.h
        Classes/Helpers/PlotHelper.h
        Classes/Helpers/Utils.h
        Classes/Tickables/Indicators/SMA.cpp
        Classes/Tickables/Indicators/SMA.h
        Classes/Helpers/ImageLoader.cpp
        Classes/Helpers/ImageLoader.h Classes/Data/ReversedData.h Classes/Tickables/Indicators/Bollinger.cpp Classes/Tickables/Indicators/Bollinger.h Classes/Widgets/SimulationController.cpp Classes/Widgets/SimulationController.h Classes/Tickables/Strategies/TestStrategy.cpp Classes/Tickables/Strategies/TestStrategy.h)

###############################################################################
# FETCH CONTENT LIBS
###############################################################################

#include(FetchContent)
#
#FetchContent_Declare(curl
#        URL                    https://github.com/curl/curl/releases/download/curl-7_75_0/curl-7.75.0.tar.xz
#        URL_HASH               SHA256=fe0c49d8468249000bda75bcfdf9e30ff7e9a86d35f1a21f428d79c389d55675 # the file hash for curl-7.75.0.tar.xz
#        USES_TERMINAL_DOWNLOAD TRUE)
#FetchContent_MakeAvailable(curl)
#add_library(curl_int INTERFACE)
#target_link_libraries(curl_int INTERFACE libcurl)
#target_include_directories(curl_int INTERFACE ${curl_SOURCE_DIR}/include ${curl_BINARY_DIR}/include/curl)
#add_library(CURL::libcurl ALIAS curl_int)

#-END---FETCH CONTENT LIBS----------------------------


#--EXTERNAL ------------------
add_subdirectory(external/fmt)
add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/rapidcsv)
#add_subdirectory(external/curl)

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

if(NOT CURL_FOUND)
    message(FATAL_ERROR "CURL NOT FOUND!")
else()
    message("CURL FOUND!")
endif()

set(IMGUI_SOURCE
        external/imgui/imgui.h
        external/imgui/imstb_rectpack.h
        external/imgui/imstb_textedit.h
        external/imgui/imstb_truetype.h
        external/imgui/imgui_internal.h
        external/imgui/imconfig.h
        external/imgui/misc/cpp/imgui_stdlib.h
        external/imgui/backends/imgui_impl_glfw.h
        external/imgui/backends/imgui_impl_opengl3.h
        )

set(IMGUI_HEADER
        external/imgui/imgui.cpp
        external/imgui/misc/cpp/imgui_stdlib.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_demo.cpp
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.cpp)

add_library(imgui STATIC ${IMGUI_SOURCE} ${IMGUI_HEADER})

target_include_directories(imgui PUBLIC
        external/imgui
        external/imgui/misc/cpp
        external/imgui/backends
        )

target_link_libraries(imgui PUBLIC glfw glad)

set(IMPLOT_SOURCE
        external/implot/implot.cpp
        external/implot/implot_demo.cpp
        external/implot/implot_items.cpp
        )

set(IMPLOT_HEADER
        external/implot/implot.h
        external/implot/implot_internal.h
        )

add_library(implot STATIC ${IMPLOT_SOURCE} ${IMPLOT_HEADER})

target_include_directories(implot
        PUBLIC external/implot
        )

target_link_libraries(implot PUBLIC imgui)
#-EXTERNAL--END---------------

#-APP----------------------------
add_library(app STATIC
        Classes/App.h
        Classes/App.cpp
        Resources/Fonts/FontAwesome5.cpp
        Resources/Fonts/FontAwesome5Brands.cpp
        Resources/Fonts/Fonts.h
        Resources/Fonts/IconsFontAwesome5.h
        Resources/Fonts/IconsFontAwesome5Brands.h
        Resources/Fonts/RobotoBold.cpp
        Resources/Fonts/RobotoItalic.cpp
        Resources/Fonts/RobotoMonoBold.cpp
        Resources/Fonts/RobotoMonoItalic.cpp
        Resources/Fonts/RobotoMonoRegular.cpp
        Resources/Fonts/RobotoRegular.cpp
        )

target_include_directories(app PUBLIC
        Resources/Fonts
        Resources/
        )

target_link_libraries(app PUBLIC
        imgui
        implot
        )

#-APP-END--------------------------

#-APPLICATION-HEADERS-------------
set(INCLUDES
        Resources
        external
        external/miniz-cpp
        external/glfw/include
        external/imgui
        external/imgui/misc/cpp
        external/imgui/backends
        external/implot
        external/stb
        ${CMAKE_CURRENT_BINARY_DIR}/external/glad/include
        external/rapidcsv/src
        ${CURL_INCLUDE_DIR}
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${INCLUDES}
        )
#-APPLICATION-HEADERS-END---------

#-APPLICATION-LIBRARIES-----------------------
target_link_libraries(${PROJECT_NAME} PUBLIC
        app
        fmt
        glfw
        glad
        imgui
        implot
        rapidcsv
        curl
        )
#-APPLICATION-LIBRARIES-END-------------------

