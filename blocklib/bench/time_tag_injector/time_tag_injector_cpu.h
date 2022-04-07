#pragma once

#include <gnuradio/bench/time_tag_injector.h>
#include <chrono>

namespace gr {
namespace bench {

class time_tag_injector_cpu : public time_tag_injector
{
public:
    time_tag_injector_cpu(block_args args)
        : sync_block("time_tag_injector"),
          time_tag_injector(args),
          d_itemsize(args.itemsize)
    {
        d_sample_period = std::chrono::duration<double>(args.interval);
    }
virtual work_return_code_t work(std::vector<block_work_input_sptr>& work_input,
                                    std::vector<block_work_output_sptr>& work_output) override;

protected:
    size_t d_itemsize;
    unsigned long d_samp_rate;
    std::chrono::time_point<std::chrono::steady_clock> d_start;
    std::chrono::duration<double> d_sample_period;

};

} // namespace bench
} // namespace gr