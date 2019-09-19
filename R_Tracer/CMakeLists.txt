cmake_minimum_required(VERSION 3.3)
project(RTracer)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Geometry.h Vec3.h Ray.h Camera.h Triangle.cpp Triangle.h parse.cpp parse.h texture.cpp texture.h quat.cpp quat.h kbsplpos.cpp kbsplpos.h kbsplrot.cpp kbsplrot.h animation.cpp animation.h Hitable.cpp Hitable.h Light.h Scene.cpp Scene.h Meshhitable.cpp Meshhitable.h ContainBox.cpp ContainBox.h Xform.h StaticXform.cpp StaticXform.h AnimatedXform.cpp AnimatedXform.h Texturetriangles.cpp Texturetriangles.h Hitablebox.h Hitable.cpp)
add_executable(RTracer ${SOURCE_FILES})