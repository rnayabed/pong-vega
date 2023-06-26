# pong-vega

This is a weekend project to create pong without any library functions or libc on a CDAC THEJAS32 powered board. No external code whatsoever.

As a result, I was able to learn about linker scripts, RISC-V assembly much better in detail, and had first hand experience in going through hardware datasheet and controlling it accordingly.

<div align="center">
<img src="https://raw.githubusercontent.com/rnayabed/pong-vega/master/screenshots/photo.png">

# [Video Demo](https://www.youtube.com/watch?v=BnFxO1wrXD8) 
</div>

Pin configurations, display I2C address, game speed, and other settings can be changed by editing `config.h`

# Hardware

- SoC: CDAC VEGA THEJAS32. Tested on CDAC Aries v2.0
- Display: SH1106 OLED via I2C. Note: The one I purchased has a resolution of 128x64 instead of the 132x64 in the official [datasheet](https://www.velleman.eu/downloads/29/infosheets/sh1106_datasheet.pdf).
Therefore there may be compatibility issues with other OLED displays with different resolution.
- 4 push buttons (Up and Down button for each player) configured with pull down resistors.

# Software

You need a RISC-V GCC rv32im toolchain. To compile, simply run 

```
cmake -B build -RISCV_TOOLCHAIN_FULL_PATH=<path to riscv toolchain>/bin/<target triplet>
```

For example: If GCC toolchain is stored in `/opt/riscv` with target-triplet `riscv64-unknown-elf`, the value would be `/opt/riscv/bin/riscv64-unknown-elf`
Note: if `RISCV_TOOLCHAIN_FULL_PATH` is not specfied, it searches for the toolchain in PATH with the triplet `riscv64-unknown-elf`.

After configuration, run:

```
cmake --build build
```

The executable will be built as `pong-vega` in the `build` directory. 

If you have an ARIES v2.0 board, you can use [vegadude](https://github.com/rnayabed/vegadude) to upload the binary.

Example usage:

```
vegadude -bp build/pong-vega -tp /dev/ttyUSB0 --aries -sau
```
