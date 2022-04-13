#include "solve/algo.h"

#include "solve/low/Low.h"
#include "solve/lowPlus/LowPlus.h"
#include "solve/medium/medium.h"
#include "solve/mediumPlus/mediumPlus.h"
#include "solve/mediumPlusPlus/mediumPlusPlus.h"
#include "solve/hard/Hard.h"

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
    MediumPlus,
    MediumPlusPlus,
    Hard,
    All,
    Fast,
};

const std::string low = "low";
const std::string low_p = "low+";
const std::string medium = "medium";
const std::string medium_p = "medium+";
const std::string medium_pp = "medium++";
const std::string hard = "hard";

std::map<std::string, Type> algo = {
        {"help",   Type::Help},
        {low,      Type::Low},
        {low_p,    Type::LowPlus},
        {medium,   Type::Medium},
        {medium_p, Type::MediumPlus},
        {medium_pp, Type::MediumPlusPlus},
        {hard, Type::Hard},
        {"all",    Type::All},
        {"fast",   Type::Fast},
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

    if (tokens[0] == "help") {
        return std::make_tuple(Type::Help, 0);
    }

    if (tokens[0] == "exit") {
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
            [string]: )"""" +
            low + ", " + low_p + ", " + medium + ", " + medium_p + ", " + medium_pp + ", " + hard
            + R""""(, all, fast (ignore low/up)
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
void run(int points, int seed, const std::string &name) {
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
            run<Low>(points, seed, low);
            break;
        case Type::LowPlus:
            run<LowPlus>(points, seed, low_p);
            break;
        case Type::Medium:
            run<Medium>(points, seed, medium);
            break;
        case Type::MediumPlus:
            run<MediumPlus>(points, seed, medium_p);
            break;
        case Type::MediumPlusPlus:
            run<MediumPlusPlus>(points, seed, medium_pp);
            break;
        case Type::Hard:
            run<Hard>(points, seed, hard);
            break;
        case Type::All:
            run<Low>(points, seed, low);
            run<LowPlus>(points, seed, low_p);
            run<Medium>(points, seed, medium);
            run<MediumPlus>(points, seed, medium_p);
            run<MediumPlusPlus>(points, seed, medium_pp);
            run<Hard>(points, seed, hard);
            break;
        case Type::Fast:
            run<Medium>(points, seed, medium);
            run<MediumPlus>(points, seed, medium_p);
            run<MediumPlusPlus>(points, seed, medium_pp);
            run<Hard>(points, seed, hard);
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
