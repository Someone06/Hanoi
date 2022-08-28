// Ensure assertions are enabled.
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <array>
#include <cassert>
#include <iostream>
#include <stack>

class IllegalMove : std::runtime_error {
public:
    explicit IllegalMove(const char *const message) : runtime_error(message) {}
};

class EmptyFromStack final : IllegalMove {
public:
    EmptyFromStack() : IllegalMove("Trying to move a ring from an empty stack."){};
};

class MovingBiggerRingOnSmallerRing final : IllegalMove {
public:
    MovingBiggerRingOnSmallerRing() : IllegalMove("Trying to place a bigger ring on top of a smaller ring.") {}
};

void move_ring(std::stack<int> &from, std::stack<int> &to) {
    if (from.empty()) throw EmptyFromStack();

    if (to.empty() || from.top() < to.top()) {
        to.push(from.top());
        from.pop();
    } else {
        throw MovingBiggerRingOnSmallerRing();
    }
}

void solve_hanoi(std::stack<int> &from, std::stack<int> &to, std::stack<int> &free, const int height) {
    constexpr int uintBitSize = sizeof(unsigned int) << 3;
    assert(height >= 0 && height < uintBitSize);
    const int oddHeight = height & 1;
    std::array<std::stack<int> *, 3> towers{};
    towers[0] = &from;
    towers[oddHeight + 1] = &to;
    towers[2 - oddHeight] = &free;

    const unsigned int totalSteps = 1u << height;
    for (unsigned int step = 1; step != totalSteps; ++step) {
        const int ring = uintBitSize - __builtin_clz(step ^ (step - 1));
        const int oddRingNumber = ring & 1;
        const unsigned int moved = (step >> ring) << oddRingNumber;
        const unsigned int fromIndex = moved % 3;
        const unsigned int toIndex = (fromIndex + (1u << oddRingNumber)) % 3;
        move_ring(*towers[fromIndex], *towers[toIndex]);
    }
}

int get_height() {
    constexpr int uintBitSize = sizeof(unsigned int) << 3;

    while (true) {
        std::cout << "Height: ";
        std::string input;
        std::getline(std::cin, input);

        int number{0};
        try {
            number = std::stoi(input);
        } catch (const std::invalid_argument &e) {
            std::cout << "Not a number.\n";
            continue;
        } catch (const std::out_of_range &e) {
            std::cout << "Out of range.\n";
            continue;
        }

        if (number <= 0 || number >= uintBitSize) {
            std::cout << "Out of range.\n";
            continue;
        }

        return number;
    }
}

void run_and_verify(const int height) {
    std::stack<int> from{};
    std::stack<int> to{};
    std::stack<int> empty{};
    for (int i = height; i >= 1; --i)
        from.push(i);

    solve_hanoi(from, to, empty, height);

    assert(from.empty());
    assert(to.size() == height);
    for (int i = 1; i <= height; ++i) {
        assert(to.top() == i);
        to.pop();
    }
    assert(empty.empty());
}

constexpr bool interactive =
#ifdef INTERACTIVE
        true
#else
        false
#endif
        ;

int main() {
    if constexpr (interactive) {
        const int height = get_height();
        run_and_verify(height);
    } else {
        for (int height = 1; height < sizeof(unsigned int) << 3; ++height) {
            std::cout << "Solving for height " << height << "." << std::endl;
            run_and_verify(height);
            std::cout << "Done." << std::endl;
        }
    }
}
