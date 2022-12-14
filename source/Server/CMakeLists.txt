add_library(serverLib Server.hpp Server.cpp)

add_executable(server ServerMain.cpp)
target_link_libraries(server PUBLIC serverLib service pthread)