
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

project(Cpp_design_patterns CXX)

   
add_executable(Pimpl
   pimpl.cpp
   )
   
add_executable(Class_design
   class_design.cpp
   )
   
add_executable(Singleton
   singleton.cpp
   )
   
add_executable(Visitor_classic
   visitor_classic.cpp
   )
   
add_executable(Visitor_modern
   visitor_modern.cpp
   )

add_executable(Factory_method
   factory_method.cpp
   )

add_executable(Factory_simple
   factory_simple.cpp
   )

add_executable(Bridge
   bridge.cpp
   )

set_target_properties(
   Pimpl
   Class_design
   Singleton
   Visitor_classic
   Visitor_modern
   Factory_method
   Factory_simple
   Bridge
   PROPERTIES
   EXCLUDE_FROM_ALL ON
   EXCLUDE_FROM_DEFAULT_BUILD ON
   )

