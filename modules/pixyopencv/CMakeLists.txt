FILE(GLOB SOURCE_FILES  source/*.cpp)

add_library(pixyopencv ${SOURCE_FILES})
target_link_libraries(pixyopencv ${OpenCV_LIBS})
target_link_libraries(pixyopencv libpixyusb2)
target_include_directories(pixyopencv PRIVATE include/pixyopencv)
target_include_directories(pixyopencv PUBLIC include)
