#include <cstdlib>

#include "../state/state.hpp"
#include "./AlphaBeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

const int INF = __INT32_MAX__;

int getMax_AlphaBeta(const int lhs, const int rhs){
    return lhs < rhs ? rhs : lhs;
}
int getMin_AlphaBeta(const int lhs, const int rhs){
    return lhs > rhs ? rhs : lhs;
}

int getHeuristicAlphaBeta(State *state, int depth, int alpha, int beta, bool MaximizingPlayer){
    if(!state->legal_actions.size())
        state->get_legal_actions();

    if(state->game_state == WIN)
    {
        if(MaximizingPlayer)
            return INF;
        else
            return -1 * INF;
    }

    if(depth == 0 || state->legal_actions.size() == 0 || state->game_state == DRAW)
        return state->evaluate();
    
    if(MaximizingPlayer){
        int val = INF * -1;
        for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); ++it){
            val = getMax_AlphaBeta(val, getHeuristicAlphaBeta(state->next_state(*it), depth - 1, alpha, beta, false));
            alpha = getMax_AlphaBeta(val, alpha);
            if(alpha >= beta)
                break;
        }
        return val;
    } 
    else{
        int val = INF;
        for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); ++it){
            val = getMin_AlphaBeta(val, getHeuristicAlphaBeta(state->next_state(*it), depth - 1, alpha, beta, true));
            beta = getMin_AlphaBeta(val, beta);
            if(alpha >= beta)
                break;
        }
        return val;
    }
}

Move AlphaBeta::get_move(State *state, int depth, bool MaximizingPlayer){
    if(!state->legal_actions.size())
        state->get_legal_actions();
    
    int maxCheck = -1 * INF;
    int minCheck = INF;
    Move next = *state->legal_actions.begin();
    for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); ++it){
        int tmp = getHeuristicAlphaBeta(state->next_state(*it), depth - 1, maxCheck, minCheck, MaximizingPlayer);
        if(MaximizingPlayer){
            if(tmp > maxCheck)
            {
                maxCheck = tmp;
                next = *it;
            }
        }
        else{
            if(tmp < minCheck)
            {
                minCheck = tmp;
                next = *it;
            }
        }
    }
    return next;
}