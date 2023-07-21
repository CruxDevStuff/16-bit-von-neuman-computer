#### CPU

##### Memory Management
    1. Memory Allocation:
        
    2. Memory Hierarchy :
        
##### Pipelining:

#### Registers
    1. FIFO - First in First Out 
        * Data that enters first leaves first/read first. Used for stuff like buffering in sensors. 
        * There is limited space(depth) and a certain width(width of incoming data in bits).
        * Data in FIFO is discarded once read. 
        * Always check before reading or writing to a FIFO, writing to a FULL FIFO will cause overflow and reading from a empty FIFO will cause underflow. 
        * Can be constructed from FLIP-FLOPS. Some FPGA's have dedicated FIFO blocks/logic. 

