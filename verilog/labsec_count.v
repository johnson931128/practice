module labsec_count (
    input wire clk,      // 50 MHz 時鐘
    input wire reset,           // 重置訊號
    output reg [6:0] seg1, // 十位數的七段顯示器輸出
    output reg [6:0] seg0  // 個位數的七段顯示器輸出
);

	 reg one_sec_div_clk; // 一秒分頻時鐘訊號
    reg [31:0] count; // 分頻計數器
	 
    // 分頻器，將 50 MHz 時鐘分頻為 1 Hz
    always @(posedge clk or negedge reset) begin
        if (!reset) begin
            count <= 32'd0;
            one_sec_div_clk <= 1'b0;
        end else begin
            if (count == 32'd25000000) begin
                count <= 32'd0;
                one_sec_div_clk <= ~one_sec_div_clk;
            end else begin
                count <= count + 32'd1;
            end
        end
    end	 
	 
	 
    reg [3:0] tens; // 十位數 (0-9)
    reg [3:0] ones; // 個位數 (0-9)

    always @(posedge one_sec_div_clk or negedge reset) begin
        if (!reset) begin
            tens <= 0;
            ones <= 0;
        end else begin
            if (ones == 9) begin
                ones <= 0;
                if (tens == 9) begin
                    tens <= 0; // 超過 99 秒，重置為 0
                end else begin
                    tens <= tens + 1;
                end
            end else begin
                ones <= ones + 1;
            end
        end
    end

    // 七段顯示器顯示數字的 case 寫法
    always @(*) begin
        case (ones)
            4'd0: seg0 = 7'b1000000; // 0
            4'd1: seg0 = 7'b1111001; // 1
            4'd2: seg0 = 7'b0100100; // 2
            4'd3: seg0 = 7'b0110000; // 3
            4'd4: seg0 = 7'b0011001; // 4
            4'd5: seg0 = 7'b0010010; // 5
            4'd6: seg0 = 7'b0000010; // 6
            4'd7: seg0 = 7'b1111000; // 7
            4'd8: seg0 = 7'b0000000; // 8
            4'd9: seg0 = 7'b0010000; // 9
            default: seg0 = 7'b1111111; // Blank
        endcase

        case (tens)
            4'd0: seg1 = 7'b1000000; // 0
            4'd1: seg1 = 7'b1111001; // 1
            4'd2: seg1 = 7'b0100100; // 2
            4'd3: seg1 = 7'b0110000; // 3
            4'd4: seg1 = 7'b0011001; // 4
            4'd5: seg1 = 7'b0010010; // 5
            4'd6: seg1 = 7'b0000010; // 6
            4'd7: seg1 = 7'b1111000; // 7
            4'd8: seg1 = 7'b0000000; // 8
            4'd9: seg1 = 7'b0010000; // 9
            default: seg1 = 7'b1111111; // Blank
        endcase
    end
	 
	 
endmodule 
