# configuration
SHELL = /bin/sh
FPGA_PKG = cb132
FPGA_TYPE = hx8k
PCF = board.pcf

PROJ = ram
# included modules
ADD_SRC = ${PROJ}.v

${PROJ}: ${PROJ}.rpt ${PROJ}.bin

${PROJ}.json: ${PROJ}.v
	yosys -p 'synth_ice40 -top top -json $@' ${PROJ}.v

${PROJ}.asc: ${PROJ}.json
	nextpnr-ice40 --${FPGA_TYPE} --package ${FPGA_PKG} --json $< --pcf-allow-unconstrained --pcf ${PCF} --asc $@

${PROJ}.rpt: ${PROJ}.asc
	icetime -d ${FPGA_TYPE} -mtr $@ $<

${PROJ}.bin: ${PROJ}.asc
	icepack $< $@

gui: ${PROJ}.json
	nextpnr-ice40 --gui --${FPGA_TYPE} --package ${FPGA_PKG} --json $< --pcf ${PCF} --asc ${PROJ}.asc

upload: ${PROJ}.bin
	iceprog $<

all:${PROJ} 

clean:
	rm -f *.json *.asc *.rpt *.bin *yosys.log

.PHONY: all clean