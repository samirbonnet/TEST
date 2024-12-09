MyCProject

Requirements

A C compiler (e.g., gcc)
CMake (version 3.10 or higher is recommended)
Build Instructions (Windows, Linux, macOS)

1 _ Create a new directory for the build files: mkdir build cd build

2 _ Run CMake to configure the project: cmake ..

3 _ Build the project: cmake --build .

This will create an executable called MyCProject. On Windows it might be MyCProject.exe and can be imported as a CMake Project with MS Visual Studio.

-> On linux the executable is launched with the command $ ./build/TEST after compilation

Running the Program From the build directory: ./MyCProject

Follow the menu instructions to view movies, theaters, available seats, and to book a seat.

*Technical choice of the architecture was to demonstrate minimum memory usage via bitfields and static allocation and code readability

*Program has been tested working on Visual studio 2022 and gcc 14.
