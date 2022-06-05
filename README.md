<p align="center">
    <img src="docs/header.jpg">
</p>

<hr>

## Another game engine?

*There are dozens of great and feature-complete game engines already available on the market today, why develop another one? Is MATTER trying to compete with those?*

Simply put, **no**. MATTER is a personal learning project being developed as a vessel for better understanding computer graphics and the physics involved in 3D game engines. I like making games, and I like programming. But more than those two things, I love challenges.

![](docs/screenshot.jpg)

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

## Configuring your buildchain

MATTER comes with a [script](#configuring-your-buildchain) you can run to automate the process of compiling the third party libraries and MATTER runtime and copying them to the correct locations.
Simply run:

```
$ ./configure_project.sh
```

The script will ask for the CMake generator name which you can find by running:

```
$ cmake --help
```

It'll then ask for your architecture (`x64` is the only supported one currently) and will then compile and copy all the project dependencies for you.

## Third Party Libraries

MATTER uses several third party libraries. License information can be found here: [Third Party Licenses](/EXTERNAL/licenses/).

## License

MATTER is licensed under the [ISC license](LICENSE). All third party sources are licensed under their respective licenses detailed [here](/EXTERNAL/licenses/).