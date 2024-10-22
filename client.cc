/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "blackjack.h"
#include <iostream>
#define zxc(x) cerr<<(#x)<<" = "<<(x)<<endl;

using namespace std;
CLIENT *clnt;

//name of suit
string suit_name[] = {"Spade","Heart","Diamond","Club"};
string rank_name[] = {"0","1","2","3","4","5","6","7","8","9","10","J","Q","K","A"};

void initialize_deck(){
	void* a;
	if(initialize_1(&a,clnt)== (int *) NULL){
		clnt_perror (clnt, "call failed");
	}
}

card player_draw(){
	void* a;
	card *result;
	result = draw_for_player_1(&a,clnt);
	if(result == (card *) NULL){
		clnt_perror (clnt, "call failed");
	}
	cout<<"You draw a "<<rank_name[result->rank]<<" of "<<suit_name[result->suit]<<endl;
	return *result;
}

string _dealer_turn(){
	void* a;
	char **result;
	result = dealer_turn_1(&a, clnt);
	if(result == (char **) NULL){
		clnt_perror (clnt, "call failed");
	}
	return *result;
}

card _dealer_before_turn(){
	void* a;
	card *result;
	result = dealer_before_turn_1(&a,clnt);
	if(result == (card*) NULL){
		clnt_perror (clnt, "call failed");
	}
	return *result;
}

string _check_win(){
	void* a;
	char **result;
	result = check_win_1(&a, clnt);
	if(result == (char **) NULL){
		clnt_perror (clnt, "call failed");
	}
	return *result;
}

string _show_hole_card(){
	void* a;
	char **result;
	result = show_hole_card_1(&a, clnt);
	if(result == (char **) NULL){
		clnt_perror (clnt, "call failed");
	}
	return *result;
}

int _get_player_points(){
	void* a;
	int *result;
	result = get_player_points_1(&a, clnt);
	if(result == (int *) NULL){
		clnt_perror (clnt, "call failed");
	}
	return *result;
}

int _get_dealer_points(){
	void* a;
	int *result;
	result = get_dealer_points_1(&a, clnt);
	if(result == (int *) NULL){
		clnt_perror (clnt, "call failed");
	}
	return *result;
}

void blackjack_1(char *host)
{
	clnt = clnt_create (host, BLACKJACK, BLACKJACK_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

	initialize_deck();
	card up_card = _dealer_before_turn();
	cout<<"Dealer draw a "<<rank_name[up_card.rank]<<" of "<<suit_name[up_card.suit]<<endl;
	cout<<"Dealer draw a hidden card"<<endl;
	
	player_draw();
	player_draw();

	while(1){
		cout<<"Current points: "<<_get_player_points()<<endl;
		cout<<"Hit or Stand? (h/s)\n";
		char input;
		cin>>input;
		if(input=='h'){
			player_draw();
			int tot_points = _get_player_points();
			cout<<"Your points: "<<tot_points<<endl;
			if(tot_points>21){
				cout<<"Your points exceed 21."<<endl;
				cout<<"You lose."<<endl;
				break;
			}else if(tot_points==21){
				cout<<"You win."<<endl;
				break;
			}
		}else if(input=='s'){
			cout<<_show_hole_card()<<endl;
			cout<<_dealer_turn()<<endl;
			cout<<_check_win()<<endl;
			break;
		}else{
			cout<<"Invalid input"<<endl;
		}
	}

	clnt_destroy (clnt);
}


int main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	blackjack_1 (host);
exit (0);
}
