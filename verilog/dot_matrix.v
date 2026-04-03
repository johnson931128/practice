module dot_matrix(
    input clk_50MHz,
    input reset,
    input left_wall_hit,
    input right_wall_hit,
   
    output reg [7:0] dot_row,
    output reg [7:0] dot_col


);

reg [1:0] left_point;
reg [1:0] right_point;
reg [2:0]row_count;



//reg left_wall_hit_pre=1'b0;
//reg right_wall_hit_pre=1'b0;

wire clk_10000hz;
divider_to_10000Hz(.clk_50MHz(clk_50MHz), .reset(reset), .clk_10000Hz(clk_10000hz));


always @(posedge left_wall_hit, negedge reset) begin
    if(!reset) begin
	  left_point <= 2'd0;
    end
    else begin
		left_point <= left_point + 2'd1;
    end
end

always @(posedge right_wall_hit, negedge reset) begin
	if(!reset) begin
		right_point <= 2'd0;
	end
	else begin
		right_point <= right_point + 2'd1;
	end
end

always @(posedge clk_10000hz or negedge reset) begin
    if(!reset)begin
        dot_col<=8'd0;
        dot_row<=8'd0;
        row_count<=4'd0;
    end
    else begin
        row_count<=row_count+1;
        case(left_point)
            3'd0:begin 
                case(right_point)
                    3'd0:begin
                        case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b00000000; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b00011000; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b00011000; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b00000000; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b00000000; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b00011000; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b00011000; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b00000000; end
                        endcase
                    end
                    3'd1:begin
                        case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b00000001; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b00011001; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b00011001; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b00000001; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b00000001; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b00011001; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b00011001; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b00000001; end
                        endcase
                    end
                    3'd2:begin
                        case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b00000011; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b00011011; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b00011011; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b00000011; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b00000011; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b00011011; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b00011011; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b00000011; end
                        endcase
                    end
                    3'd3:begin
                       case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b00000111; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b00011111; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b00011111; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b00000111; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b00000111; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b00011111; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b00011111; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b00000111; end
                        endcase
                    end
                
                endcase
            end
            3'd1:begin
                case(right_point)
                    3'd0:begin
                        case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b10000000; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b10011000; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b10011000; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b10000000; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b10000000; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b10011000; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b10011000; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b10000000; end
                        endcase
                    end
                    3'd1:begin
                       case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b10000001; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b10011001; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b10011001; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b10000001; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b10000001; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b10011001; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b10011001; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b10000001; end
                        endcase
                    end
                    3'd2:begin
                        case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b10000011; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b10011011; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b10011011; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b10000011; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b10000011; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b10011011; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b10011011; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b10000011; end
                        endcase
                    end
                    3'd3:begin
                       case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b10000111; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b10011111; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b10011111; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b10000111; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b10000111; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b10011111; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b10011111; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b10000111; end
                        endcase
                    end
                
                endcase
            end
            3'd2:begin
                case(right_point)
                    3'd0:begin
                        case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b11000000; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b11011000; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b11011000; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b11000000; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b11000000; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b11011000; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b11011000; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b11000000; end
                        endcase
                    end
                    3'd1:begin
                        case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b11000001; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b11011001; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b11011001; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b11000001; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b11000001; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b11011001; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b11011001; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b11000001; end
                        endcase
                    end
                    3'd2:begin
                       case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b11000011; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b11011011; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b11011011; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b11000011; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b11000011; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b11011011; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b11011011; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b11000011; end
                        endcase
                    end
                    3'd3:begin
                        case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b11000111; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b11011111; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b11011111; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b11000111; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b11000111; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b11011111; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b11011111; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b11000111; end
                        endcase
                    end
                
                endcase
            end
            3'd3:begin
                case(right_point)
                    3'd0:begin
                      case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b11100000; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b11111000; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b11111000; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b11100000; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b11100000; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b11111000; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b11111000; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b11100000; end
                        endcase
                    end
                    3'd1:begin
                       case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b11100001; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b11111001; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b11111001; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b11100001; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b11100001; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b11111001; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b11111001; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b11100001; end
                        endcase
                    end
                    3'd2:begin
                       case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b11100011; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b11111011; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b11111011; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b11100011; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b11100011; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b11111011; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b11111011; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b11100011; end
                        endcase
                    end
                    3'd3:begin
                        case(row_count)
                        3'd0:begin dot_row<=8'b01111111; dot_col<=8'b11100111; end
                        3'd1:begin dot_row<=8'b10111111; dot_col<=8'b11111111; end
                        3'd2:begin dot_row<=8'b11011111; dot_col<=8'b11111111; end
                        3'd3:begin dot_row<=8'b11101111; dot_col<=8'b11100111; end
                        3'd4:begin dot_row<=8'b11110111; dot_col<=8'b11100111; end
                        3'd5:begin dot_row<=8'b11111011; dot_col<=8'b11111111; end
                        3'd6:begin dot_row<=8'b11111101; dot_col<=8'b11111111; end
                        3'd7:begin dot_row<=8'b11111110; dot_col<=8'b11100111; end
                        endcase
                    end
                
                endcase
            end
            default:begin
            end
        endcase
    end
end
endmodule
