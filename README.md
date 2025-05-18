# 🎮 Tank Battle Simulation

![Tank Battle Simulation](https://img.shields.io/badge/Tank%20Battle-Simulation-brightgreen)
![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![OpenGL](https://img.shields.io/badge/OpenGL-4.5-red)
![freeglut](https://img.shields.io/badge/freeglut-3.2.1-orange)
![Multiplayer](https://img.shields.io/badge/Multiplayer-UDP-blueviolet)
![License](https://img.shields.io/badge/License-MIT-green)

A high-performance 3D tank battle simulation game built with C++, OpenGL, and freeglut. Experience intense tank combat with realistic physics, multiplayer functionality, and immersive visual effects.

<p align="center">
  <img src="screenshots/gameplay.jpg" alt="Tank Battle Gameplay" width="600"/>
</p>

<!--
NOTE: Uncomment these sections after adding your gameplay GIF and YouTube video

## 🎬 Gameplay Preview

<p align="center">
  <img src="screenshots/gameplay.gif" alt="Tank Battle Gameplay GIF" width="600"/>
</p>

## 📹 Full Gameplay Video

[![Tank Battle Gameplay Video](https://img.youtube.com/vi/YOUR_VIDEO_ID/0.jpg)](https://www.youtube.com/watch?v=YOUR_VIDEO_ID)
-->

<!-- INSTRUCTIONS FOR ADDING MEDIA:
1. Create a gameplay GIF (5-10 seconds) showing an exciting moment
2. Save it as "gameplay.gif" in the screenshots folder
3. Record a 2-3 minute gameplay video and upload to YouTube
4. Replace YOUR_VIDEO_ID with your actual YouTube video ID
5. Uncomment the sections above
6. Delete these instructions
-->

## ✨ Features

### 🎯 Gameplay

- **Realistic Tank Physics**: Experience authentic tank movement with acceleration, deceleration, and terrain-based handling
- **Third-Person Camera**: Dynamic camera system that follows your tank for immersive gameplay
- **Combat Mechanics**: Engage in tactical battles with precise aiming and realistic projectile physics
- **Health System**: Monitor your tank's health and strategically avoid enemy fire
- **Game Over System**: Clear win/lose conditions with an intuitive retry mechanism

### 🌍 Environment

- **Dynamic Terrain**: Navigate through procedurally generated terrain with height variations
- **Environmental Objects**: Maneuver around trees, rocks, and other obstacles
- **Collision Detection**: Realistic collision handling between tanks, projectiles, and terrain

### 🎭 Multiplayer

- **LAN Multiplayer**: Connect with friends over local network for intense 1v1 battles
- **UDP Networking**: Low-latency communication for responsive gameplay
- **State Synchronization**: Seamless synchronization of tank positions, projectiles, and game events
- **Chat System**: Communicate with your opponent during gameplay

### 🎬 Visual Effects

- **Particle System**: Spectacular explosions, muzzle flashes, and smoke effects
- **Realistic Projectiles**: Missiles with smoke trails and realistic flight paths
- **Tank Animations**: Animated tank tracks and turret rotation
- **Retro UI**: Stylish user interface with a classic gaming aesthetic

## 🎮 Controls

| Action            | Control                   |
| ----------------- | ------------------------- |
| Move Forward      | W / Up Arrow              |
| Move Backward     | S / Down Arrow            |
| Turn Left         | A / Left Arrow            |
| Turn Right        | D / Right Arrow           |
| Aim Turret        | Mouse Movement            |
| Fire              | Left Mouse Button / Space |
| Toggle Fullscreen | F11                       |
| Show Network Menu | CTRL                      |
| Chat              | T                         |
| Exit              | Esc                       |

## 🖼️ Screenshots

<p align="center">
  <img src="screenshots/tank_model.png" alt="Tank Model" width="400"/>
  <img src="screenshots/battle.png" alt="Battle Scene" width="400"/>
</p>

<p align="center">
  <img src="screenshots/explosion.png" alt="Explosion Effect" width="400"/>
  <img src="screenshots/network_menu.png" alt="Network Menu" width="400"/>
</p>

## 🛠️ Technical Implementation

### Graphics

- **OpenGL Rendering**: Custom rendering pipeline for efficient 3D graphics
- **Custom Models**: Detailed tank models with separate components for hull, turret, and tracks
- **Particle Effects**: Advanced particle system for realistic visual effects
- **Text Rendering**: Custom text rendering system for UI elements

### Physics

- **Tank Movement**: Realistic physics for tank acceleration, deceleration, and rotation
- **Terrain Interaction**: Height-based terrain movement with slope effects
- **Projectile Ballistics**: Accurate projectile physics for realistic bullet trajectories

### Networking

- **UDP Protocol**: Fast, low-overhead networking for real-time gameplay
- **Client-Server Architecture**: Reliable connection handling with server and client roles
- **State Synchronization**: Efficient synchronization of game state between players
- **Message System**: Robust message handling for game events and player actions

## 📋 Requirements

- Windows 10/11
- C++17 compatible compiler
- OpenGL 4.5+
- freeglut 3.2.1+
- Network adapter for multiplayer functionality

## 🚀 Building and Running

1. Clone the repository:

```bash
git clone https://github.com/yourusername/tank-battle-simulation.git
cd tank-battle-simulation
```

2. Compile the project:

```bash
g++ -o EnhancedTankGame.exe EnhancedTankGame.cpp NetworkManager.cpp -lopengl32 -lglu32 -lgdi32 -lws2_32
```

3. Run the game:

```bash
./EnhancedTankGame.exe
```

## 🔄 Multiplayer Setup

### Hosting a Game

1. Launch the game
2. Press 'CTRL' to open the network menu
3. Select "Start Server"
4. Wait for a client to connect

### Joining a Game

1. Launch the game
2. Press 'CTRL' to open the network menu
3. Enter the host's IP address
4. Select "Connect to Server"

## 🧩 Project Structure

```
tank-battle-simulation/
├── EnhancedTankGame.cpp    # Main game file
├── NetworkManager.h        # Networking header
├── NetworkManager.cpp      # Networking implementation
├── external/               # External dependencies
│   └── freeglut/           # freeglut library
├── screenshots/            # Game screenshots
└── README.md               # Project documentation
```

## 🔮 Future Enhancements

- **Advanced Shader Effects**: Implementation of modern shader techniques for enhanced visuals
- **External 3D Model Loading**: Support for loading external 3D models in common formats
- **Enhanced AI**: Computer-controlled opponents for single-player mode
- **Additional Weapons**: Multiple weapon types with different damage and effects
- **Map Editor**: Custom map creation tool for designing battle arenas

## 📜 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🙏 Acknowledgements

- OpenGL for the powerful graphics API
- freeglut for the OpenGL utility toolkit
- All contributors and testers who helped improve the game

---

<p align="center">
  <i>Developed with ❤️ by Keshav Bansal & Dhruv Aggarwal</i>
</p>
