#pragma once

#include "evpp/inner_pre.h"

namespace evpp {
    class EventLoop;
    class EVPP_EXPORT InvokeTimer : public std::enable_shared_from_this<InvokeTimer> {
    public:
        typedef std::function<void()> Functor;
        static std::shared_ptr<InvokeTimer> Create(EventLoop* evloop,
            Duration timeout, const Functor& f);
        ~InvokeTimer();
        void Start();
    private:
        InvokeTimer(EventLoop* evloop, Duration timeout, const Functor& f);
        void AsyncWait(Duration timeout);
        void OnTimeout();
        void OnCanceled();
        void DeleteTimerEventWatcher();
        void Cancel();
    private:
        EventLoop* loop_;
        Duration timeout_;
        Functor functor_;
        TimerEventWatcher* timer_;
    };

    typedef std::shared_ptr<InvokeTimer> InvokeTimerPtr;
}