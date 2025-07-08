cmake_minimum_required(VERSION 3.5)

project(stc-assignment VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

message(STATUS "Using Qt version ${QT_VERSION_MAJOR}")

set(PROJECT_HEADERS
    widget.h
    Model/subjectmodel.h
    Serialization/Serialization.h
    Common/Types.h
    Dialog/adduser.h
    Dialog/seed.h
    Crc32/crc32.h
)

set(PROJECT_SOURCES
    main.cpp
    widget.cpp
    Model/subjectmodel.cpp
    Serialization/Serialization.cpp
    Common/Types.cpp
    Dialog/adduser.cpp
    Dialog/seed.cpp
    Crc32/crc32.cpp
)

set(PROJECT_UIS
    UI/widget.ui
    UI/adduser.ui
    UI/seed.ui
)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/UI
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(stc-assignment
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_UIS}
    )
    qt_finalize_executable(stc-assignment)
else()
    add_executable(stc-assignment
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_UIS}
    )
endif()

target_include_directories(stc-assignment PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(stc-assignment PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(stc-assignment PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS stc-assignment
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
