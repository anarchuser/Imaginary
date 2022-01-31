cmake_minimum_required(VERSION 3.22.1)
project(Imaginary)

# Language specs
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++)

# Library linker flags
set(LDLIBS_GLOG "-lglog")
set(LDLIBS_OPENCV "-lopencv_core -lopencv_calib3d -lopencv_highgui -lopencv_imgproc -lopencv_stitching -lopencv_video")
set(LDLIBS_OPENCV "lopencv_core -l opencv_imgcodecs -l opencv_highgui -lopencv_photo -l opencv_videoio -l opencv_imgproc -l opencv_calib3d")

# Linker & compiler flags
set(CMAKE_REQUIRED_LIBRARIES ${LDLIBS_GLOG} ${LDLIBS_OPENCV})
set(CMAKE_CXX_FLAGS "-fconcepts")

# List source files and define target
file(GLOB_RECURSE LIBS ${PROJECT_SOURCE_DIR}/lib/*)
file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src/*)
list(REMOVE_ITEM SRCS ${PROJECT_SOURCE_DIR}/src/main.cpp)
add_executable(Imaginary ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/config.h ${SRCS} ${LIBS})

add_compile_definitions(Imaginary PROJECT_ROOT="${PROJECT_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR}/)
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_SOURCE_DIR}/src/)
include_directories(${PROJECT_SOURCE_DIR}/test/)

# Define dependencies
## Google Logging Library
target_link_libraries(Imaginary glog)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Imaginary ${OpenCV_LIBS})

# If Catch2 is installed prepare the `Test` target
find_package(Catch2 CONFIG)
IF (Catch2_FOUND)
    file(GLOB_RECURSE TEST_SRCS ${PROJECT_SOURCE_DIR}/test/*.c*)
    add_executable(Test ${GEN_PROTO_FILES} ${TEST_SRCS} ${SRCS} ${LIBS})

    add_compile_definitions(Test PRIVATE ERRORS_AS_WARNINGS)

    target_link_libraries(Test PRIVATE ${OpenCV_LIBS})

    target_link_libraries(Test PRIVATE Catch2::Catch2)
    include(CTest)
    include(Catch)
    catch_discover_tests(Test)

    target_link_libraries(Test PRIVATE glog)
ENDIF ()
