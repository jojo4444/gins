#include "solve/algo.h"

#include "solve/low/Low.h"
#include "solve/lowPlus/LowPlus.h"
#include "solve/medium/medium.h"

#include <iostream>
#include <iomanip>
#include <map>

enum class Type {
    Help,
    Exit,
    Bad,
    Low,
    LowPlus,
    Medium,
    All,
};

std::map<std::string, Type> algo = {
        {"help", Type::Help},
        {"low", Type::Low},
        {"lowplus", Type::LowPlus},
        {"medium", Type::Medium},
        {"all", Type::All},
};

std::tuple<Type, int> getToken() {
    std::cout << ">>>" << std::flush;

    std::string s;
    getline(std::cin, s);

    std::vector<std::string> tokens;
    int n = (int) s.size();
    if (n == 0) {
        return std::make_tuple(Type::Bad, 0);
    }

    for (int i = 0; i < n;) {
        if (s[i] == ' ') {
            ++i;
            continue;
        }


        int j = i;
        while (j < n && s[j] != ' ') {
            ++j;
        }
        std::string token = s.substr(i, j - i);

        if (!token.empty()) {
            std::for_each(token.begin(), token.end(), [](char &c) { c = (char) tolower(c); });
            tokens.push_back(token);
        }

        i = j;
    }

    if (tokens.size() == 1 && tokens[0] == "help") {
        return std::make_tuple(Type::Help, 0);
    }

    if (tokens.size() == 1 && tokens[0] == "exit") {
        return std::make_tuple(Type::Exit, 0);
    }

    if (tokens.size() != 2) {
        return std::make_tuple(Type::Bad, 0);
    }

    auto it = algo.find(tokens[0]);
    if (it == algo.end()) {
        return std::make_tuple(Type::Bad, 0);
    }

    try {
        int points = std::stoi(tokens[1]);
        if (points > 0) {
            return std::make_tuple(it->second, points);
        } else {
            return std::make_tuple(Type::Bad, 0);
        }
    }
    catch (std::exception const &ex) {
        return std::make_tuple(Type::Bad, 0);
    }
}

void writeHelp() {
    std::string msg = R""""(
        using: [type] [points]
        type:
            [string]: low, lowplus, medium, all (Low = lOw = ... ignoring low/up)
        points:
            [int]: greater 0

        use type "help" without points for read this page
        use type "exit" without points for exit
    )"""";
    std::cout << msg << std::endl;
}

void writeStat(ll checksum, ll inside, ld sec, const std::string &msg) {
    std::cout << "\n";
    std::cout << msg << "\n";
    std::cout << "    checksum = " << checksum << "\n";
    std::cout << "    inside = " << inside << "\n";
    std::cout << "    time = " << std::setprecision(9) << std::fixed << sec << "s" << std::endl;
}

template<typename T>
void run(int points, int seed, const std::string& name) {
    T a;
    auto msg = "algo: " + name;

    auto[checksum, inside, sec, err] = calculateAlgo(a, points, seed);
    if (!err) {
        err.wrap(msg).log();
        return;
    }

    writeStat(checksum, inside, sec, msg);
}

void event(Type t, int points) {
    static std::mt19937 eng(4);
    int seed = (int) eng() % 100000;

    switch (t) {
        case Type::Exit:
            std::cout << "ZA WARUDO TOMARE TOKIA" << std::endl;
            exit(0);
            break;
        case Type::Help:
            writeHelp();
            break;
        case Type::Bad:
            std::cout << "incorrect input ¯\\_(ツ)_/¯" << std::endl;
            break;
        case Type::Low:
            run<Low>(points, seed, "low");
            break;
        case Type::LowPlus:
            run<LowPlus>(points, seed, "lowPlus");
            break;
        case Type::Medium:
            run<Medium>(points, seed, "medium");
            break;
        case Type::All:
            run<Low>(points, seed, "low");
            run<LowPlus>(points, seed, "lowPlus");
            run<Medium>(points, seed, "medium");
            break;
    }
}

int main() {
    writeHelp();

    while (true) {
        auto[type, points] = getToken();
        event(type, points);
    }

    return 0;
}
