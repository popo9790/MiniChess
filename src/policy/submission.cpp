#include <cstdlib>

#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

const int INF = __INT32_MAX__;

int getMax_AlphaBeta_s(const int lhs, const int rhs){
    return lhs <= rhs ? rhs : lhs;
}
int getMin_AlphaBeta_s(const int lhs, const int rhs){
    return lhs >= rhs ? rhs : lhs;
}

int getHeuristicAlphaBeta_s(State *state, int depth, int alpha, int beta){
    if(state->game_state == WIN)
    {
        if(state->player == 0)
            return INF;
        else
            return -1 * INF;
    }

    if(depth == 0 || state->game_state == DRAW || state->legal_actions.size() == 0)
        return state->evaluate();
    
    if(state->player == 0){
        int val = INF * -1;
        for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); ++it){
            val = getMax_AlphaBeta_s(val, getHeuristicAlphaBeta_s(state->next_state(*it), depth - 1, alpha, beta));
            alpha = getMax_AlphaBeta_s(val, alpha);
            if(alpha >= beta)
                break;
        }
        return val;
    } 
    else{
        int val = INF;
        for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); ++it){
            val = getMin_AlphaBeta_s(val, getHeuristicAlphaBeta_s(state->next_state(*it), depth - 1, alpha, beta));
            beta = getMin_AlphaBeta_s(val, beta);
            if(alpha >= beta)
                break;
        }
        return val;
    }
}

Move submission::get_move(State *state, int depth, bool MaximizingPlayer){
    if(!state->legal_actions.size())
        state->get_legal_actions();
    
    int maxCheck = -1 * INF;
    int minCheck = INF;
    Move next = *state->legal_actions.begin();
    for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); ++it){
        int tmp = getHeuristicAlphaBeta_s(state->next_state(*it), depth, maxCheck, minCheck);
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