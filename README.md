# 3D Solar System Simulation

A real-time 3D Solar System simulation developed using C++, OpenGL, GLFW, and GLM. The project represents the Sun, planets, moons, orbital paths, stars, and meteors in an interactive 3D environment.

The simulation includes camera controls, planetary animation, adjustable simulation speed, and reverse time functionality.

## Features

* 3D Solar System simulation
* Sun and planets from Mercury to Pluto
* Planetary orbital motion
* Multiple moons
* Saturn's ring
* Interactive 3D camera
* Mouse-based camera controls
* Zoom in and zoom out
* Adjustable simulation speed
* Forward and reverse time simulation
* Star field background
* Animated meteor particles
* OpenGL lighting and shading
* Circular planetary orbit paths
* Real-time animation

## Technologies Used

| Technology    | Purpose                                             |
| ------------- | --------------------------------------------------- |
| C++20         | Core programming language                           |
| OpenGL        | 3D graphics and rendering                           |
| GLFW          | Window management and input handling                |
| GLM           | Mathematics, vectors, matrices, and transformations |
| Visual Studio | Development environment                             |

## Project Structure

```text
Solar_system/
│
├── ProjectS/
│   ├── SolarSystem.cpp
│   ├── ProjectS.vcxproj
│   └── ProjectS.vcxproj.filters
│
├── ProjectS.slnx
├── .gitignore
├── .gitattributes
└── README.md
```

## Requirements

Before running the project, make sure the following are installed:

* Windows operating system
* Visual Studio
* C++ development tools
* C++20 support
* OpenGL
* GLFW
* GLM

## Installation

Clone the repository:

```bash
git clone https://github.com/SahilisSahil/Solar_system.git
```

Navigate to the project directory:

```bash
cd Solar_system
```

Open the Visual Studio solution:

```text
ProjectS.slnx
```

Build and run the project from Visual Studio.

## Controls

| Input                               | Action                       |
| ----------------------------------- | ---------------------------- |
| Mouse Wheel                         | Zoom in or out               |
| Left Mouse Button + Mouse Movement  | Rotate camera                |
| Right Mouse Button + Mouse Movement | Move camera target           |
| Up Arrow                            | Increase simulation speed    |
| Down Arrow                          | Decrease simulation speed    |
| R                                   | Reverse simulation direction |

## How the Simulation Works

Each planet has properties such as:

* Name
* Radius
* Distance from the Sun
* Orbital speed
* Color
* Ring information

The position of each planet is continuously updated according to its orbital angle.

The general concept used for the animation is:

```text
angle = angle + orbitSpeed × timeSpeed × timeDirection
```

This allows the simulation to control the speed and direction of planetary movement.

## Planetary System

The simulation includes:

* Sun
* Mercury
* Venus
* Earth
* Mars
* Jupiter
* Saturn
* Uranus
* Neptune
* Pluto

Planets are positioned at different distances from the Sun and move with different orbital speeds.

## Moons

Moons are implemented separately from the planets.

Each moon is associated with a parent planet. Its position is calculated using the position of the parent planet along with its own orbital distance and orbital angle.

This creates the effect of moons orbiting planets while the planets themselves orbit the Sun.

## Stars and Meteors

The background of the simulation contains procedurally generated stars.

The project also includes meteor particles distributed around the Solar System. Their positions, speeds, angles, and other properties are generated to create a dynamic space environment.

## Camera System

The project includes an interactive 3D camera.

The camera allows the user to:

* Rotate around the Solar System
* Move the viewing target
* Zoom in
* Zoom out
* View the Solar System from different angles

The camera system uses GLM for vector and matrix calculations.

## OpenGL Rendering

The project uses OpenGL for real-time 3D rendering.

Important rendering techniques include:

* Depth testing
* Perspective projection
* Lighting
* Smooth shading
* Material properties
* 3D transformations
* Circular orbit rendering
* Point-based star and meteor rendering

The Sun acts as the primary light source in the scene.

## Rendering of Planets

The planets and moons are represented as 3D spherical objects.

Their surfaces are generated using mathematical calculations based on latitude and longitude angles.

This creates the geometry required to display spherical celestial bodies in the OpenGL environment.

## Saturn's Ring

Saturn's ring system is generated using a circular geometry with an inner and outer radius.

The ring is positioned around Saturn and rotates along with the planetary system.

## Project Objectives

The main objectives of this project are:

1. To develop a 3D Solar System simulation using OpenGL.
2. To understand fundamental computer graphics concepts.
3. To implement 3D transformations.
4. To understand camera movement and perspective projection.
5. To implement planetary orbital motion.
6. To work with OpenGL lighting and shading.
7. To implement keyboard and mouse interaction.
8. To create a real-time animated graphics application.

## Learning Outcomes

This project provides practical experience with:

* C++ programming
* OpenGL programming
* GLFW
* GLM
* 3D coordinate systems
* Vector and matrix mathematics
* 3D transformations
* Camera systems
* Perspective projection
* Lighting and shading
* Animation
* Keyboard and mouse input
* Procedural generation

## Future Improvements

Possible improvements for future versions include:

* Realistic planet textures
* More accurate planetary sizes and distances
* Additional moons
* More detailed planetary rings
* Planet information interface
* Individual planet camera views
* Spacecraft simulation
* Improved particle effects
* Free-flight camera mode
* User-configurable simulation settings
* Improved visual effects and lighting


## License

This project is created for educational and academic purposes.

You are free to study, modify, and improve the source code for learning and experimentation.
