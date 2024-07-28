# 16-bit-von-neuman-computer

computer from the "Elements of Computing Systems" book implemented in verilog and simulated with verilator and some GUI through dearimgui. This project was just for me to learn about digital design through verilog and also tie together all the things I learnt in school about how a von-neuman computer works at a very low level. I wanted to learn how digital design is done in the real world, hence I skipped the HDL supplied by the authors specifically for this purpose. 

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

### A GUI window will open 
Press "Play/Pause" to run the program wihtout interruptions or Press "STEP" to execute one instruction per click.

<img width="1440" alt="Screenshot 2024-07-28 at 10 54 04 AM" src="https://github.com/user-attachments/assets/63d83bf0-a86a-4bb1-bfcc-dbc400dc282f">

### Changing Programs 
By default the ROM is loaded with a test script called "rect.hack" supplied by the authors. The program basically just draws to screen a rectangle of width 16 pixels and with a length of the value stored at RAM[0], in this case RAM[0] is set to 25. 

#### Loading a custom program
There are three different test programs in this repo and can be changed by uncommenting them in the `rom.v` file. custom programs can be run the same way by copying `*.hack` file into the `/hardware/` folder and setting the `parameter memory_file` to the corresponding `*.hack`. Re-build and run after changing the program name - `make all && ./obj_dir/computer`. 
```v
parameter memory_file = "rect.hack"; // draws a rectangle of length RAM[0](set to 25 at the start of the program)
// parameter memory_file = "add.hack"; // add's two numbers
// parameter memory_file = "sub.hack"; // subtracts two numbers and stores it in two's complement form.
```
