# minimum cmake required
cmake_minimum_required(VERSION 3.5)

# project name
project(HelloApp
        VERSION 0.0.1
        DESCRIPTION "The leading Hello World App "
        LANGUAGES CXX)
        
add_executable(HelloAppBinary cpp20.cpp)# HelloApp exename


target_compile_features(HelloAppBinary PRIVATE cxx_std_20)