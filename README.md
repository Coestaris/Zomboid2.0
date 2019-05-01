# Zomboid 2.0
A small game on self-written GLUT-based game engine. Developing it just for fun...

*Zomboid 1.0 is an [previous](https://github.com/Coestaris/Zomboid) abandoned c++-written version*


Setup
```bash
git clone --recurse-submodules https://github.com/Coestaris/Zomboid2.0
cd Zomboid2.0
sudo apt install mesa-utils freeglut3-dev 
sudo apt install cmake # If needed
```

To build client
```bash
cd client
cmake CMakeLists.txt 
make all
```

To build server
```bash
cd server
cmake CMakeLists.txt 
make all
```
