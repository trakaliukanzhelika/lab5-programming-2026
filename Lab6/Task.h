#pragma once

#include <coroutine>
class Task {
public:
    struct promise_type {
        Task get_return_object();
        std::suspend_always initial_suspend() const noexcept;
        std::suspend_always final_suspend() const noexcept;
        void return_void() const noexcept;
        void unhandled_exception() const;
    };

    explicit Task(std::coroutine_handle<promise_type> handle);
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    ~Task();

    void resume() const;
    std::coroutine_handle<> handle() const;

private:
    std::coroutine_handle<promise_type> _handle;
};