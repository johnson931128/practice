module divider_to_100Hz(clk_50MHz, reset, clk_100Hz);

input clk_50MHz, reset;
output clk_100Hz;

reg clk_100Hz;
reg [31:0] count;

always@(posedge clk_50MHz or negedge reset) begin
	if(!reset) begin
		count <= 32'd0;
		clk_100Hz <= 1'b0;
	end
	else begin
		if(count == 32'd250000) begin
			count <= 32'd0;
			clk_100Hz <= ~clk_100Hz;
		end
		else begin
			count <= count + 32'd1;
		end
	end

end


endmodule

