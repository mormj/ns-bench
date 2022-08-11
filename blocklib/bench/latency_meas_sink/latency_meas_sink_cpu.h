#pragma once

#include <gnuradio/bench/latency_meas_sink.h>
#include <chrono>
#include <thread>

namespace gr {
namespace bench {

class latency_meas_sink_cpu : public latency_meas_sink
{
public:
    latency_meas_sink_cpu(block_args args);
    virtual work_return_t work(work_io& wio);


    bool start() override
    {
        d_start = std::chrono::steady_clock::now();
        return true;
    }

    double avg_latency() { return d_avg_latency; }

private:
    size_t d_itemsize;
    unsigned int d_samp_rate;
    bool d_blocking = true;

    std::vector<int64_t> d_latency_estimates;
    double d_avg_latency = 0.0;
    int64_t d_num_latency = 0;
    bool d_started = false;
    std::chrono::duration<double> d_sample_period;
    uint64_t d_total_samples = 0;
    std::chrono::time_point<std::chrono::steady_clock> d_start;
};

} // namespace bench
} // namespace gr