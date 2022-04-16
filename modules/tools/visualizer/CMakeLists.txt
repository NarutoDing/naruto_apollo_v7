cmake_minimum_required(VERSION 3.16)

project(modules_tools_visualizer LANGUAGES CXX)



set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -pthread -fPIC")
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)



set(CMAKE_PREFIX_PATH "~/Software_Install/qt514/5.14.1/gcc_64")
set(Qt5_DIR "${CMAKE_PREFIX_PATH}/lib/cmake/Qt5")
set(Qt5Widgets_DIR "${CMAKE_PREFIX_PATH}/lib/cmake/Qt5Widgets")
#查找Qt相关库
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5OpenGL)
find_package(Qt5Xml)
find_package(Qt5Multimedia )
find_package(Qt5MultimediaWidgets )
find_package(Qt5Designer)

#设置OPenCV相关库
#set(OpenCV_DIR ~/opencv-3.4.3/share/OpenCV)
#find_package(OpenCV REQUIRED)

#设置头文件
file(GLOB  visualizer ${PROJECT_SOURCE_DIR}/*.cc)
include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
    ${Qt5Xml_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    #~/build-naruto_apollo-Desktop_Qt_5_14_1_GCC_64bit-Debug/modules/tools/visualizer
)
#source_group("Ui" FILES ${UI_FILES} ${WRAP_FILES} )

#编译ui文件
file(GLOB UI_FILES ${PROJECT_SOURCE_DIR}/*.ui)
qt5_wrap_ui(GenerateUi ${UI_FILES})
qt5_add_resources(QrcFiles ${PROJECT_SOURCE_DIR}/res.qrc)

#可执行文件
add_executable(${PROJECT_NAME}
   ${visualizer}
   ${GenerateUi}
   ${QrcFiles}
)
#目标库链接
target_link_libraries(${PROJECT_NAME}
    cyber
    ${fastrtps}
    modules::drivers::proto::pointcloud_cc_proto
    modules::drivers::proto::radar_cc_proto
    modules::drivers::proto::sensor_image_cc_proto
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    Qt5::Multimedia
    Qt5::MultimediaWidgets
    Qt5::OpenGL
    Qt5::Designer
    -lglut
    -lGLU
    -lGL
)
