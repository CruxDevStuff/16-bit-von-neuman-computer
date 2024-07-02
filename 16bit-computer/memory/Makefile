PROJ      = blinky
BUILD     = ./build
DEVICE    = hx8k
FOOTPRINT = cb132

# Files
FILES = test.v

.PHONY: all clean upload timing

all $(BUILD)/$(PROJ).asc $(BUILD)/$(PROJ).bin:
	# if build folder doesn't exist, create it
	mkdir -p $(BUILD)

	# synthesize using Yosys
	yosys -p "synth_ice40 -top ram_chip -blif $(BUILD)/$(PROJ).blif -json $(BUILD)/$(PROJ).json" $(FILES)

	# Place and route using arachne
	arachne-pnr -d $(subst hx,,$(subst lp,,$(DEVICE))) -P $(FOOTPRINT) -o $(BUILD)/$(PROJ).asc -p board.pcf $(BUILD)/$(PROJ).blif

	#nextpnr-ice40 --hx$(DEVICE) --json build/$(PROJ).json --pcf board.pcf --asc build/$(PROJ).asc

	# Convert to bitstream using IcePack
	icepack $(BUILD)/$(PROJ).asc $(BUILD)/$(PROJ).bin

upload: $(BUILD)/$(PROJ).bin
	iceprog $(BUILD)/$(PROJ).bin

timing: $(BUILD)/$(PROJ).asc
	icetime -tmd hx$(DEVICE) $(BUILD)/$(PROJ).asc

clean:
	rm build/*