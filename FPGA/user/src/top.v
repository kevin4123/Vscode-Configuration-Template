module top (
    input  wire clk,
    input  wire rst,
    output wire [3:0] led
);
    counter u_counter (
        .clk (clk),
        .rst (rst),
        .count (led)
    );
endmodule
