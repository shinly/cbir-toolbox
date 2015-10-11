ADD_EXECUTABLE(ccgram main.cpp ColorCorrelogram.cpp ColorQuantization.cpp)
FIND_PACKAGE(OpenCV REQUIRED)
TARGET_LINK_LIBRARIES(ccgram ${OpenCV_LIBS})