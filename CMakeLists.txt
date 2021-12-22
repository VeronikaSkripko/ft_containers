cmake_minimum_required(VERSION 3.20)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_containers Vector/Vector.hpp ft_utils.h Vector/VectorIterator.hpp Stack/Stack.hpp Vector/ReverseIterator.hpp Map/Map.hpp Map/Pair.hpp Map/MapIterator.hpp test-map.cpp Map/Base.hpp Map/stl_tree_like.hpp)
