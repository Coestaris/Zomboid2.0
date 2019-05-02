# Zomboid 2.0
A small game on self-written GLUT-based game engine. Developing it just for fun...

*Zomboid 1.0 is an [previous](https://github.com/Coestaris/Zomboid) abandoned c++-written version*


#### Setup
```bash
git clone --recurse-submodules https://github.com/Coestaris/Zomboid2.0
cd Zomboid2.0
sudo apt install mesa-utils freeglut3-dev libfreetype6-dev
sudo apt install cmake # If needed
```


If you got errors like 
"***fatal error**: ft2build.h: No such file or directory*"
or
"***fatal error**: freetype/config/ftheader.h: No such file or directory*"

Use 
```bash
pkg-config --cflags freetype2 
# copy output

    vim client/CMakeList.txt 
# and past it to include_directories section 
# as space separated arguments
```

#### Build
###### To build client
```bash
cd client
cmake CMakeLists.txt 
make all
```

###### To build server
```bash
cd server
cmake CMakeLists.txt 
make all
```
