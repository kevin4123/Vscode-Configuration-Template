`timescale 1ns/1ps

module tb_top;
    reg clk = 0;
    reg rst = 0;
    wire [3:0] led;

    top uut (
        .clk (clk),
        .rst (rst),
        .led (led)
    );

    always #5 clk = ~clk; // 100 MHz 时钟

    initial begin
        $dumpfile("tb_top.vcd");
        $dumpvars(0, tb_top);

        rst = 1;
        #20;
        rst = 0;

        #100;
        $finish;
    end
endmodule
