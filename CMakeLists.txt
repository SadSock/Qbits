cmake_minimum_required(VERSION 3.16)

project(Qbits VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GMPXX REQUIRED IMPORTED_TARGET gmpxx)
pkg_check_modules(MPFR REQUIRED IMPORTED_TARGET mpfr)

qt_standard_project_setup()

qt_add_executable(appQbits
    main.cpp
)

qt_add_qml_module(appQbits
    URI Qbits
    VERSION 1.0
    QML_FILES Main.qml
    RESOURCES
    QML_FILES
    QML_FILES
    SOURCES
    SOURCES e11m53rawdata.h
    SOURCES e5m2rawdata.h
    SOURCES e4m3rawdata.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQbits PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQbits
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    #WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQbits
    PRIVATE Qt6::Quick PkgConfig::GMPXX PkgConfig::MPFR
)

# target_link_libraries(appQbits gmp libgmp)

include(GNUInstallDirs)
install(TARGETS appQbits
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


