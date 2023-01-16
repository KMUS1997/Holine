# CMakeList.txt : CMake project for Holine, include source and define
# project specific logic here.
#

#Client Version
set(CLIENTVERSION "1.0.0.1")


#configure_file("template/version.in"  "${CMAKE_CURRENT_SOURCE_DIR}/public/version.h")
configure_file("template/clientversion.in"  "include/clientversion.h")


add_executable (${CLIENTNAME} "private/holineclient.cpp")
#set_target_properties(${EXECUTABLENAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

#include_directories("${PROJECT_TRD_DIR}/asio124/include")


target_include_directories(${CLIENTNAME} PUBLIC
											 #[[holineclient.h]]
											"public"
											#[[clientversion.h]]
											"${PROJECT_BINARY_DIR}/client/include"
)

target_link_libraries(${CLIENTNAME} PRIVATE CXX20_compiler_flags)




#[[
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET holine PROPERTY CXX_STANDARD 20)
endif()
]]


# TODO: Add tests and install targets if needed.

