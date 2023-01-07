cmake_minimum_required(VERSION 3.7)
cmake_policy(SET CMP0077 NEW)

project(HtmlEditTest VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(BUILD_SHARED_LIBS NO CACHE BOOL "Set libraries static")
#set(SMLIBRARIES_BUILD_EXAMPLES YES CACHE BOOL "Set SMlibraries build examples on/off")

message ("Using " ${USE_QT_VERSION})

#if (USE_QT_VERSION EQUAL 5)
#    message("QT5")
#    find_package(Qt5
#      REQUIRED
#      COMPONENTS
#        Core
#        Gui
#        Widgets
#        Network
#        Xml
#        Svg
#        LinguistTools
#        Concurrent
#        Sql
##      OPTIONAL_COMPONENTS
##        Zlib
#    )
#    set(CMAKE_AUTOMOC ON)
#    set(CMAKE_AUTOUIC ON)
#    set(CMAKE_AUTORCC ON)
#    include(GNUInstallDirs)
#elseif(USE_QT_VERSION EQUAL 6)
#    message("QT6")
#    find_package(Qt6
#      REQUIRED
#      COMPONENTS
#        Core
#        Gui
#        Widgets
#        Network
#        Xml
#        Svg
#        LinguistTools
#        Concurrent
#        Sql
#      OPTIONAL_COMPONENTS
#        Core5Compat
##        Zlib
#    )
#    qt_standard_project_setup()
#else()
#    find_package(Qt6
#      REQUIRED
#      COMPONENTS
#        Core
#        Gui
#        Widgets
#        Network
#        Xml
#        Svg
#        LinguistTools
#        Concurrent
#        Sql
#      OPTIONAL_COMPONENTS
#        Core5Compat
##        Zlib
#    )
#    qt_standard_project_setup()
#    if (NOT Qt6_FOUND)
#        find_package(Qt5
#          REQUIRED
#          COMPONENTS
#            Core
#            Gui
#            Widgets
#            Network
#            Xml
#            Svg
#            LinguistTools
#            Concurrent
#            Sql
##        OPTIONAL_COMPONENTS
##            Zlib
#        )
#        set(CMAKE_AUTOMOC ON)
#        set(CMAKE_AUTOUIC ON)
#        set(CMAKE_AUTORCC ON)
#        include(GNUInstallDirs)
#    endif()
#endif()

find_package(Qt6
  REQUIRED
  COMPONENTS
    Core
    Gui
    Widgets
    Network
    Xml
    Svg
    LinguistTools
    Concurrent
    Sql
  OPTIONAL_COMPONENTS
    Core5Compat
#        Zlib
)
qt_standard_project_setup()

#if (Qt5_FOUND)
#  message("Using Qt5 ")
#elseif (Qt6_FOUND)
#  message("Using Qt6 ")
#endif()



find_library(TIDY tidy REQUIRED PATHS /usr/local)
# tidy-html5 uses BUILD_SHARED_LIB rather than the standard BUILD_SHARED_LIBS
#set(BUILD_SHARED_LIB NO)
#set(SUPPORT_CONSOLE_APP NO)
#set(LIB_INSTALL_DIR CMAKE_CURRENT_BINARY_DIR)
#message("Binary install directory " ${CMAKE_CURRENT_BINARY_DIR})

#find_package(QuaZip-Qt6 PATHS /usr/local)
#find_package(yaml-cpp REQUIRED PATHS /usr/local)
#find_package(CuteLogger REQUIRED PATHS /usr/local)

# contains various libraries which should be built if
# not already found locally.
#add_subdirectory(contrib)
# My libs
add_subdirectory(libs)
# My apps
add_subdirectory(apps)
