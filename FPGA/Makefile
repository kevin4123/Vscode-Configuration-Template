TB = "C:/Users/ch180/Desktop/FPGA/led/user/sim/tb_top.v"
TARGET = "prj/icarus/tb_top.vvp"
SRC = $(wildcard C:/Users/ch180/Desktop/FPGA/led/user/src/*.v C:/Users/ch180/Desktop/FPGA/led/user/src/lib/*.v)


all: icarus
	iverilog.exe -g2012 -o $(TARGET) -s tb_top $(TB) $(SRC)
	vvp ./prj/icarus/tb_top.vvp

icarus:
	if not exist prj\icarus mkdir prj\icarus

clean:
	rm -rf prj/icarus

.PHONY: clean

