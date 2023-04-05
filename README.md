Afterburner
===========

![CI](https://github.com/x6herbius/afterburner-game/workflows/CI/badge.svg)

*(Working title)*

Open-source reboot of [James Bond 007: Nightfire](https://en.wikipedia.org/wiki/James_Bond_007:_Nightfire). The primary purpose of this mod is to recreate and improve the experience of the PC version of Nightfire, and to provide in the process an open-source codebase that will allow for extension and refinement. The Xash3D (GoldSrc) engine was chosen because its codebase is fully available, it's smaller and simpler than Source, it's closer to the genuine Nightfire engine, and it doesn't come with the expectation that games will be photorealistic (I don't have the time or the energy as a single hobbyist to be working on some sort of HD photorealistic remake).

## I want to play, where are the downloads?

See [here](https://github.com/x6herbius/afterburner-game/releases). Please note, however, that at time of writing only pre-release versions of the game are available for testing purposes. These are liable to be buggy and will not be representative of the final game.

## I want to compile the game from source, how do I do that?

### Game prerequisites

Ensure that you have Python 3 installed on your computer, as well as the appropriate C/C++ development tools for your platform (Windows and Linux are supported). The required dependencies for the Xash3D engine are listed in the original Xash3D readme [later in this file](#prerequisites) - you should follow the appropriate steps for your platform to install them. Note that for Afterburner, **64-bit builds are now supported and recommended**, but if you want to compile in 32-bit, you will need the 32-bit versions of the dependencies.

Clone this repository using `git clone --recursive`. If you don't use the `--recursive` switch, the game **will not** compile without manually initialising the subrepositories. If you find yourself needing to do this, run `git submodule update --init --recursive` from within the root directory of the repository.

### Building the game

To build, open a terminal in the root of the repository and call:

```
python3 ./waf configure --64bits --build-type=debug --prefix=build/debug --enable-packaging
```

This will set up the build for a debug version of the game. Note that if you downloaded SDL2 from the SDL website (eg. for a Windows build) and it is not available in the system path, you will need to pass the path to the directory you extracted it to via the `--sdl2` option, eg. `--sdl2=/path/to/SDL2`.

To build the game and copy all output to the `build/debug` folder in the root of the repo, call:

```
python3 ./waf build install
```

For more information, or a list of all available options, run `python3 ./waf --help`. Note that most of these will be for advanced users only.

## Credits

Many thanks to:

* Gearbox for the original game.
* The FWGS team for the [Xash3D engine](https://github.com/FWGS/xash3d-fwgs) and [Xash3D version of Half Life SDK](https://github.com/FWGS/hlsdk-xash3d).
* j-yaniv and others for [Rho-Bot Half Life bots](https://sourceforge.net/projects/rhobot/).
* Developers of [STB libraries](https://github.com/nothings/stb).
* Developers of [rapidjson library](http://rapidjson.org/).
* Contributors to [XeNTaX game reverse-engineering forums](https://forum.xentax.com/).
* ZapSplat.com for various free sound effects.
* Various Nightfire modders over the years whose tools and reverse-engineering have proven invaluable when developing this mod (specifically Tres, 009, Ford, UltimateSniper).

For posterity, the Xash3D engine readme is below.

-----

# Xash3D FWGS Engine
[![GitHub Actions Status](https://github.com/FWGS/xash3d-fwgs/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/FWGS/xash3d-fwgs/actions/workflows/c-cpp.yml) [![FreeBSD Build Status](https://img.shields.io/cirrus/github/FWGS/xash3d-fwgs?label=freebsd%20build)](https://cirrus-ci.com/github/FWGS/xash3d-fwgs) [![Discord Server](https://img.shields.io/discord/355697768582610945.svg)](http://fwgsdiscord.mentality.rip/) \
[![Download Stable](https://img.shields.io/badge/download-stable-yellow)](https://github.com/FWGS/xash3d-fwgs/releases/latest) [![Download Testing](https://img.shields.io/badge/downloads-testing-orange)](https://github.com/FWGS/xash3d-fwgs/releases/tag/continuous)

Xash3D FWGS is a fork of Xash3D Engine by Unkle Mike with extended features and crossplatform.

```
Xash3D is a game engine, aimed to provide compatibility with Half-Life Engine,
as well as to give game developers well known workflow and extend it.
Read more about Xash3D on ModDB: https://www.moddb.com/engines/xash3d-engine
```

## Fork features
* HLSDK 2.4 support.
* Crossplatform: supported x86 and ARM on Windows/Linux/BSD/Android. ([see docs for more info](Documentation/ports.md))
* Modern compilers support: say no more to MSVC6.
* Better multiplayer support: multiple master servers, headless dedicated server.
* Mobility API: allows better game integration on mobile devices(vibration, touch controls)
* Different input methods: touch, gamepad and classic mouse & keyboard.
* TrueType font rendering, as a part of mainui_cpp.
* Multiple renderers support: OpenGL, GLESv1, GLESv2, Software.
* Voice support.
* External filesystem module like in GoldSrc engine.
* External vgui support module.
* PNG image format support.
* A set of small improvements, without broken compatibility.

## Planned fork features
* Virtual Reality support and game API.
* Vulkan renderer.

## Installation & Running
0) Get Xash3D FWGS binaries: you can use [testing](https://github.com/FWGS/xash3d-fwgs/releases/tag/continuous) build or you can compile engine from source code.
1) Copy engine binaries to some directory.
2) Copy `valve` directory from [Half-Life](https://store.steampowered.com/app/70/HalfLife/) to directory with engine binaries.
If your CPU is NOT x86 compatible or you're running 64-bit version of the engine, you may want to compile [Half-Life SDK](https://github.com/FWGS/hlsdk-portable).
This repository contains our fork of HLSDK and restored source code for some of the mods. Not all of them, of course.
You still needed to copy `valve` directory as all game resources located there.
3) Run the main executable (`xash3d.exe` or AppImage).

For additional info, run Xash3D with `-help` command line key.

## Contributing
* Before sending an issue, check if someone already reported your issue. Make sure you're following "How To Ask Questions The Smart Way" guide by Eric Steven Raymond. Read more: http://www.catb.org/~esr/faqs/smart-questions.html
* Issues are accepted in both English and Russian
* Before sending a PR, check if you followed our contribution guide in CONTRIBUTING.md file.

## Build instructions
We are using Waf build system. If you have some Waf-related questions, I recommend you to read https://waf.io/book/

NOTE: NEVER USE GitHub's ZIP ARCHIVES. GitHub doesn't include external dependencies we're using!

### Prerequisites

If your CPU is x86 compatible, we are building 32-bit code by default. This was done to maintain compatibility with Steam releases of Half-Life and based on it's engine games.
Even if Xash3D FWGS does support targetting 64-bit, you can't load games without recompiling them from source code!

If your CPU is NOT x86 compatible or you decided build 64-bit version of engine, you may want to compile [Half-Life SDK](https://github.com/FWGS/hlsdk-portable).
This repository contains our fork of HLSDK and restored source code for some of the mods. Not all of them, of course.

#### Windows (Visual Studio)
* Install Visual Studio.
* Install latest [Python](https://python.org) **OR** run `cinst python.install` if you have Chocolatey.
* Install latest [Git](https://git-scm.com/download/win) **OR** run `cinst git.install` if you have Chocolatey.
* Download [SDL2](https://libsdl.org/download-2.0.php) development package for Visual Studio.
* Clone this repository: `git clone --recursive https://github.com/FWGS/xash3d-fwgs`.
* Make sure you have at least 12GB of free space to store all build-time dependencies: ~10GB for Visual Studio, 300 MB for Git, 100 MB for Python and other.

#### GNU/Linux
##### Debian/Ubuntu
* Enable i386 on your system, if you're compiling 32-bit engine on amd64. If not, skip this

`$ sudo dpkg --add-architecture i386`
* Install development tools
  * For 32-bit engine on amd64: \
    `$ sudo apt install build-essential gcc-multilib g++-multilib python libsdl2-dev:i386 libfontconfig-dev:i386 libfreetype6-dev:i386`
  * For everything else: \
    `$ sudo apt install build-essential python libsdl2-dev libfontconfig-dev libfreetype6-dev`
* Clone this repostory:
`$ git clone --recursive https://github.com/FWGS/xash3d-fwgs`

### Building
#### Windows (Visual Studio)
0) Open command line
1) Navigate to `xash3d-fwgs` directory.
2) Carefully examine which build options are available: `waf --help`
3) Configure build: `waf configure -T release --sdl2=c:/path/to/SDL2`
4) Compile: `waf build`
5) Install: `waf install --destdir=c:/path/to/any/output/directory`

#### Linux
If compiling 32-bit on amd64, you may need to supply `export PKG_CONFIG_PATH=/usr/lib/i386-linux-gnu/pkgconfig` prior to running configure.

0) Examine which build options are available: `./waf --help`
1) Configure build: `./waf configure -T release`
(You need to pass `-8` to compile 64-bit engine on 64-bit x86 processor)
2) Compile: `./waf build`
3) Install(optional): `./waf install --destdir=/path/to/any/output/directory`
