add_library(clientLib Client.cpp Client.hpp)

add_executable(client ClientMain.cpp)

target_link_libraries(client PUBLIC clientLib pthread)