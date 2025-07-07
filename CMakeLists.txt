cmake_minimum_required(VERSION 3.16)

project(frontend-state-remains-synchronized-with-backend VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appfrontend-state-remains-synchronized-with-backend
    main.cpp
)

qt_add_qml_module(appfrontend-state-remains-synchronized-with-backend
    URI frontend-state-remains-synchronized-with-backend
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES worker.h worker.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appfrontend-state-remains-synchronized-with-backend PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appfrontend-state-remains-synchronized-with-backend
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appfrontend-state-remains-synchronized-with-backend
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appfrontend-state-remains-synchronized-with-backend
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
