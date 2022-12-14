add_library(service Service.hpp Service.cpp)
target_link_libraries(service PUBLIC LedLibrary)