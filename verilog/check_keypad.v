module check_keypad(clk_50MHz, reset, keypad_row, keypad_col);

input clk_50MHz, reset;
input [3:0] keypad_col;

output reg [3:0] keypad_row;

wire keypad_clk;

divider_to_100Hz(.clk_50MHz(clk_50MHz), .reset(reset), .clk_100Hz(keypad_clk));


always@(posedge keypad_clk, negedge reset) begin
	if (!reset) begin
		keypad_row <= 4'b1110;
	end
	else begin
		case(keypad_row)
			4'b1110: keypad_row <= 4'b1101;
			4'b1101: keypad_row <= 4'b1011;
			4'b1011: keypad_row <= 4'b0111;
			4'b0111: keypad_row <= 4'b1110;
			default: keypad_row <= 4'b1110;
		endcase
	end
end

endmodule
