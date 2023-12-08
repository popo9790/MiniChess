#include <cstdlib>
#include <math.h>

#include "../state/state.hpp"
#include "./MCTS.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

const int INF = __INT32_MAX__;
const double C = sqrt(2);


// w := # of win; n := # of simulation; N := Total of # of simulation
double UCT_Function(int w, int n,int N){
    if(n == 0)
        return INF;
    else
        return (double)w/n + C * sqrt(log(N)/n);
}

void SelectNode(int w, int n){

}

void ExtandNode(){

}

std::pair<int, int> Rollout(){

}

std::pair<int, int> Backpropagation(){
    
}


Move MCTS::get_move(State *state, int depth){
    int w = 0, n = 0;
    if(!state->legal_actions.size())
        state->get_legal_actions();
    
    auto LegalAct = state->legal_actions;
    auto next = *state->legal_actions.begin();
    for(auto child = LegalAct.begin(); child != LegalAct.end(); ++child){
        
    }
}