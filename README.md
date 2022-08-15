# Signal Tracer
## General
Visualize wifi theoretical speed levels as a heatmap in 3d model of floor or building. 
The program builds a heat map on a cutting plane that can be moved along the Z axis. The resulting series of images looks like a picture on a tomograph. 
Model itself rendered gray, access points rendered as green pyramids.

## Screenshot
![screenshot](https://user-images.githubusercontent.com/12677911/184630285-645ceea6-497d-4682-a071-146b2834509f.png)

## Building or floor model
The ASSIMP library is used to load models of floors or buildings, so all model formats supported by this library are supported. 
The program was tested using the FBX 2013 format. There is one test case in this repository.

## Access points parameters
Data on the location of access points, their power and frequency, and other parameters are loaded as a json configuration file.
```
    "signal_sources": [
        {
            "position": {
                "x": -65.0,
                "y": -70.0,
                "z": -20.001
            },
            "frequency": 5150,
            "attenuation": 4,
            "power": 12,
            "gain": 5,
            "noise": 2,
            "channel_width": 40,
            "temperature": 300,
            "standard": "ax"
        }, 
        ... 
        ]
```

## Build
Make shure you have compiler tools `gcc`, `g++` (version 11 minimum), `cmake`, `make` installed.

Install development packages of `SDL2`, `GLEW`, `OpenGL`, `GLUT`, `GLM`, `ASSIMP`, `nlohmann json`.

Configure: 
```
$ mkdir signaltracer/build
$ cd signaltracer/build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
```

Build:
```
$ cmake --build . -- -j8
```
or
```
$ make
```

## Usage
```
./sigtracer [model filename] [configuration]
```

to just show test case:
```
./sigtracer
```
