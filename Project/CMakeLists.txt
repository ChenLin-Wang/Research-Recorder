cmake_minimum_required(VERSION 3.5)

project(Research_Recorder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)

SET(QRC_FILES assets.qrc)

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

	shareddefines.h

	user.h user.cpp
	userdatacontroller.h userdatacontroller.cpp
	filecontroller.h filecontroller.cpp
	cmyfiledialog.h cmyfiledialog.cpp
	filecopyworker.h filecopyworker.cpp

	assets.qrc

        header.h header.cpp header.ui
	useradddialog.h useradddialog.cpp useradddialog.ui
	filebrowser.h filebrowser.cpp filebrowser.ui
	usereditdialog.h usereditdialog.cpp usereditdialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Research_Recorder
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Research_Recorder APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Research_Recorder SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Research_Recorder
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Research_Recorder PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Research_Recorder PRIVATE Qt6::Sql)

set_target_properties(Research_Recorder PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Research_Recorder
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Research_Recorder)
endif()
