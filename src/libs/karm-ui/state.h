#pragma once

#include <karm-base/func.h>

#include "react.h"

namespace Karm::Ui {

template <typename T>
struct _State : public React<_State<T>> {
    struct Wrap {
        _State<T> &_s;

        Wrap(_State<T> &s) : _s(s) {}

        void update(T t) {
            _s._value = t;
            _s.shouldRebuild();
        }

        T const &value() const {
            return _s._value;
        }

        Func<void()> bind(auto f) {
            return [*this, f] mutable {
                update(f(value()));
            };
        }

        void dispatch(auto f) { update(f(value())); }
    };

    T _value;
    Func<Child(Wrap)> _build;

    _State(T initial, Func<Child(Wrap)> build)
        : _value(initial), _build(std::move(build)) {}

    Child build() override {
        return _build(Wrap(*this));
    }
};

template <typename T>
using State = typename _State<T>::Wrap;

template <typename T>
Child state(T initial, Func<Child(State<T>)> build) {
    return makeStrong<_State<T>>(initial, std::move(build));
}

} // namespace Karm::Ui
