#pragma once

#include <gnuradio/bench/time_tag_injector.h>
#include <chrono>

namespace gr {
namespace bench {

class time_tag_injector_cpu : public time_tag_injector
{
public:
    time_tag_injector_cpu(block_args args);
    virtual work_return_t work(work_io& wio);


protected:
    size_t d_itemsize;
    unsigned long d_samp_rate;
    std::chrono::time_point<std::chrono::steady_clock> d_start;
    std::chrono::duration<double> d_sample_period;
};

} // namespace bench
} // namespace gr