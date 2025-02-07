#pragma once

#include <karm-base/string.h>
#include <karm-fmt/fmt.h>
#include <karm-io/funcs.h>
#include <karm-io/traits.h>

namespace Karm::Text {

struct Emit {
    Io::TextWriter<Utf8> &_writer;
    size_t _ident = 0;
    size_t _total = 0;
    Error _error = OK;
    bool _newline = true;

    void _try(Result<size_t> result) {
        if (result) {
            _total += result.unwrap();
        } else {
            _error = result.none();
        }
    }

    void indent() {
        _ident++;
    }

    void indented(auto inner) {
        indent();
        inner();
        deindent();
    }

    void deindent() {
        if (_ident == 0) {
            panic("deident() underflow");
        }
        _ident--;
    }

    void newline() {
        if (!_error)
            return;

        _newline = true;
    }

    void insertNewline() {
        if (!_error)
            return;

        _try(_writer.writeRune('\n'));
        for (size_t i = 0; i < _ident; i++) {
            _try(_writer.writeStr("    "));
        }

        _newline = false;
    }

    void operator()(Rune r) {
        if (!_error)
            return;

        _try(_writer.writeRune(r));
    }

    void operator()(Str str) {
        if (!_error)
            return;

        if (_newline) {
            insertNewline();
        }

        _try(_writer.writeStr(str));
    }

    template <typename... Ts>
    void operator()(Str format, Ts &&...ts) {
        if (!_error)
            return;

        if (_newline) {
            insertNewline();
        }

        _try(Fmt::format(_writer, format, std::forward<Ts>(ts)...));
    }

    size_t total() {
        return _total;
    }
};

} // namespace Karm::Text
