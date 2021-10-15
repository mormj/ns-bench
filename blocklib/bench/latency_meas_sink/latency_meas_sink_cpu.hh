#pragma once

#include <gnuradio/bench/latency_meas_sink.hh>
#include <chrono>
#include <thread>

namespace gr {
namespace bench {

class latency_meas_sink_cpu : public latency_meas_sink
{
public:
    latency_meas_sink_cpu(block_args args) : sync_block("latency_meas_sink"), latency_meas_sink(args),
    d_itemsize(args.itemsize), d_samp_rate(args.samp_rate), d_blocking(args.blocking) {}
    virtual work_return_code_t work(std::vector<block_work_input>& work_input,
                                    std::vector<block_work_output>& work_output) override;

    bool start() override{
        d_start = std::chrono::steady_clock::now();
        return true;
    }
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