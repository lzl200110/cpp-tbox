#include <gtest/gtest.h>
#include "semaphore.hpp"
#include <tbox/base/scope_exit.hpp>
#include <tbox/event/timer_event.h>

using namespace std;
using namespace tbox;
using namespace tbox::event;
using namespace tbox::coroutine;

/**
 * 生产者 -- 消费者测试
 */
TEST(Semaphore, TwoRoutines_ProduceAndConsumer)
{
    Loop *sp_loop = event::Loop::New();
    SetScopeExitAction([sp_loop]{ delete sp_loop;});

    Scheduler sch(sp_loop);

    Semaphore sem(sch, 0);

    int times = 200;
    int count = 0;
    //! 生产者，将 send_vec 中的数据逐一发送到 ch
    auto routine1_entry = [&] (Scheduler &sch) {
        for (int i = 0; i < times; ++i) {
            sem.release();
            sch.yield();
        }
    };

    //! 消费者，从 ch 中读取数据，存入到 recv_vec 中
    auto routine2_entry = [&] (Scheduler &sch) {
        while (!sch.isCanceled()) {
            sem.acquire();
            ++count;
        }
    };

    sch.create(routine1_entry);
    sch.create(routine2_entry);

    sp_loop->exitLoop(chrono::milliseconds(100));
    sp_loop->runLoop();

    //! 检查发送的数据与接收到数据是否对应
    EXPECT_EQ(times, count);
}

/**
 * 用定时器定时向ch发送数据，协程循环接收数据
 *
 * 主要测试主协程的loop事件与子协程之间是否存在冲突
 */
TEST(Semaphore, TimerProduceAndConsumer)
{
    Loop *sp_loop = event::Loop::New();
    SetScopeExitAction([sp_loop]{ delete sp_loop;});

    Scheduler sch(sp_loop);
    Semaphore sem(sch, 0);

    int times = 10;
    int count = 0;

    int index = 0;
    auto timer = sp_loop->newTimerEvent();
    timer->initialize(chrono::milliseconds(10), Event::Mode::kPersist);
    timer->setCallback(
        [&] {
            if (index < times) {
                sem.release();
                ++index;
            } else {
                sp_loop->exitLoop();
            }
        }
    );
    timer->enable();

    //! 消费者，从 ch 中读取数据，存入到 recv_vec 中
    auto routine2_entry = [&] (Scheduler &sch) {
        while (!sch.isCanceled()) {
            sem.acquire();
            ++count;
        }
    };

    sch.create(routine2_entry);

    sp_loop->runLoop();

    //! 检查发送的数据与接收到数据是否对应
    EXPECT_EQ(count, times);
}
