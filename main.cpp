#include <iostream>

class NFA {
    std::vector<int> currentStates = {0};
    std::vector<int> finalStates;
    std::vector<char> sigma;
    std::vector<int> states;
    std::vector<std::tuple<int, char, int>> transitions;

public:
    NFA (std::vector<int> finalStates, std::vector<char> sigma, std::vector<int> states,
    std::vector<std::tuple<int, char, int>> transitions) : finalStates(finalStates),
    sigma(sigma), states(states), transitions(transitions) {
        sigma.push_back('$');
    }

    ~NFA () = default;

    std::vector<int> exists (const int &state, const char &sigma) {
        std::vector<int> nextStates;
        for (auto transition : transitions)
            if (std::get<0>(transition) == state && std::get<1>(transition) == sigma)
                nextStates.push_back(std::get<2>(transition));

        return nextStates;
    }

    void accepts (const std::string &input) {
        currentStates = {0};

        for (char symbol : input) {
            std::vector<int> nextStates;

            for(int state : currentStates) {
                std::vector<int> states = exists(state, symbol);
                for(int cursor : states)
                    nextStates.push_back(cursor);
            }
            currentStates = nextStates;
        }

        for (int state : currentStates)
            if (std::find(finalStates.begin(), finalStates.end(), state) != finalStates.end())
                return print(true);

        return print(false);
    }

    void print(const bool &accepts) {
        if (accepts == true)
            std::cout << "It accepts.\n";
        else std::cout << "It doesn't accept.\n";
    }
};

int main() {
    NFA zamfimat({3}, {'a', 'b'}, {0, 1, 2, 3}, {{0, '0', 0}, {0, '1', 0}, {0, '1', 1},
                                                 {0, '$', -1},{1, '0', 2}, {1, '1', -1}, {1, '$', 2}, {2, '0', -1}, {2, '1', 3},
                                                 {2, '$', -1}, {3, '0', 3}, {3, '1', 3}, {3, '$', -1}});

    zamfimat.accepts("0101"); // It accepts.
    zamfimat.accepts("0111"); // It doesn't accept.
    zamfimat.accepts("$$$$"); // It doesn't accept.
    zamfimat.accepts("0011$1001"); // It accepts.
    zamfimat.accepts("0011$1001"); // It accepts.
    zamfimat.accepts("0101"); // It accepts.
    zamfimat.accepts("11"); // It doesn't accept.
    zamfimat.accepts("00$1$11101"); // It doesn't accept.
    zamfimat.accepts("111001$1"); // It accepts.
    return 0;
}