# kbidle

## Description

The purpose of this program is to fade in/out the Framework laptop's keyboard backlight based on user activity.

The `KIdleTime` interface of KDE is used to detect user idleness.

## Usage

Usage of the program is straightforward. It takes a single argument: the duration in milliseconds for which a user must be idle for the backlight to fade out:

`./kbidle DURATION_MS` (i.e. `./kbidle 60000` for one minute)

## Compilation

Compiling this requires the Qt, KDE and hidapi dev bindings as well as CMake and a C++ compiler

`build.sh` is included as a convenience script, but otherwise it can be compiled as any standard CMake project

## Thanks

Framework - Making an awesome laptop and [implementing the VIA/QMK HID interface removing the need to reverse engineer it myself](https://github.com/FrameworkComputer/qmk_hid)

KDE - [Making a nice example on how to use KIdleTime](https://github.com/KDE/kidletime)
