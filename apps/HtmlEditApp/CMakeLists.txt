cmake_minimum_required(VERSION 3.7)

project(HtmlEditApp VERSION 0.1.0 LANGUAGES CXX)

set(QUAZIP_QT_MAJOR_VERSION 6 CACHE STRING "Qt version to use (4, 5 or 6), defaults to ${QT_VERSION_MAJOR}")

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
#      OPTIONAL_COMPONENTS
#        Core5Compatif (USE_QT_VERSION EQUAL 5)
#        message("QT5")
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
#        )
#        set(CMAKE_AUTOMOC ON)
#        set(CMAKE_AUTOUIC ON)
#        set(CMAKE_AUTORCC ON)
#        include(GNUInstallDirs)
#    elseif(USE_QT_VERSION EQUAL 6)
#        message("QT6")
#        find_package(Qt6

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
#      OPTIONAL_COMPONENTS
#        Core5Compat
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
#        )
#        set(CMAKE_AUTOMOC ON)
#        set(CMAKE_AUTOUIC ON)
#        set(CMAKE_AUTORCC ON)
#        include(GNUInstallDirs)
#    endif()
#endif()

add_executable(${PROJECT_NAME} "")

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Werror
#        -DCMAKE_PREFIX_PATH=/opt/Qt/
)

target_sources(
    ${PROJECT_NAME}
  PRIVATE
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
    src/config.h
    src/config.cpp
    src/htmleditor.h
    src/htmleditor.cpp

)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Xml
        Qt${QT_VERSION_MAJOR}::Svg

        QuaZip::QuaZip
#        QLogger::QLogger
        yaml-cpp

        Utilities::Utilities
        Docker::Docker
        QLNPlainText::QLNPlainText
        QHtml::QHtml
        QXmlEdit::QXmlEdit
        QYaml::QYaml
        QMarkdown::QMarkdown
)
