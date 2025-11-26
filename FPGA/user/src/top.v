module top (
    input  wire clk,
    input  wire rst
);
    reg [3:0] led_reg;
    always @(posedge clk) begin
        if (rst) begin
            led_reg <= 4'b0000;
        end else begin
            led_reg <= led_reg + 1;
        end
    end
endmodule
