#include "Task.h"

Task Task::promise_type::get_return_object() {
    return Task{ std::coroutine_handle<promise_type>::from_promise(*this) };
}

std::suspend_always Task::promise_type::initial_suspend() const noexcept {
    return {};
}

std::suspend_always Task::promise_type::final_suspend() const noexcept {
    return {};
}

void Task::promise_type::return_void() const noexcept {}

void Task::promise_type::unhandled_exception() const {
    throw;
}

Task::Task(std::coroutine_handle<promise_type> handle) : _handle(handle) {}

Task::~Task() {
    _handle.destroy();
}

void Task::resume() const {
    _handle.resume();
}

std::coroutine_handle<> Task::handle() const {
    return _handle;
}