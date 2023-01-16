#CMAKE版本最低要求
cmake_minimum_required(VERSION 3.15)
# 项目名称，以及程序名称
set(PROJECTNAME "Holine")
set(SERVERNAME "holineserver")
set(CLIENTNAME "holineclient")

#设置根目录路径
get_filename_component(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
#set(PROJECT_DIR			"${CMAKE_CURRENT_SOURCE_DIR}")
set(PROJECT_BUILD_DIR		"${PROJECT_DIR}/build")
set(PROJECT_SRC_DIR			"${PROJECT_DIR}/src")
set(PROJECT_TRD_DIR			"${PROJECT_DIR}/trd")
set(PROJECT_SCRIPT_DIR		"${PROJECT_DIR}/trd")


#项目信息
project(${PROJECTNAME}	VERSION 1.0.0.1
						LANGUAGES CXX
						HOMEPAGE_URL "www.placeholder.com"
						DESCRIPTION "HANG's Game Server"
						
)


#DEBUG后缀
set(CMAKE_DEBUG_POSTFIX d)

#Interface 实现C++20编译标准
add_library(CXX20_compiler_flags INTERFACE)
target_compile_features(CXX20_compiler_flags INTERFACE cxx_std_20)


#设置如果使用gcc或者msvc
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(CXX20_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")


include_directories("${PROJECT_TRD_DIR}/asio124/include")


#添加子目录
add_subdirectory(server)
add_subdirectory(client)





#[[
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)



if(APPLE)
  set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
elseif(UNIX)
  set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
endif()


]]






