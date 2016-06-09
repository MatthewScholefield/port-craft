# About
Port Craft is a 2D Minecraft-inspired game focused on portability and low resource consumption. Currently it should run on Windows, Mac, and Linux, however in the future a Nintendo DS version is planned.

![Screenshot][screenshot]

# Build instructions
Here's an overview of what needs to be done:
 - Install SFML library and CMake
 - Use CMake to generate build files
 - Build Port Craft with `make`

More detailed instructions are below.
## Step one
First download Port Craft's source code to a directory. (From the command line: `git clone https://github.com/Wolfgange3311999/Port-Craft.git`)

Continue to the header below according to your OS.
### Linux
 - [Install the latest SFML][sfml-linux]
 - Install CMake with your package manager (for Ubuntu, `sudo apt-get install cmake`)
 - Build Port Craft with the following commands in the source directory:
   - `mkdir build`
   - `cd build`
   - `cmake ..`
   - `make`

Finished! (See the [`Running Port Craft`][running-port-craft] section below)

### Windows
*If you get confused or something goes wrong you can [contact me][contact] or try applying [this build tutorial][sfml-build-tutorial] to Port Craft. If using that link, make sure to only use the `Configuring your SFML build` section and ignore things that don't make sense in the context of Port Craft.*
 - [Install the latest SFML][sfml-windows] (Choose the header under `Getting started` that applies to you)
 - [Install CMake (under `Binary distributions`)][cmake-windows]
 - Launcher [CMake's GUI][cmake-gui]. There shouldn't be any options to specify and `Where to build the binaries` should be the a folder called `build` inside the Port Craft's source code. Then click `Configure` to begin creating the build files. It should ask for your IDE or compiler. Once that finishes click `Configure` again, keeping the default values. Lastly, click `Generate` to create either the IDE project files or the build files.

Finished! (See the [`Running Port Craft`][running-port-craft] section below)

# Running Port Craft
After compiling the project, the executable should work as is and resides in the `assets` folder of Port Craft's source. Currently, the game will crash if run without the assets in the same directory.

# Contact
Any questions about Port Craft?
Contact me at [matthew3311999@gmail.com](mailto://matthew3311999@gmail.com) or file an issue in the issue tracker.
[sfml-linux]:http://www.sfml-dev.org/tutorials/2.3/start-linux.php
[contact]:https://github.com/Wolfgange3311999/Port-Craft#contact
[running-port-craft]:https://github.com/Wolfgange3311999/Port-Craft#contact
[sfml-build-tutorial]:http://www.sfml-dev.org/tutorials/2.0/compile-with-cmake.php#configuring-your-sfml-build
[sfml-windows]:http://www.sfml-dev.org/tutorials/2.3/#getting-started
[cmake-windows]:https://cmake.org/download/
[cmake-gui]:https://cmake.org/runningcmake/
[screenshot]:https://raw.githubusercontent.com/Wolfgange3311999/Port-Craft/master/readme/Screenshot.png
