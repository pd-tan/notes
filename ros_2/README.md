# How to build a simple package


## Creating libraries in Package A for Package B to depend on
### Package A 
1. Create the library: `add_library(Name_of_library cpp_files_needed)`
2. Make the require files enter the *install* folder: `install(DIRECTORY directory_of_files DESTINATION include)`. The *include* destiation is required fo ament/colcon
3. Export the library: `ament_export_libraries(Name_of_library)`. This will allow a ament package to be able to use the library from Package A just be depending on Package A
   
### Package B
1. In *package.xml* add:<depend>Package A</depend>
2. IN CMakeLists.txt add: `find_package(Package A)`
3. In CMakeLists.txt add: `ament_target_depend(target_from_package_b Package_A)`
## Depending on a library from a different ROS2/ament package
Assume library is called foo_library
1. In the *package.xml*: add: <depend>foo_library</depend>
2. In CMakeLists.txt add: find_package(foo_library required)
3. In CMakeLists.txt use: ament_target_dependcies(bar_target foor_library)

