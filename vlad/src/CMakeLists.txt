INCLUDE_DIRECTORIES(/home/sunshy/workspace/cpp/vlfeat-0.9.20/vl/)
LINK_DIRECTORIES(/home/sunshy/workspace/cpp/vlfeat-0.9.20/bin/glnxa64/)
ADD_EXECUTABLE(vlad main.cpp SiftReader.cpp Vlad.cpp)
TARGET_LINK_LIBRARIES(vlad libvl.so)
