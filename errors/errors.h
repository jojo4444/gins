//
// Created by jojo on 24.03.2022.
//

#ifndef GINS_ERRORS_H
#define GINS_ERRORS_H

#include <string>
#include <vector>

namespace errors {
    class error {
    public:
        error() = default;

        explicit error(const std::string &msg);

        error &withStack(const error &e);

        error &wrap(const std::string &msg);

        /// https://en.cppreference.com/w/cpp/language/attributes/nodiscard
        [[nodiscard]] const std::vector<std::string> &getStack() const;

    private:
        std::vector<std::string> stack;
    };

    error NewError(std::string &msg);

    error Wrap(error e, std::string &msg);

    error WitchStack(const error &e1, const error& e2);
}

#endif //GINS_ERRORS_H
