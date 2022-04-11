//
// Created by jojo on 24.03.2022.
//

#include "errors.h"

errors::error::error(const std::string &msg) {
    stack.push_back(msg);
}

errors::error &errors::error::withStack(const errors::error &e) {
    const std::vector<std::string> &e_stack = e.getStack();
    if (e_stack.empty()) {
        return *this;
    }
    size_t len = e_stack.size();
    for (size_t i = 0; i < len; ++i) {
        stack.push_back(e_stack[len - 1 - i]);
    }
    return *this;
}

const std::vector<std::string> &errors::error::getStack() const {
    return stack;
}

errors::error &errors::error::wrap(const std::string &msg) {
    if (!msg.empty()) {
        stack.push_back(msg);
    }
    return *this;
}

void errors::error::log() const {
    if (stack.empty()) {
        return;
    }
    std::cerr << "error = {\n";
    for (const std::string &e: stack) {
        std::cerr << "    " << e << ",\n";
    }
    std::cerr << "}\n";
}

bool errors::error::operator!() const {
    return !stack.empty();
}

errors::error errors::NewError(const std::string &msg) {
    return errors::error(msg);
}

/// https://en.cppreference.com/w/cpp/utility/variadic
/// http://www.cplusplus.com/reference/cstdio/vsprintf/
errors::error errors::NewErrorf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    /// super big buffer
    static char buff[1 << 10];
    vsprintf(buff, fmt, args);

    va_end(args);

    return NewError(buff);
}

errors::error errors::Wrap(errors::error e, const std::string &msg) {
    return e.wrap(msg);
}

errors::error errors::WitchStack(const errors::error &e1, const errors::error &e2) {
    errors::error e = e1;
    return e.withStack(e2);
}

