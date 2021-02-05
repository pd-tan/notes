# How to build a simple package

## Depending on a library from a different ROS2/ament package
Assume library is called foo_library
1. In the *package.xml*: add: <depend>foo_library</depend>
2. In CMakeLists.txt add: find_package(foo_library required)
3. In CMakeLists.txt use: ament_target_dependcies(bar_target foor_library)

