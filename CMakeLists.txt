cmake_minimum_required(VERSION 3.23)

project(CommHelper VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 支持c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmakeconf")
# include(compiler_conf)
# 设置生文件存放目录
include(building_output)
# windeployqt
include(Windeployqt)
#获取 Git 修订说明
include(GetGitRevisionDescription)

set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
set(BUILD_BOTH_LIBS OFF CACHE INTERNAL "")
set(BUILD_DOCUMENTATION OFF CACHE INTERNAL "")
set(BUILD_MANPAGES OFF CACHE INTERNAL "")
add_subdirectory(libs/geographiclib)

add_subdirectory(libs/geos)

qt_add_executable(appCommHelper
    linkinterface.cpp
    linkinterface.h
    linkconfig.cpp
    linkconfig.h
    linktcp.cpp
    linktcp.h
    linkudp.cpp
    linkudp.h
    main.cpp
)

qt_add_qml_module(appCommHelper
    URI CommHelper
    VERSION 1.0
    QML_FILES
        Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCommHelper PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCommHelper
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCommHelper
    PRIVATE Qt6::Quick Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS appCommHelper
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
