cmake_minimum_required(VERSION 3.17)
project(BrokerApp)

set(CMAKE_CXX_STANDARD 17)

add_executable(BrokerApp
        Classes/Editor.cpp
        Classes/Editor.h
        Classes/Widgets/Widget.cpp
        Classes/Widgets/Widget.h
        Classes/Widgets/StockList.cpp
        Classes/Widgets/StockList.h
        Classes/Contexts/Context.cpp
        Classes/Contexts/Context.h
        Classes/Widgets/MainMenuBar.cpp
        Classes/Widgets/MainMenuBar.h
        Classes/Contexts/BackTestingContext.cpp
        Classes/Contexts/BackTestingContext.h
        Classes/Widgets/DownloaderView.cpp
        Classes/Widgets/DownloaderView.h
        Classes/Widgets/CandleChart.cpp
        Classes/Widgets/CandleChart.h
        Classes/Contexts/Contextualizable.cpp
        Classes/Contexts/Contextualizable.h
        Classes/Widgets/ChartView.cpp
        Classes/Widgets/ChartView.h
        Classes/Widgets/IndicatorsView.cpp
        Classes/Widgets/IndicatorsView.h
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
        Classes/Tickables/Indicators/EMA.h
        Classes/Tickables/Indicators/EMA.cpp
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
        Classes/Helpers/ImageLoader.h
        Classes/Data/ReversedData.h
        Classes/Tickables/Indicators/Bollinger.cpp
        Classes/Tickables/Indicators/Bollinger.h
        Classes/Widgets/SimulationController.cpp
        Classes/Widgets/SimulationController.h
        Classes/Tickables/Strategies/IndicatorFromChartExample.cpp
        Classes/Tickables/Strategies/IndicatorFromChartExample.h
        Classes/Widgets/ProfitAndLossesView.cpp
        Classes/Widgets/ProfitAndLossesView.h
        Classes/Widgets/PlotItem/PlotItem.cpp
        Classes/Widgets/PlotItem/PlotItem.h
        Classes/Tickables/Strategies/IndicatorToChartExample.cpp
        Classes/Tickables/Strategies/IndicatorToChartExample.h
        Classes/Widgets/StrategyEditor.cpp
        Classes/Widgets/StrategyEditor.h
        Classes/Nodes/SMANode.cpp
        Classes/Nodes/SMANode.h
        Classes/Nodes/INode.h
        Classes/Nodes/INode.cpp
        Classes/Nodes/CrossNode.cpp
        Classes/Nodes/CrossNode.h
        Classes/Nodes/Add.cpp
        Classes/Nodes/Add.h
        Classes/Nodes/Counter.cpp
        Classes/Nodes/Counter.h
        Classes/Widgets/NodesList.cpp
        Classes/Widgets/NodesList.h
        Classes/Nodes/TradeNode.cpp
        Classes/Nodes/TradeNode.h
        Classes/Tickables/Strategies/TradeNodeStrategy.cpp
        Classes/Tickables/Strategies/TradeNodeStrategy.h
        Classes/Nodes/UpSequenceNode.cpp
        Classes/Nodes/UpSequenceNode.h
        Classes/Nodes/DownSequenceNode.cpp
        Classes/Nodes/DownSequenceNode.h
        Classes/Nodes/BarValueNode.cpp
        Classes/Nodes/BarValueNode.h
        Classes/Tickables/Indicators/WMA.h
        Classes/Tickables/Indicators/WMA.cpp
        Classes/Tickables/Indicators/TRIX.cpp
        Classes/Tickables/Indicators/TRIX.h
        Classes/Tickables/Indicators/PSAR.cpp
        Classes/Tickables/Indicators/PSAR.h 
		Classes/Nodes/BollingerNode.cpp 
		Classes/Nodes/BollingerNode.h
		Classes/Tickables/Indicators/VWAP.h
		Classes/Tickables/Indicators/VWAP.cpp
		Classes/Nodes/VWAPNode.cpp
		Classes/Nodes/VWAPNode.h
		Classes/Nodes/EMANode.cpp
		Classes/Nodes/EMANode.h
		Classes/Nodes/WMANode.h
		Classes/Nodes/WMANode.cpp
		Classes/Nodes/TRIXNode.cpp
		Classes/Nodes/TRIXNode.h
        Classes/Nodes/PSARNode.cpp
        Classes/Networking/APIManager.cpp
        Classes/Networking/APIManager.h
        Classes/Networking/APIRouter.cpp
        Classes/Networking/APIRouter.h
        Classes/Networking/Routes/SymbolRouter.cpp
        Classes/Networking/Routes/SymbolRouter.h
        Classes/Networking/Routes/UserRouter.cpp
        Classes/Networking/Routes/UserRouter.h
        Classes/Networking/Services/SymbolService.cpp
        Classes/Networking/Services/SymbolService.h
        Classes/Networking/Services/UserService.cpp
        Classes/Networking/Services/UserService.h Classes/Helpers/JsonUtils.h Classes/Networking/Services/KLineService.cpp Classes/Networking/Services/KLineService.h Classes/Networking/Routes/KLineRouter.cpp Classes/Networking/Routes/KLineRouter.h
		Classes/Nodes/PSARNode.h
		Classes/Nodes/PSARNode.h 
		Classes/Nodes/IndicatorBaseNode.cpp 
		Classes/Nodes/IndicatorBaseNode.h
)

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
add_subdirectory(external/rapidjson)

#--CURL STUFF -------------------------------------------------------------
include(FindCURL)
find_package(CURL REQUIRED)
if(CURL_FOUND)
    message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
    message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
    message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")
else()
    message(FATAL_ERROR "Could not find CURL")
endif()
#--END CURL----------------------------------------------------------------

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
        external/imgui/backends/imgui_impl_opengl3.cpp Classes/Widgets/SubWidgets/DateChooser.cpp Classes/Widgets/SubWidgets/DateChooser.h Classes/Widgets/SubWidgets/BufferingBar.cpp Classes/Widgets/SubWidgets/BufferingBar.h Classes/Widgets/SubWidgets/Spinner.cpp Classes/Widgets/SubWidgets/Spinner.h)

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


set(IMNODES_SOURCE
        external/node_editor/imnodes.cpp
        )

set(IMNODES_HEADER
        external/node_editor/imnodes.h
        external/node_editor/imnodes_internal.h
        )

add_library(imnodes STATIC ${IMNODES_SOURCE} ${IMNODES_HEADER})

target_include_directories(imnodes
        PUBLIC external/node_editor
        )

target_link_libraries(imnodes PUBLIC glfw imgui)


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
        imnodes
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
        external/node_editor
        external/stb
        ${CMAKE_CURRENT_BINARY_DIR}/external/glad/include
        external/rapidcsv/src
        external/rapidjson/include
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
        imnodes
        rapidcsv
        ${CURL_LIBRARIES}
        )
#-APPLICATION-LIBRARIES-END-------------------

