//
// Created by jojo on 24.03.2022.
//

#ifndef GINS_ERRORS_H
#define GINS_ERRORS_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>

namespace errors {
    class [[nodiscard]] error {
    public:
        error() = default;

        explicit error(const std::string &msg);

        error &withStack(const error &e);

        error &wrap(const std::string &msg);

        void log() const;

        /// https://en.cppreference.com/w/cpp/language/attributes/nodiscard
        [[nodiscard]] const std::vector<std::string> &getStack() const;

        bool operator!() const;

    private:
        std::vector<std::string> stack;
    };

    const error NIL;

    error NewError(const std::string &msg);

    error NewErrorf(const char *fmt, ...);

    error Wrap(error e, const std::string &msg);

    error WitchStack(const error &e1, const error &e2);
}

#endif //GINS_ERRORS_H
