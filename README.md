<p align="center">
    <img src="docs/header.jpg">
</p>
<p align="center">
    <img src="https://img.shields.io/github/license/jakerieger/MATTER?style=for-the-badge"/>
    <img src="https://img.shields.io/github/issues-raw/jakerieger/MATTER?style=for-the-badge"/>
    <img src="https://img.shields.io/github/stars/jakerieger/MATTER?style=for-the-badge"/>
    <img src="https://img.shields.io/tokei/lines/github/jakerieger/MATTER?style=for-the-badge"/>
</p>

## Another game engine?

*There are dozens of great and feature-complete game engines already available on the market today, why develop another one? Is MATTER trying to compete with those?*

Simply put, **no**. MATTER is a personal learning project being developed as a vessel for better understanding computer graphics and the physics involved in 3D game engines. I like making games, and I like programming. But more than those two things, I love challenges.

![](docs/screenshot.jpg)

## Documentation

Documentation is sparse and incomplete, but is being continuously updated. You can find it [here](https://jakerieger.github.io/MATTER).

## Project Structure

MATTER is split in to a couple different components. SOLID is the editor, LIQUID is the physics engine and PLASMA handles rendering. Any of the folders that aren't capitalized are not necessary to build and run the engine and mostly contain build chain specific scripts, config files, and documentation.

`EDITOR/` contains all the resources used by SOLID such as fonts, themes, icons, etc. The `EDITOR/resources` directory needs to be copied to the same location as the SOLID executable for the editor to run.

## Build Status

MATTER is targetting Windows **only** at the moment. Support for Unix/macOS may come in the future but is not being prioritized as OpenGL support is poor at best. Therefore, the following table is referring to the specificed compilers running on Windows 10.

|Compiler|Arch|Config|Status|
|--------|----|------|------|
|MSVC 17 |x64 |Debug|![](https://img.shields.io/badge/-passing-brightgreen?style=for-the-badge)|
|MSVC 17 |x64 |Release|![](https://img.shields.io/badge/-passing-brightgreen?style=for-the-badge)|
|MSVC 15 |x64 |Debug| - |
|MSVC 15 |x64 |Release| - |
|MinGW GCC 6|x64 |Debug| - |
|MinGW GCC 6|x64 |Release| - |

## Resources

This is a list of resources I've found helpful while developing MATTER.

- [LearnOpenGL.com](https://learnopengl.com/) - A brilliant collection of step-by-step tutorials on working with OpenGL and 3D graphics from scratch.
- [3D Rigid Body Physics Simulation](https://jonathanbosson.github.io/reports/TNM085_group5.pdf) - An excellent paper by Olle Grahn, Marcus Lilja, Jonathan Bosson, and Torsten Gustafsson on the mathematics behind simulating 3D rigidbodies.
- [Unity C# Reference](https://github.com/Unity-Technologies/UnityCsReference) - The public repository for the Unity engine's managed codebase.
- [Official Blender Mirror](https://github.com/blender/blender) - Source code for the Blender 3D modelling software
- [But How DO Soft Body Simulations Work?](https://www.youtube.com/watch?v=kyQP4t_wOGI) - An excellent and concise overview of softbody physics simulations in practice
- [Designing a Physics Engine in 5 minutes](https://www.youtube.com/watch?v=-_IspRG548E) - A high level overview of the implementation of a basic 3D rigidbody physics engine
- [Ray Marching](https://michaelwalczyk.com/blog-ray-marching.html) - An overview of the Ray Marching alrgoithm and how it can be implemented in shaders
- [BeamNG.drive Docs](https://documentation.beamng.com/) - Some nice documentation on the inner-workings of the BeamNG softbody physics engine

## Third Party Libraries

MATTER uses several third party libraries. License information can be found here: [Third Party Licenses](/EXTERNAL/licenses/).

## License

MATTER is licensed under the [Apache-2.0 license](LICENSE). All third party sources are licensed under their respective licenses detailed [here](/EXTERNAL/licenses/).
