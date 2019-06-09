# Zomboid 2.0
A small game on self-written GLUT-based game engine. Developing it just for fun...

*Zomboid 1.0 is an [previous](https://github.com/Coestaris/Zomboid) abandoned c++-written version*


#### Setup
```bash
git clone --recurse-submodules https://github.com/Coestaris/Zomboid2.0
cd Zomboid2.0
sudo apt install mesa-utils freeglut3-dev libfreetype6-dev libxi-dev
sudo apt install make cmake # If needed
```

#### Build
###### To build client
```bash
cd client
cmake CMakeLists.txt 
make all
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

###### To build server
```bash
cd server
cmake CMakeLists.txt 
make all
```

####Some screenshots

![1](https://user-images.githubusercontent.com/19210828/58269521-6d0f6980-7d90-11e9-8c74-d1e73835c65c.png)

![2](https://user-images.githubusercontent.com/19210828/58269523-6d0f6980-7d90-11e9-9116-4a2623f0a2ef.png)

![3](https://user-images.githubusercontent.com/19210828/58269519-6d0f6980-7d90-11e9-8ae2-23cf624a13e3.png)

![4](https://user-images.githubusercontent.com/19210828/58269517-6c76d300-7d90-11e9-9860-9b6fc1463a8d.png)

![5](https://user-images.githubusercontent.com/19210828/58269518-6d0f6980-7d90-11e9-8cb8-77af8394000b.png)


