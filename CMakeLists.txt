cmake_minimum_required(VERSION 3.23)

# 在 project 之前设置 C++ 标准，这样会影响所有子项目
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置这些变量以确保子项目使用相同的 C++ 标准
set(CMAKE_CXX_STANDARD_DEFAULT 17)
set(CMAKE_CXX_STANDARD_REQUIRED_DEFAULT ON)
set(CMAKE_CXX_EXTENSIONS_DEFAULT OFF)

project(CommHelper VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

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

string(REGEX REPLACE "/W[3|4]" "/w" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_subdirectory(libs/geographiclib)
add_subdirectory(libs/geos)

qt_add_executable(CommHelper
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

qt_add_qml_module(CommHelper
    URI CommHelper
    VERSION 1.0
    QML_FILES
        Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(CommHelper PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CommHelper
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(CommHelper
    PRIVATE Qt6::Quick Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS CommHelper
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

#如果是Windows平台，则生成rc文件，还有inno setup脚本文件
set(EXAMPLE_VERSION_RC_PATH "")
if(WIN32)
    set(EXAMPLE_VERSION_RC_PATH ${CMAKE_CURRENT_BINARY_DIR}/version_${PROJECT_NAME}.rc)
    set(PROJECT_ICON ${CMAKE_CURRENT_SOURCE_DIR}/resources/app.ico)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake-in/version_exe.rc.in
        ${EXAMPLE_VERSION_RC_PATH}
    )

    set(BUILD_EXE_NAME ${PROJECT_NAME}.exe)
    set(BUILD_EXE_DIR ${CMAKE_BINARY_DIR}/build)
    set(BUILD_ICON_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resources/app.ico)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake-in/InstallerScript.iss.in
        ${CMAKE_CURRENT_SOURCE_DIR}/workflows/action-cli/InstallerScript.iss
    )
endif()
#如果是Windows平台，则生成rc文件，还有inno setup脚本文件
set(EXAMPLE_VERSION_RC_PATH "")
if(WIN32)
    set(EXAMPLE_VERSION_RC_PATH ${CMAKE_CURRENT_BINARY_DIR}/version_${PROJECT_NAME}.rc)
    set(PROJECT_ICON ${CMAKE_CURRENT_SOURCE_DIR}/resources/app.ico)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake-in/version_exe.rc.in
        ${EXAMPLE_VERSION_RC_PATH}
    )

    set(BUILD_EXE_NAME ${PROJECT_NAME}.exe)
    set(BUILD_EXE_DIR ${CMAKE_BINARY_DIR}/build)
    set(BUILD_ICON_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resources/app.ico)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake-in/InstallerScript.iss.in
        ${CMAKE_CURRENT_SOURCE_DIR}/workflows/action-cli/InstallerScript.iss
    )
endif()


# 拷贝qt自身所依赖库
if(WIN32)
    windeployqt(CommHelper "CommHelper.exe" ${CMAKE_CURRENT_SOURCE_DIR})
endif()

