/* add_server.cpp */
#include "blackjack.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <time.h>
using namespace std;

string suit_name[] = {"Spade","Heart","Diamond","Club"};
string rank_name[] = {"0","1","2","3","4","5","6","7","8","9","10","J","Q","K","A"};

card deck[52];
int top;

//dealer's point
int dealer_point = 0;
//player's point
int player_point = 0;

card hole_card;

int *initialize_1_svc(void *argp, struct svc_req *rqstp) {
	cout<<"Initializing game..."<<endl;
    srand(time(NULL));

    for (int i = 0; i < 52; i++) {
        deck[i].suit = i / 13;
        deck[i].rank = i % 13 + 1;
		deck[i].point = std::min(deck[i].rank, 10);
    }
    random_shuffle(deck, deck + 52);
	top = 51;
	static int result;
    result = 0;
	player_point = 0;
	dealer_point = 0;
	hole_card = card();
	return &result;
}

int* get_player_points_1_svc(void* argp, struct svc_req *rqstp) {
	static int result;
	result = player_point;
	cout<<"player's point: "<<player_point<<endl;
	return &result;
}

int* get_dealer_points_1_svc(void* argp, struct svc_req *rqstp) {
	static int result;
	result = dealer_point;
	return &result;
}

card dealer_draw(bool face_up = true){
	card result = deck[top--];
	dealer_point += result.point;
	if(face_up){
		cout<<"Dealer draw a "<<rank_name[result.rank]<<" of "<<suit_name[result.suit]<<endl;
	}else{
		cout<<"Dealer draw a card"<<endl;
	}
	return result;
}
card* dealer_before_turn_1_svc(void* argp, struct svc_req *rqstp) {
	static card up_card = dealer_draw(true);
	hole_card = dealer_draw(false);
    return &up_card;
}

card *draw_for_player_1_svc(void* argp, struct svc_req *rqstp) {
    static card result;
	result = deck[top--];
	player_point += result.point;
    return &result;
}

//dealer's turn
char** dealer_turn_1_svc(void* argp, struct svc_req *rqstp) {
	ostringstream oss;
	while(dealer_point < 17) {
		card result = dealer_draw();
		oss<<"dealer draw a "<<rank_name[result.rank]<<" of "<<suit_name[result.suit]<<endl;
		oss<<"dealer's point: "<<dealer_point<<endl;
	}
	static char* result = new char[oss.str().length() + 1];
	strcpy(result, oss.str().c_str());
	return &result;
}

char** show_hole_card_1_svc(void* argp, struct svc_req *rqstp) {
	ostringstream oss;
	oss<<"Dealer's hole card is "<<rank_name[hole_card.rank]<<" of "<<suit_name[hole_card.suit]<<endl;
	static char* result = new char[oss.str().length() + 1];
	strcpy(result, oss.str().c_str());
	return &result;
}

//finish the game
char** check_win_1_svc(void* argp, struct svc_req *rqstp) {
	ostringstream oss;
	if (player_point > 21) {
		oss<<"player busts"<<endl;
		oss<<"dealer wins"<<endl;
	} else if (dealer_point > 21) {
		oss<<"dealer busts"<<endl;
		oss<<"player wins"<<endl;
	} else if (player_point > dealer_point) {
		oss<<"player points: "<<player_point<<endl;
		oss<<"dealer points: "<<dealer_point<<endl;
		oss<<"player wins"<<endl;
		oss<<"dealer loses"<<endl;
	} else if (player_point < dealer_point) {
		oss<<"player points: "<<player_point<<endl;
		oss<<"dealer points: "<<dealer_point<<endl;
		oss<<"dealer wins"<<endl;
		oss<<"player loses"<<endl;
	} else {
		oss<<"player points: "<<player_point<<endl;
		oss<<"dealer points: "<<dealer_point<<endl;
		oss<<"draw"<<endl;
	}
	static char* result = new char[oss.str().length() + 1];
	strcpy(result, oss.str().c_str());
	return &result;
}