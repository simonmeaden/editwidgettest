cmake_minimum_required(VERSION 3.5)

project(QYamlApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (USE_QT_VERSION EQUAL 5)
    message("QT5")
    find_package(Qt5
      REQUIRED
      COMPONENTS
        Core
        Gui
        Widgets
        Network
        Xml
        Svg
        LinguistTools
    )
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)
    include(GNUInstallDirs)
elseif(USE_QT_VERSION EQUAL 6)
    message("QT6")
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
      OPTIONAL_COMPONENTS
        Core5Compat
    )
    qt_standard_project_setup()
else()
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
      OPTIONAL_COMPONENTS
        Core5Compat
    )
    qt_standard_project_setup()
    if (NOT Qt6_FOUND)
        find_package(Qt5
          REQUIRED
          COMPONENTS
            Core
            Gui
            Widgets
            Network
            Xml
            Svg
            LinguistTools
        )
        set(CMAKE_AUTOMOC ON)
        set(CMAKE_AUTOUIC ON)
        set(CMAKE_AUTORCC ON)
        include(GNUInstallDirs)
    endif()
endif()

add_executable(qyamlapp "")

target_include_directories(qyamlapp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(qyamlapp
    PRIVATE
        -Werror
#        -DCMAKE_PREFIX_PATH=/opt/Qt/
)

target_sources(
    qyamlapp
  PRIVATE
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
)

target_compile_features(qyamlapp
    PRIVATE
        cxx_std_17
)

target_link_libraries(qyamlapp
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Xml
        Qt${QT_VERSION_MAJOR}::Svg

        Utilities::Utilities
        Widgets::Widgets
        QLNPlainText::QLNPlainText
        QYaml::QYaml
)


