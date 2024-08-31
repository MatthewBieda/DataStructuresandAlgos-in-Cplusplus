//Usage:
//unordered_map<State, int, StateHash> dpCache;

struct State {
    int r, c1, c2;
    bool operator==(const State& other) const {
        return r == other.r && c1 == other.c1 && c2 == other.c2;
    }
};

struct StateHash {
    size_t operator()(const State& state) const {
        return ((state.r * 100 + state.c1) * 100 + state.c2);
    }
};
