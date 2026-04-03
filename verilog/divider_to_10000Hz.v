module divider_to_10000Hz(clk_50MHz, reset, clk_10000Hz);

input clk_50MHz, reset;
output clk_10000Hz;

reg clk_10000Hz;
reg [31:0] count;

always@(posedge clk_50MHz or negedge reset) begin
	if(!reset) begin
		count <= 32'd0;
		clk_10000Hz <= 1'b0;
	end
	else begin
		if(count == 32'd2500) begin
			count <= 32'd0;
			clk_10000Hz <= ~clk_10000Hz;
		end
		else begin
			count <= count + 32'd1;
		end
	end

end


endmodule
