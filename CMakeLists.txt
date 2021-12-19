cmake_minimum_required(VERSION 3.17)
project(BrokerApp)

set(CMAKE_CXX_STANDARD 17)

add_executable(BrokerApp Editor.cpp Editor.h)

#--EXTERNAL ------------------
add_subdirectory(external/fmt)
add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/rapidcsv)

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
       external/imgui/backends/imgui_impl_opengl3.cpp
        )

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
        external/implot//implot.h
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
        common/App.h
        common/App.cpp
        common/Fonts/FontAwesome5.cpp
        common/Fonts/FontAwesome5Brands.cpp
        common/Fonts/Fonts.h
        common/Fonts/IconsFontAwesome5.h
        common/Fonts/IconsFontAwesome5Brands.h
        common/Fonts/RobotoBold.cpp
        common/Fonts/RobotoItalic.cpp
        common/Fonts/RobotoMonoBold.cpp
        common/Fonts/RobotoMonoItalic.cpp
        common/Fonts/RobotoMonoRegular.cpp
        common/Fonts/RobotoRegular.cpp
        )

target_include_directories(app PUBLIC
        common
        common/Fonts
        )

target_link_libraries(app PUBLIC
        imgui
        implot
        )

#-APP-END--------------------------

#-APPLICATION-HEADERS-------------
set(INCLUDES
        common
        external
        external/glfw/include
        external/imgui
        external/imgui/misc/cpp
        external/imgui/backends
        external/implot
        ${CMAKE_CURRENT_BINARY_DIR}/external/glad/include
        external/rapidcsv/src
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${INCLUDES}
        )
#-APPLICATION-HEADERS-END---------

#-APPLICATION-LIBRARIES-----------------------
target_link_libraries(${PROJECT_NAME} PUBLIC
        app
        glfw
        glad
        imgui
        implot
        rapidcsv
        )
#-APPLICATION-LIBRARIES-END-------------------

