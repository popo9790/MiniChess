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

const int INF = INT_MAX;

int getMax(const int lhs, const int rhs){
    return lhs < rhs ? rhs : lhs;
}
int getMin(const int lhs, const int rhs){
    return lhs > rhs ? rhs : lhs;
}

int getHeuristicMiniMax(State *state, int depth){
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
            val = getMax(val, getHeuristicMiniMax(state->next_state(*it), depth - 1));
        }
        return val;
    } 
    else{
        int val = INF;
        for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); ++it){
            val = getMin(val, getHeuristicMiniMax(state->next_state(*it), depth - 1));
        }
        return val;
    }
}

Move MiniMax::get_move(State *state, int depth, bool MaximizingPlayer){
    if(!state->legal_actions.size())
        state->get_legal_actions();

    int maxCheck = -1 * INF;
    int minCheck = INF;
    int next_idx = 0;

    int cnt = 0;
    for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); ++it, ++cnt){
        int tmp = getHeuristicMiniMax(state->next_state(*it), depth );
        if(MaximizingPlayer){
            if(tmp > maxCheck)
            {
                maxCheck = tmp;
                next_idx = cnt;
            }
        }
        else{
            if(tmp < minCheck)
            {
                minCheck = tmp;
                next_idx = cnt;
            }
        }
    }
    return state->legal_actions[next_idx];
}
