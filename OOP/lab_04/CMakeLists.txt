cmake_minimum_required(VERSION 3.1.0)

project(fnabiev_lab_04)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -g3 -fsanitize=address,undefined -fno-omit-frame-pointer")

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
    include/HashTable.h

    include/MainViewObserver.h
    include/MainViewEmitter.h
    include/MainViewKeeper.h

    include/Canvas.h
    include/DrawObject.h
    include/CanvasLine.h

    include/Scene.h

    include/Point3d.h
    include/Edge3d.h
    include/WireFrameModel.h
    include/WFMIterator.h

    include/WFMReaderBase.h
    include/WFMReader.h
    include/WFMBuilderBase.h
    include/WFMBuilder.h
    include/WFMBuildManager.h

    include/Exception.h
)

set(SOURCES
    source/main.cc
    source/mainwindow.cc

    source/MainViewEmitter.cc

    source/MainViewKeeper.cc
    source/MainPresenter.cc
    source/Model.cc

    source/Canvas.cc
    source/CanvasLine.cc

    source/Scene.cc

    source/Point3d.cc
    source/Edge3d.cc
    source/WireFrameModel.cc

    source/WFMReader.cc
    source/WFMBuilder.cc
    source/WFMBuildManager.cc

    source/Exception.cc
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

