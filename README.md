# fractol

> Interactive Mandelbrot and Julia fractal explorer in C with MiniLibX.

## What it does
Renders the Mandelbrot set or a Julia set with custom parameters, with mouse-wheel zoom, arrow-key panning, iteration control and colour schemes.

## What I learned
- Complex-number iteration and pixel-to-plane mapping
- Event hooks (keyboard/mouse) and image buffers in MiniLibX
- Optimised build (`-O3 -flto`)

## Tech stack
C, MiniLibX (X11)

## Build & run
```bash
make
./fractol mandelbrot
./fractol julia <real> <imaginary>   # e.g. ./fractol julia -0.8 0.156
```

## Usage
```bash
Controls: mouse wheel = zoom, arrows = move, +/- = iterations, C/V/B = colours, R = reset, Tab = switch, Esc = quit
```

## Structure
`fractol.c` (entry/args), `draw.c`, `color.c`, `hooks*.c`, `init.c`, bundled `minilibx-linux/`.

---
*Built at 42 Madrid by jgomez-d (Jorge Gomez De Oliveira).*
