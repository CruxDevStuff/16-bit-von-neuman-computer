# 16 bit computer 
16 bit computer from the "Elements of Computing Systems" book implemented in verilog and simulated with verilator and some GUI through dearimgui. This project was just for me to learn about digital design through verilog and also tie together all the things I learnt in school about how a von-neuman computer works at a very low level. I wanted to learn how digital design is done in the real world, hence I skipped the HDL supplied by the authors specifically for this purpose. 

### *** Note ***
While the hardware(verilog) is tested and functionally verified through test programs given by the authors, its not fast enough to run tetris at a playable state and takes hours to just load. While I could simplify things and build a better simulator there is no point as there is a ready to use fast simulator issued by the authors. This project is about how computers work at a gate level and I would like to preserve that in the implementation. 

## Running 
Tested on Mac, should work without problems on Linux

### Requirements
* Dear Imgui(cloned as submodule, no need to install manually)
* Verilator - https://verilator.org/guide/latest/install.html
* SDL2 (available on brew and apt)

### Run
```bash
# clone repo 
git clone --recursive https://github.com/CruxDevStuff/16-bit-von-neuman-computer.git

# switch folder
cd hardware

# build
make all

# run
./obj_dir/computer
```
