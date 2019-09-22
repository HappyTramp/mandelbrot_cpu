# Mandelbrot set visualizer

A visualizer for the [Mandelbrot Set](https://en.wikipedia.org/wiki/Mandelbrot_set).

## Dependencies

- [SDL2](https://www.libsdl.org/) for the graphics

## Install

SDL2: `sudo apt install libsdl2-dev`

## Usage

1. compile: `make all`
2. run: `./mandel`

## TODO

- [ ] Color gradient with control points and cubic iterpolation
      like <https://stackoverflow.com/a/25816111>
- [ ] Smooth shading for out of set iteration colors.
- [ ] Draw to bmp image.
- [x] Create pixel array and update the render line by line.
- [ ] Display coordinates and other useful info.
- [x] Computation done in parallel.
- [x] Command line options
- [x] Anti-aliasing with supersampling
- [ ] Other (not random?) supersampling algorithm
