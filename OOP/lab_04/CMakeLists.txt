cmake_minimum_required(VERSION 3.1.0)

project(fnabiev_lab_04)

SET(CMAKE_CXX_COMPILER clang++)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    "forms"
)

set(HEADERS
    include/mainwindow.h

    include/MainPresenter.h
    include/MainView.h
    include/Model.h

    include/Container.h

    include/MainViewObserver.h
    include/MainViewEmitter.h

    include/MainViewKeeper.h
)

set(SOURCES
    sources/main.cc
    sources/mainwindow.cc

    sources/MainViewEmitter.cc

    sources/MainViewKeeper.cc
    sources/MainPresenter.cc
    sources/Model.cc
)

set(FORMS
    forms/mainwindow.ui
)

set(RESOURCES
    resources/fonts/fonts.qrc
    resources/icons/icons.qrc
    resources/styles/styles.qrc
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(fnabiev_lab_04
    ${HEADERS}
    ${SOURCES}
    ${FORMS}
    ${RESOURCES}
)

target_include_directories(fnabiev_lab_04
    PUBLIC
        "include"
)

target_link_libraries(fnabiev_lab_04
    Qt5::Widgets
)

