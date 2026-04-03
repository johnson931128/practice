module vga
(
    input                   I_clk   , // 系统50MHz时钟
    input                   I_rst_n , // 系统复位
    output                  O_hs    , // VGA行同步信号
    output                  O_vs    ,  // VGA场同步信号
	 output video_on,
	 output p_tick,
	 output [9:0] x,     // pixel count/position of pixel x, max 0-799
    output [9:0] y      // pixel count/position of pixel y, max 0-524
);

// 分辨率为640*480时行时序各个参数定义
parameter       C_H_SYNC_PULSE      =   96  , 
                C_H_BACK_PORCH      =   48  ,
                C_H_ACTIVE_TIME     =   640 ,
                C_H_FRONT_PORCH     =   16  ,
                C_H_LINE_PERIOD     =   800 ;

// 分辨率为640*480时场时序各个参数定义               
parameter       C_V_SYNC_PULSE      =   2   , 
                C_V_BACK_PORCH      =   33  ,
                C_V_ACTIVE_TIME     =   480 ,
                C_V_FRONT_PORCH     =   10  ,
                C_V_FRAME_PERIOD    =   525 ;
                
parameter       C_COLOR_BAR_WIDTH   =   C_H_ACTIVE_TIME / 8  ;  

reg [11:0]      R_h_cnt         ; // 行时序计数器
reg [11:0]      R_v_cnt         ; // 列时序计数器
reg             R_clk_25M       ;


always @(posedge I_clk or negedge I_rst_n)
begin
    if(!I_rst_n)
        R_clk_25M   <=  1'b0        ;
    else
        R_clk_25M   <=  ~R_clk_25M  ;     
end

assign p_tick = R_clk_25M;

always @(posedge R_clk_25M or negedge I_rst_n)
begin
    if(!I_rst_n)
        R_h_cnt <=  12'd0   ;
    else if(R_h_cnt == C_H_LINE_PERIOD - 1'b1)
        R_h_cnt <=  12'd0   ;
    else
        R_h_cnt <=  R_h_cnt + 1'b1  ;                
end                

assign O_hs =   (R_h_cnt < C_H_SYNC_PULSE) ? 1'b0 : 1'b1    ; 


always @(posedge R_clk_25M or negedge I_rst_n)
begin
    if(!I_rst_n)
        R_v_cnt <=  12'd0   ;
    else if(R_v_cnt == C_V_FRAME_PERIOD - 1'b1)
        R_v_cnt <=  12'd0   ;
    else if(R_h_cnt == C_H_LINE_PERIOD - 1'b1)
        R_v_cnt <=  R_v_cnt + 1'b1  ;
    else
        R_v_cnt <=  R_v_cnt ;                        
end                

assign O_vs =   (R_v_cnt < C_V_SYNC_PULSE) ? 1'b0 : 1'b1    ; 
  

assign video_on =  (R_h_cnt >= (C_H_SYNC_PULSE + C_H_BACK_PORCH                  ))  &&
                        (R_h_cnt <= (C_H_SYNC_PULSE + C_H_BACK_PORCH + C_H_ACTIVE_TIME))  && 
                        (R_v_cnt >= (C_V_SYNC_PULSE + C_V_BACK_PORCH                  ))  &&
                        (R_v_cnt <= (C_V_SYNC_PULSE + C_V_BACK_PORCH + C_V_ACTIVE_TIME))  ;                     
assign x = R_h_cnt;
assign y = R_v_cnt;

endmodule
