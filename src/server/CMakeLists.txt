# CMakeList.txt : CMake project for Holine, include source and define
# project specific logic here.
#

#configure_file("template/version.in"  "${CMAKE_CURRENT_SOURCE_DIR}/public/version.h")
configure_file("template/serverversion.in"  "include/serverversion.h")

add_executable (${SERVERNAME} "private/holineserver.cpp")
#set_target_properties(${EXECUTABLENAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

#include_directories("${PROJECT_TRD_DIR}/asio124/include")



target_include_directories(${SERVERNAME} PUBLIC
											 #[[holineserver.h]]
											"public"
											#[[serverversion.h]]
											"${PROJECT_BINARY_DIR}/server/include"
)



target_link_libraries(${SERVERNAME} PRIVATE CXX20_compiler_flags)




#[[
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET holine PROPERTY CXX_STANDARD 20)
endif()
]]


# TODO: Add tests and install targets if needed.

