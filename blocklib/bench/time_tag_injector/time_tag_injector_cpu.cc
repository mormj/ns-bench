#include "time_tag_injector_cpu.h"
#include "time_tag_injector_cpu_gen.h"

namespace gr {
namespace bench {

time_tag_injector_cpu::time_tag_injector_cpu(block_args args)
    : INHERITED_CONSTRUCTORS, d_itemsize(args.itemsize)
{
    d_sample_period = std::chrono::duration<double>(args.interval);
}

work_return_t time_tag_injector_cpu::work(work_io& wio)
{
    auto in = wio.inputs()[0].items<uint8_t>();
    auto out = wio.outputs()[0].items<uint8_t>();
    auto noutput_items = wio.outputs()[0].n_items;

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
        wio.outputs()[0].add_tag(wio.outputs()[0].nitems_written(), // + noutput_items / 2,
                                pmtf::map({
                                    { "time", diff },
                                }));
    }

    std::memcpy(out, in, noutput_items * d_itemsize);

    // Tell runtime system how many output items we produced.
    wio.produce_each(noutput_items);
    return work_return_t::OK;
}


} // namespace bench
} // namespace gr