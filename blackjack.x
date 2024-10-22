program BLACKJACK {
    version BLACKJACK_VERS {
		int initialize() = 0;
		card draw_for_player() = 1;
		card dealer_before_turn() = 2;
		string dealer_turn() = 3;
		string check_win() = 4;
		string show_hole_card() = 5;
		int get_player_points() = 6;
		int get_dealer_points() = 7;
		int player_choice(int) = 8;
    } = 1;
} = 0x20000001;

struct card {
    int rank;
    int suit;
	int point;
};

