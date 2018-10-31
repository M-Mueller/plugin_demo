cmake_minimum_required(VERSION 3.5)

project(demo)

set(BUILD_SHARED_LIBS true)

find_package(PNG REQUIRED)

add_library(spam spam.c)
target_link_libraries(spam PUBLIC dl PNG::PNG)

add_library(foo foo.c)
target_link_libraries(foo PUBLIC spam bar)
set_target_properties(foo PROPERTIES INSTALL_RPATH "$ORIGIN:$ORIGIN/..")

add_library(bar bar.c)
target_link_libraries(bar PUBLIC spam baz)
set_target_properties(bar PROPERTIES INSTALL_RPATH "$ORIGIN:$ORIGIN/..")

add_library(baz baz.c)
target_link_libraries(baz PUBLIC spam)
set_target_properties(baz PROPERTIES INSTALL_RPATH "$ORIGIN:$ORIGIN/..")

add_executable(demo main.c)
target_link_libraries(demo PUBLIC spam)
set_target_properties(demo PROPERTIES INSTALL_RPATH "$ORIGIN/../lib")

install(TARGETS demo RUNTIME DESTINATION bin)
install(TARGETS spam LIBRARY DESTINATION lib)
install(TARGETS foo LIBRARY DESTINATION lib/spam)
install(TARGETS bar LIBRARY DESTINATION lib/spam)
install(TARGETS baz LIBRARY DESTINATION lib/spam)

