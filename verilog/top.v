 module top(
    input clk_50MHz,       // from Basys 3
    input reset,            // btnC on Basys 3
	 input [3:0] keycol,
	 output [3:0] keyrow,
    output hsync,           // VGA port on Basys 3
    output vsync,           // VGA port on Basys 3
    output [11:0] rgb,       // to DAC, 3 bits to VGA port on Basys 3
	 output [7:0] dot_row,
	 output [7:0] dot_col,
	 output [7:0] dot_col2,
	 output left_wall_hit,
	 output right_wall_hit,
	 output [6:0] seg1,
	 output [6:0] seg0
    );
    
	 reg up1, up2, down1, down2;
    wire w_video_on, w_p_tick;
//	 wire [1:0] left_point, right_point;
    wire [9:0] w_x, w_y;
    reg [11:0] rgb_reg;
    wire[11:0] rgb_next;
	 wire div_clk;
	
    
    vga vc(.I_clk(clk_50MHz), .I_rst_n(reset), .video_on(w_video_on), .O_hs(hsync), 
                      .O_vs(vsync), .p_tick(w_p_tick), .x(w_x), .y(w_y));
    check_keypad(.clk_50MHz(clk_50MHz), .reset(reset), .keypad_row(keyrow), .keypad_col(keycol));
	 dot_matrix(.clk_50MHz(clk_50MHz), .reset(reset), .left_wall_hit(left_wall_hit), .right_wall_hit(right_wall_hit), 
								.dot_row(dot_row), .dot_col(dot_col));
	 labsec_count(.clk(clk_50MHz), .reset(reset), .seg1(seg1), .seg0(seg0));
	 pixel_generation(.clk(clk_50MHz), .div_clk(div_clk), .reset(reset), .up1(up1), .down1(down1), .up2(up2), .down2(down2), .video_on(w_video_on), 
					.x(w_x), .y(w_y), .rgb(rgb_next), .left_wall_hit(left_wall_hit), .right_wall_hit(right_wall_hit));
	 clk_div_10_sec(.clk(clk_50MHz), .reset(reset), .div_clk(div_clk));
								
	 assign dot_col2 = 8'b0000_0000;
	 
	 always @(*) begin
			case ({keyrow, keycol}) 
			8'b0111_0111:
				up1 = 1;
			8'b1110_0111:
				down1 = 1;
			8'b0111_1110:
				up2 = 1;
			8'b1110_1110:
				down2 = 1;
			default: begin
				up1 = 0;
				down1 = 0;
				up2 = 0;
				down2 = 0;
			end
			endcase
	 end
	 
    always @(posedge clk_50MHz)
        if(w_p_tick)
            rgb_reg <= rgb_next;
            
    assign rgb = rgb_reg;
 
endmodule
