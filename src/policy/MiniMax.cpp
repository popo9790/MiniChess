#include <cstdlib>

#include "../state/state.hpp"
#include "./MiniMax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

const int INF = __INT32_MAX__;

int getMax(const int lhs, const int rhs){
    return lhs > rhs ? rhs : lhs;
}
int getMin(const int lhs, const int rhs){
    return lhs < rhs ? rhs : lhs;
}

int getHeuristicMiniMax(State *state, int depth, bool MaximizingPlayer){
    if(depth == 0)
        return state->evaluate();
    
    if(!state->legal_actions.size())
        state->get_legal_actions();
    if(MaximizingPlayer){
        int val = INF * -1;
        for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); ++it){
            val = getMax(val, getHeuristicMiniMax(state->next_state(*it), depth - 1, false));
        }
        return val;
    } 
    else{
        int val = INF;
        for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); ++it){
            val = getMin(val, getHeuristicMiniMax(state->next_state(*it), depth - 1, true));
        }
        return val;
    }
}

Move MiniMax::get_move(State *state, int depth, bool MaximizingPlayer){
    if(!state->legal_actions.size())
        state->get_legal_actions();
    
    int minCheck = INF;
    Move next;
    for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); ++it){
        int tmp = getHeuristicMiniMax(state->next_state(*it), depth, MaximizingPlayer);
        if(tmp < minCheck)
        {
            minCheck = tmp;
            next = *it;
        }
    }
    return next;
}
