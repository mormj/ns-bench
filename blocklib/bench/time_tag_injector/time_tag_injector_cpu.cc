#include "time_tag_injector_cpu.h"

namespace gr {
namespace bench {

time_tag_injector::sptr time_tag_injector::make_cpu(const block_args& args)
{
    return std::make_shared<time_tag_injector_cpu>(args);
}

work_return_code_t
time_tag_injector_cpu::work(std::vector<block_work_input_sptr>& work_input,
                            std::vector<block_work_output_sptr>& work_output)
{
    auto in = work_input[0]->items<uint8_t>();
    auto out = work_output[0]->items<uint8_t>();
    auto noutput_items = work_output[0]->n_items;

    // The time at which the work function is called
    auto now = std::chrono::steady_clock::now();
    auto next_tag = d_start + d_sample_period;

    if (now > next_tag) {
        d_start = std::chrono::steady_clock::now();
        // Drop a tag right in the middle of the buffer
        const auto p1 = std::chrono::system_clock::now();
        auto diff =
            std::chrono::duration_cast<std::chrono::microseconds>(p1.time_since_epoch())
                .count();

        // std::cout << "adding tag at " << nitems_written(0) + noutput_items / 2 << "
        // with val " << diff << std::endl;
        work_output[0]->add_tag(work_output[0]->nitems_written(), // + noutput_items / 2,
                                pmtf::map({
                                    { "time", diff },
                                }));
    }

    std::memcpy(out, in, noutput_items * d_itemsize);

    // Tell runtime system how many output items we produced.
    produce_each(noutput_items, work_output);
    return work_return_code_t::WORK_OK;
}


} // namespace bench
} // namespace gr