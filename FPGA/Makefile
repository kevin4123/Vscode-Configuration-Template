# mingw32-make


TB = "$(CURDIR)/user/sim/tb_top.v"
TARGET = "$(CURDIR)/prj/icarus/tb_top.vvp"
SRC = $(wildcard $(CURDIR)/user/src/*.v)


all: icarus
	iverilog.exe -g2012 -o $(TARGET) -s tb_top $(TB) $(SRC)
	vvp $(TARGET)

icarus:
	if not exist "$(CURDIR)\prj\icarus" mkdir "$(CURDIR)\prj\icarus"	


$(info ==========================================================)
$(info TB = $(TB))
$(info TARGET = $(TARGET))
$(info SOURCES = $(SRC))
$(info ==========================================================)
