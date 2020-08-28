class baseball_animations{
public:

byte curr_bases;
int frames_left;
int curr_idx [3];
bool add_run;
bool start_count_runs;


bool play_frame(){
  add_run = false;
  
	if(frames_left==0) return false;
  print_idx();
	curr_bases= curr_idx_value();
 if (! runner_on_home(curr_idx_value())) start_count_runs = true;
 curr_idx[2]++;
 
 if (runner_on_home(curr_bases) & ! runner_on_home(curr_idx_value()) & frames_left>1 &start_count_runs) add_run = true;
	frames_left--;
  
	return true;
}

bool runner_on_home(byte base){
  return bitRead(base, 3);
}

void print_idx(){
  Serial.print(curr_idx[0]);
  Serial.print(", ");
  Serial.print(curr_idx[1]);
   Serial.print(", ");
  Serial.println(curr_idx[2]);
}

void init_animation(byte start_bases, int hit_num){

	curr_idx[0] = (start_bases & 0b0111);
	curr_idx[1] = hit_num-1;
	curr_idx[2] = 0;
	frames_left= curr_idx_value();
  print_idx();
	curr_idx[2]++;
  add_run= false;
  start_count_runs=false;
	
}




byte curr_idx_value() { return animation_LUT [curr_idx[0]] [curr_idx[1]] [curr_idx[2]] ;}

byte animation_LUT [8][4][20]= { 
// First element in array is animation length
// 
	{ // 1000 = Starting Bases 
		{ 3, 0b0100, 0b0100, 0b1100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SINGLE
		{ 4, 0b0100, 0b0010, 0b0010, 0b1010, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // DOUBLE
		{ 5, 0b0100, 0b0010, 0b0001, 0b0001, 0b1001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // TRIPLE
		{ 7, 0b0100, 0b0010, 0b0001, 0b1000, 0b0000, 0b0000, 0b1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} // HR

	},

	{ // 1001 = Starting Bases 
		{ 3, 0b0101, 0b0101, 0b1101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SINGLE
		{ 4, 0b0101, 0b0011, 0b0011, 0b1011, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // DOUBLE
		{ 6, 0b0101, 0b0011, 0b1010, 0b0001, 0b0001, 0b1001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // TRIPLE
		{ 8, 0b0101, 0b0011, 0b1010, 0b0001, 0b1000, 0b0000, 0b0000, 0b1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // HR
	},

	{ // 1010 = Starting Bases 
		{ 3, 0b0110, 0b0110, 0b1110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SINGLE
		{ 5, 0b0110, 0b0101, 0b0011, 0b0011, 0b1011, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // DOUBLE
		{ 7, 0b0110, 0b0101, 0b0011, 0b1010, 0b0001, 0b0001, 0b1001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // TRIPLE
		{ 9, 0b0110, 0b0101, 0b0011, 0b1010, 0b0001, 0b1000, 0b0000, 0b0000, 0b1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // HR
	},

	{ // 1011 = Starting Bases 
		{ 3, 0b0111, 0b0111, 0b1111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SINGLE
		{ 6, 0b0111, 0b1110, 0b0101, 0b0011, 0b0011, 0b1011, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // DOUBLE
		{ 8, 0b0111, 0b1110, 0b0101, 0b0011, 0b1010, 0b0001, 0b0001, 0b1001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // TRIPLE
		{ 10, 0b0111, 0b1110, 0b0101, 0b0011, 0b1010, 0b0001, 0b1000, 0b0000, 0b0000, 0b1000, 0, 0, 0, 0, 0, 0, 0}  // HR
	},

	{ // 1100 = Starting Bases 
		{ 4, 0b1010, 0b0110, 0b0110, 0b1110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SINGLE
		{ 6, 0b1010, 0b0110, 0b0101, 0b0011, 0b0011, 0b1011, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // DOUBLE
		{ 8, 0b1010, 0b0110, 0b0101, 0b0011, 0b1010, 0b0001, 0b0001, 0b1001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // TRIPLE
		{ 10, 0b1010, 0b0110, 0b0101, 0b0011, 0b1010, 0b0001, 0b1000, 0b0000, 0b0000, 0b1000, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // HR
	},

	{ // 1101 = Starting Bases 
		{ 4, 0b1011, 0b0111, 0b0111, 0b1111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SINGLE
		{ 7, 0b1011, 0b0111, 0b1110, 0b0101, 0b0011, 0b0011, 0b1011, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // DOUBLE
		{ 9, 0b1011, 0b0111, 0b1110, 0b0101, 0b0011, 0b1010, 0b0001, 0b0001, 0b1001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // TRIPLE
		{ 11, 0b1011, 0b0111, 0b1110, 0b0101, 0b0011, 0b1010, 0b0001, 0b1000, 0b0000, 0b0000, 0b1000, 0, 0, 0, 0, 0, 0, 0, 0}  // HR

	},


	{ // 1110 = Starting Bases 
		{ 5, 0b1101, 0b1011, 0b0111, 0b0111, 0b1111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SINGLE
		{ 8, 0b1101, 0b1011, 0b0111, 0b1110, 0b0101, 0b0011, 0b0011, 0b1011, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // DOUBLE
		{ 10, 0b1101, 0b1011, 0b0111, 0b1110, 0b0101, 0b0011, 0b1010, 0b0001, 0b0001, 0b1001, 0, 0, 0, 0, 0, 0, 0}, // TRIPLE
		{ 12, 0b1101, 0b1011, 0b0111, 0b1110, 0b0101, 0b0011, 0b1010, 0b0001, 0b1000, 0b0000, 0b0000, 0b1000, 0, 0, 0, 0, 0}  // HR  
	},

	{ // 1111 = Starting Bases 
		{ 7, 0b1111, 0b0111, 0b1110, 0b0110, 0b0101, 0b0011, 0b111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // SINGLE
		{ 13, 0b1111, 0b0111, 0b1110, 0b0110, 0b0101, 0b1100, 0b0100, 0b0010, 0b0110, 0b0101, 0b0011, 0b0011, 0b1011, 0, 0, 0, 0, 0, 0}, // DOUBLE
		{ 16, 0b1111, 0b0111, 0b1110, 0b0110, 0b0101, 0b1100, 0b0100, 0b0010, 0b0110, 0b0101, 0b1100, 0b0100, 0b0010, 0b0001, 0b0001, 0b1001, 0, 0, 0}, // TRIPLE
		{ 18, 0b1111, 0b0111, 0b1110, 0b0110, 0b0101, 0b1100, 0b0100, 0b0010, 0b0110, 0b0101, 0b1100, 0b0100, 0b0010, 0b0001, 0b1000, 0b0000, 0b0000, 0b1000, 0}  // HR  
	}
};

};
