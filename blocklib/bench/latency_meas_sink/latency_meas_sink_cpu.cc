#include "latency_meas_sink_cpu.hh"

namespace gr {
namespace bench {

latency_meas_sink::sptr latency_meas_sink::make_cpu(const block_args& args)
{
    return std::make_shared<latency_meas_sink_cpu>(args);
}

work_return_code_t
latency_meas_sink_cpu::work(std::vector<block_work_input>& work_input,
                            std::vector<block_work_output>& work_output)
{
    // auto now = std::chrono::system_clock::now();
    // if (!d_started) {
        // d_start = std::chrono::steady_clock::now();
        // d_started = true;
    // } else {
        if (d_blocking) {
            
            auto now = std::chrono::steady_clock::now();
            auto expected_time = d_start + d_sample_period * d_total_samples;
            // auto ms  =
            //     std::chrono::duration_cast<std::chrono::milliseconds>(expected_time - now)
            //         .count();
            // std::cout << "Blocking for " << ms << " ms " << std::endl;

            // wait until the last batch would have finished up processing
            if (expected_time > now) {
                auto limit_duration =
                    std::chrono::duration<double>(std::numeric_limits<long>::max());
                if (expected_time - now > limit_duration) {
                    GR_LOG_WARN(_logger,
                                "WARNING: Throttle sleep time overflow! You "
                                "are probably using a very low sample rate.");
                }
                std::this_thread::sleep_until(expected_time);
            }

            // std::cout << " ... Done blocking " << std::endl;
        }
    // }

    auto now = std::chrono::system_clock::now();
    // auto in = static_cast<const uint8_t*>(work_input[0].items());
    auto noutput_items = work_input[0].n_items;

    // std::cout << "noutput = " <<  noutput_items << std::endl;

    auto tags = work_input[0].tags_in_window(0, noutput_items);
    for (auto& t : tags) {

        auto microseconds =
            std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch())
                .count();
        // std::cout << "received: " << microseconds << std::endl;
        auto nr = work_input[0].nitems_read();
        auto diff = microseconds - pmt::to_long(t.value);
        // std::cout << d_samp_rate << " " << t.offset - nr << " " << 1e6 * (t.offset - nr)
        //           << " " << (1e6 * (t.offset - nr)) / d_samp_rate << std::endl;
        auto adjusted_diff = diff + (int64_t)((1e6 * (t.offset - nr)) / d_samp_rate);
        // std::cout << "received: " << microseconds << " - " << pmt::to_long(t.value)
        //           << " = " << diff << " --> " << adjusted_diff << std::endl;
        // d_latency_estimates.push_back(adjusted_diff);
        d_num_latency++;
        auto a = 1.0 / (double)d_num_latency;
        d_avg_latency = a * (double)adjusted_diff + (1.0 - a) * d_avg_latency;

        // std::cout << "time passed is " << diff << " microseconds" << std::endl;
    }

    d_total_samples += noutput_items;
    // Tell runtime system how many output items we produced.
    produce_each(noutput_items, work_output);
    return work_return_code_t::WORK_OK;
}


} // namespace bench
} // namespace gr