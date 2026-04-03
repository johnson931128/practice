module pixel_generation(
    input clk,                              // 50MHz
    input reset,                            
	 input up1,
	 input down1,
	 input up2,
	 input down2,
    input video_on,                         // from VGA controller
    input [9:0] x, y,                       // from VGA controller
    input div_clk,
	 output reg [11:0] rgb,                  // to DAC, to VGA controller
	 output reg left_wall_hit,
	 output reg right_wall_hit
    );
    
	 parameter HBHS = 96+48;
	 parameter VBVS = 2+33;
    parameter X_MAX = HBHS+639;            // right border of display area
    parameter Y_MAX = VBVS+479; 	 // bottom border of display area
    parameter SQ_RGB = 12'h0FF;             // green & blue = yellow for square
    parameter BG_RGB = 12'h000;             // black background
	 parameter PAD_RGB = 12'hFFF;                
	 parameter PAD2_RGB = 12'hFFF;
	 parameter LEFT_SCORE_AREA_RGB = 12'h0F0;
	 parameter RIGHT_SCORE_AREA_RGB = 12'h0F0;
    parameter SQUARE_SIZE = 16;             // width of square sides in pixels
    parameter SQUARE_VELOCITY_POS = 2;      // set position change value for positive direction
    parameter SQUARE_VELOCITY_NEG = -2;     // set position change value for negative direction 
	 /////磚塊區
	 parameter BRICK_SIZE = 12; //磚塊寬度-------球	 
	 parameter BK_RGB = 12'hFA0;  //磚塊顏色	 
	 reg [9:0] BRICK_VELOCITY_POS; // 向上速度------球
	 reg [9:0] BRICK_VELOCITY_NEG; // 向下速度------球
    /////
	 
    // create a 60Hz refresh tick at the start of vsync 
    wire refresh_tick;
    assign refresh_tick = ((y == 481) && (x == 0)) ? 1 : 0;
    
    // square boundaries and position
    wire [9:0] sq_x_l, sq_x_r;              // square left and right boundary
    wire [9:0] sq_y_t, sq_y_b;              // square top and bottom boundary

    
    reg  [9:0] sq_x_reg, sq_y_reg;           // regs to track left, top position
    wire [9:0] sq_x_next, sq_y_next;        // buffer wires 
    
    reg [9:0] x_delta_reg, y_delta_reg;     // track square speed
    reg [9:0] x_delta_next, y_delta_next;   // buffer regs    
    

	 /////磚塊區
	 
	 wire [9:0] bk_x_l, bk_x_r;              // 磚塊的左邊界與右邊界-------球
	 wire [9:0] bk_y_t, bk_y_b;              // 磚塊的上邊界與下邊界-------球	 
	 
	 reg  [9:0] bk_x_reg, bk_y_reg;                    //追蹤磚塊的x,y座標-------球
	 wire [9:0] bk_x_next, bk_y_next;	 
	 
	 reg [9:0] bk_x_delta_reg, bk_y_delta_reg;   //追蹤磚塊x,y速度--------球
	 reg [9:0] bk_x_delta_next, bk_y_delta_next;
	 
	 parameter X_BRICK_L = HBHS+322;
	 parameter X_BRICK_R = HBHS+328;
	 
	 /////
	 
	 
	 
	 // PADDLE 326,327
    // paddle horizontal boundaries
    parameter X_PAD_L = HBHS+600;
    parameter X_PAD_R = HBHS+603;    // 4 pixels wide
	 parameter X_PAD2_L = HBHS+50;
	 parameter X_PAD2_R = HBHS+53;
	 
	 
	 
    // paddle vertical boundary signals
    wire [9:0] y_pad_t, y_pad_b;
	 wire [9:0] y_pad2_t, y_pad2_b;
    parameter PAD_HEIGHT = 72;  // 72 pixels high
	 parameter PAD2_HEIGHT = 72;  // 72 pixels high
	 

	 
    // register to track top boundary and buffer
    reg [9:0] y_pad_reg, y_pad_next;
	 reg [9:0] y_pad2_reg, y_pad2_next;
	 
    // paddle moving velocity when a button is pressed
    parameter PAD_VELOCITY = 10;     // change to speed up or slow down paddle movement
	 parameter PAD2_VELOCITY = 10;     // change to speed up or slow down paddle movement
	 
	 
    // register control
    always @(posedge clk or negedge reset)
        if(!reset) begin
				y_pad_reg <= 0;
				y_pad2_reg <= 0;
            sq_x_reg <= 0;
            sq_y_reg <= 0;
            x_delta_reg <= 10'h002;
            y_delta_reg <= 10'h002;
	/////磚塊區			
				bk_x_reg <= HBHS + 320; //先讓磚塊到中間------
				bk_y_reg <= VBVS ;
				bk_x_delta_reg <= 10'h000;  //y速度先跟球一樣,Vx=0------
				bk_y_delta_reg <= 10'h002;
	/////
				
        end
        else begin
				y_pad_reg <= y_pad_next;
				y_pad2_reg <= y_pad2_next;
            sq_x_reg <= sq_x_next;
            sq_y_reg <= sq_y_next;
            x_delta_reg <= x_delta_next;
            y_delta_reg <= y_delta_next;
	/////磚塊區			
				bk_x_delta_reg <= bk_x_delta_next;//磚塊速度------
				bk_y_delta_reg <= bk_y_delta_next;
				bk_x_reg <= bk_x_next;//磚塊位置------
				bk_y_reg <= bk_y_next;
	/////
	
        end
    
    // square boundaries
    assign sq_x_l = sq_x_reg;                   // ball left boundary
    assign sq_y_t = sq_y_reg;                   // ball top boundary
    assign sq_x_r = sq_x_l + SQUARE_SIZE - 1;   // ball right boundary
    assign sq_y_b = sq_y_t + SQUARE_SIZE - 1;   // ball bottom boundary
	 
	 /////磚塊區
	 assign bk_x_l = bk_x_reg;                   // 磚塊的左邊界	 
    assign bk_y_t = bk_y_reg;                   // 磚塊的上邊界
    assign bk_x_r = bk_x_l + BRICK_SIZE - 1;   // 磚塊的右邊界	 
    assign bk_y_b = bk_y_t + BRICK_SIZE*12 - 1;   // 磚塊的下邊界
	 /////
	 
	 
	 
    
    // square status signal
    wire sq_on;
    assign sq_on = (sq_x_l <= x) && (x <= sq_x_r) &&
                   (sq_y_t <= y) && (y <= sq_y_b);
						 
	 /////磚塊區
	 wire bk_on;   //磚塊狀態訊號
	 assign bk_on = (bk_x_l <= x) && (x <= bk_x_r) &&
                   (bk_y_t <= y) && (y <= bk_y_b);
						 
    assign bk_x_next = (refresh_tick) ? bk_x_reg : bk_x_reg;  //磚塊新位置
    assign bk_y_next = (refresh_tick) ? bk_y_reg + bk_y_delta_reg : bk_y_reg;	 						 
						 
    /////          
			  
    // new square position
    assign sq_x_next = (refresh_tick) ? sq_x_reg + x_delta_reg : sq_x_reg;
    assign sq_y_next = (refresh_tick) ? sq_y_reg + y_delta_reg : sq_y_reg;
	 
    
	 // score detection
	 always@(*) begin
		  if (sq_x_l < X_LEFT_SCORE_AREA_R) begin
				left_wall_hit = 1;
		  end
		  else if (sq_x_r > X_RIGHT_SCORE_AREA_L) begin
				right_wall_hit = 1;
		  end
		  else begin
				left_wall_hit = 1'b0;
				right_wall_hit = 1'b0;
		  end

	 end
	 
    // ball collision detection    跟磚塊碰撞做
    always @(*) begin
		  
		  x_delta_next = x_delta_reg;
		  y_delta_next = y_delta_reg;
	  
		  if(sq_y_t < VBVS-1)                              // collide with top display edge
				y_delta_next = SQUARE_VELOCITY_POS;     // change y direction(move down)
		  else if(sq_y_b > Y_MAX)                     // collide with bottom display edge
				y_delta_next = SQUARE_VELOCITY_NEG;     // change y direction(move up)
		  else if((X_PAD_L <= sq_x_r) && (sq_x_r <= X_PAD_R) &&
					 (y_pad_t <= sq_y_b) && (sq_y_t <= y_pad_b))     // collide with right paddle
				x_delta_next = SQUARE_VELOCITY_NEG;                       // move left
		  else if((X_PAD_L <= sq_x_l) && (sq_x_l <= X_PAD_R) &&
					 (y_pad_t <= sq_y_b) && (sq_y_t <= y_pad_b))     // collide with right paddle
				x_delta_next = SQUARE_VELOCITY_POS;                       // move right
		  else if((X_PAD2_L <= sq_x_l) && (sq_x_l <= X_PAD2_R) &&
					 (y_pad2_t <= sq_y_b) && (sq_y_t <= y_pad2_b))     // collide left with paddle
				x_delta_next = SQUARE_VELOCITY_POS;                       // move right
		  else if((X_PAD2_L <= sq_x_r) && (sq_x_r <= X_PAD2_R) &&
					 (y_pad2_t <= sq_y_b) && (sq_y_t <= y_pad2_b))     // collide left with paddle
				x_delta_next = SQUARE_VELOCITY_NEG;                       // move left
		  else if((X_LEFT_SCORE_AREA_L <= sq_x_l) && (sq_x_l <= X_LEFT_SCORE_AREA_R) &&
					 (VBVS+1 <= sq_y_b) && (sq_y_t <= Y_MAX))     // collide with left score area
				x_delta_next = SQUARE_VELOCITY_POS;                       // move right
		  else if((X_RIGHT_SCORE_AREA_L <= sq_x_r) && (sq_x_r <= X_RIGHT_SCORE_AREA_R) &&
					 (VBVS+1 <= sq_y_b) && (sq_y_t <= Y_MAX))     // collide with left score area
				x_delta_next = SQUARE_VELOCITY_NEG;                       // move left
		  else if((X_BRICK_L <= sq_x_r) && (sq_x_r <= X_BRICK_R) &&  // 向右撞到磚塊
		          (bk_y_b < sq_y_t) && (sq_y_t <= bk_y_t))   			
				x_delta_next = SQUARE_VELOCITY_NEG;             // 改成向左彈		
		  else if((X_BRICK_L <= sq_x_l) && (sq_x_l <= X_BRICK_R) &&  // 向左撞到磚塊
		          (bk_y_b < sq_y_t) && (sq_y_t <= bk_y_t))   			
				x_delta_next = SQUARE_VELOCITY_POS;             // 改成向右彈					
		  else if((X_BRICK_L <= sq_x_r) && (sq_x_r <= X_BRICK_R) &&  // 向右下撞到磚塊
		          (bk_y_t == sq_y_b) )   			
				y_delta_next = SQUARE_VELOCITY_POS;             // 改成向上彈!!				
		  else if((X_BRICK_L <= sq_x_l) && (sq_x_l <= X_BRICK_R) &&  // 向左下撞到磚塊
		          (bk_y_t == sq_y_b) )   			
				y_delta_next = SQUARE_VELOCITY_POS;             // 改成向上彈!!
		  else if((X_BRICK_L <= sq_x_r) && (sq_x_r <= X_BRICK_R) &&  // 向右上撞到磚塊
		          (bk_y_b == sq_y_t))   			
				y_delta_next = SQUARE_VELOCITY_NEG;             // 改成向下彈!!	
		  else if((X_BRICK_L <= sq_x_l) && (sq_x_l <= X_BRICK_R) &&  // 向左上撞到磚塊
		          (bk_y_b == sq_y_t))   			
				y_delta_next = SQUARE_VELOCITY_NEG;             // 改成向下彈!!	
		  else if((X_BRICK_L <= sq_x_r) && (sq_x_r <= X_BRICK_R) &&
					 (bk_y_b <= sq_y_b) && (sq_y_t <= bk_y_b))     // 向右撞到磚塊
				x_delta_next = SQUARE_VELOCITY_NEG;                       // 改成向左彈
		  else if((X_BRICK_L <= sq_x_l) && (sq_x_l <= X_BRICK_R) &&
					 (bk_y_t <= sq_y_b) && (sq_y_t <= bk_y_b))     // 向左撞到磚塊
				x_delta_next = SQUARE_VELOCITY_POS;                       // 改成向右彈	
		  else if((X_BRICK_L <= sq_x_l) && (sq_x_l <= X_BRICK_R) &&
					 (bk_y_t <= sq_y_b) && (sq_y_t <= bk_y_b))     // 向左撞到磚塊
				x_delta_next = SQUARE_VELOCITY_POS;                       // 改成向右彈
		  else if((X_BRICK_L <= sq_x_r) && (sq_x_r <= X_BRICK_R) &&
					 (bk_y_t <= sq_y_b) && (sq_y_t <= bk_y_b))     // 向右撞到磚塊
				x_delta_next = SQUARE_VELOCITY_NEG;                       // 改成向左彈

    end
	 
	 
	 
    /////磚塊區: 磚塊撞擊偵測
    always @(*) begin
		  bk_x_delta_next = bk_x_delta_reg;
		  bk_y_delta_next = bk_y_delta_reg;
	  
		  if(bk_y_t < VBVS-1)                              // 撞到下面
		      bk_y_delta_next = BRICK_VELOCITY_POS;     // 改成向上移動
		  else if(bk_y_b > Y_MAX)                     // 撞到上面
				bk_y_delta_next = BRICK_VELOCITY_NEG;     // 改持向下移動		

    end	 
	 /////
	 
	 
	 // paddle status signal
    wire pad_on;
    assign y_pad_t = y_pad_reg;                             // paddle top position
    assign y_pad_b = y_pad_t + PAD_HEIGHT - 1;              // paddle bottom position
    assign pad_on = (X_PAD_L <= x) && (x <= X_PAD_R) &&     // pixel within paddle boundaries
                    (y_pad_t <= y) && (y <= y_pad_b);
						  
	 // paddle2 status signal
    wire pad2_on;
    assign y_pad2_t = y_pad2_reg;                             // paddle top position
    assign y_pad2_b = y_pad2_t + PAD2_HEIGHT - 1;              // paddle bottom position
    assign pad2_on = (X_PAD2_L <= x) && (x <= X_PAD2_R) &&     // pixel within paddle boundaries
                    (y_pad2_t <= y) && (y <= y_pad2_b);
	
	 // Left score area
	 parameter X_LEFT_SCORE_AREA_L = HBHS;
	 parameter X_LEFT_SCORE_AREA_R = HBHS+5;
	 
	 // Left score area status signal
	 wire left_score_area_on;
	 assign left_score_area_on = (X_LEFT_SCORE_AREA_L <= x) && (x <= X_LEFT_SCORE_AREA_R) &&
											(VBVS+1 <= y) && (y <= Y_MAX);
	 
	 // Right score area
	 parameter X_RIGHT_SCORE_AREA_L = X_MAX - 5;
	 parameter X_RIGHT_SCORE_AREA_R = X_MAX;
	 
	 // Right score area status signal
	 wire right_score_area_on;
	 assign right_score_area_on = (X_RIGHT_SCORE_AREA_L <= x) && (x <= X_RIGHT_SCORE_AREA_R) &&
											(VBVS+1 <= y) && (y <= Y_MAX);
	 // Paddle Control
    always @* begin
        y_pad_next = y_pad_reg;     // no move
        if(refresh_tick)
            if(up1 & (y_pad_t > VBVS+ PAD_VELOCITY))
                y_pad_next = y_pad_reg - PAD_VELOCITY;  // move up
            else if(down1 & (y_pad_b < (Y_MAX - PAD_VELOCITY)))
                y_pad_next = y_pad_reg + PAD_VELOCITY;  // move down
    end
	 // Paddle2 Control
    always @* begin
        y_pad2_next = y_pad2_reg;     // no move
        if(refresh_tick)
            if(up2 & (y_pad2_t > VBVS+ PAD2_VELOCITY))
                y_pad2_next = y_pad2_reg - PAD2_VELOCITY;  // move up
            else if(down2 & (y_pad_b < (Y_MAX - PAD_VELOCITY)))
                y_pad2_next = y_pad2_reg + PAD2_VELOCITY;  // move down
    end
	 

    // RGB control
    always @*
        if(~video_on)
            rgb = 12'h000;          // black(no value) outside display area
        else
		  
            if(sq_on)
                rgb = SQ_RGB;       // yellow square
				else if(bk_on)
					 rgb = BK_RGB;   /////磚塊區
				else if(pad_on)
					 rgb = PAD_RGB;
				else if(pad2_on)
					 rgb = PAD2_RGB;
				else if (left_score_area_on)
					 rgb = LEFT_SCORE_AREA_RGB;
				else if (right_score_area_on)
					 rgb = RIGHT_SCORE_AREA_RGB;
            else
                rgb = BG_RGB;       // blue background
	
	 
	 always@(posedge div_clk or negedge reset) begin
		if(!reset) begin
			BRICK_VELOCITY_POS <= 10'd0;
			BRICK_VELOCITY_NEG <= -10'd0;
		end
		else begin
			BRICK_VELOCITY_POS <= BRICK_VELOCITY_POS + 10'd2;
			BRICK_VELOCITY_NEG <= BRICK_VELOCITY_NEG - 10'd2;
		end
	end
			
endmodule






