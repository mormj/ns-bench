#include <chrono>
#include <iostream>
#include <thread>

#include <gnuradio/bench/pdu_process.h>
#include <gnuradio/flowgraph.h>
#include <gnuradio/realtime.h>
#include <gnuradio/runtime.h>

#include <pmtf/wrap.hpp>

#include "CLI/App.hpp"
#include "CLI/Config.hpp"
#include "CLI/Formatter.hpp"

using namespace gr;

int main(int argc, char* argv[])
{
    uint64_t pdus = 10000;
    uint64_t pdu_size = 1024;
    std::string data_type = "rf32";
    unsigned int nblocks = 4;
    bool rt_prio = false;

    CLI::App app{ "App description" };

    // app.add_option("-h,--help", "display help");
    app.add_option("--pdus", pdus, "Number of PDUs");
    app.add_option("--pdu_size", pdu_size, "Size of data vector in PDU");
    app.add_option("--data_type",
                   data_type,
                   "Data Type of pdu vector (cf32, rf32, ri32, ri16, ru8)");
    app.add_option("--nblocks", nblocks, "Number of pdu process blocks");
    app.add_flag("--rt_prio", rt_prio, "Enable Real-time priority");

    CLI11_PARSE(app, argc, argv);

    if (rt_prio && gr::enable_realtime_scheduling() != rt_status_t::OK) {
        std::cout << "Error: failed to enable real-time scheduling." << std::endl;
    }

    {
        std::vector<block_sptr> msg_blks(nblocks);
        for (size_t i = 0; i < nblocks; i++) {
            size_t x = 0;
            if (i == nblocks - 1)
                x = pdus;

            // brute force do the type mappings here:
            if (data_type == "cf32")
                msg_blks[i] = bench::pdu_process<gr_complex>::make({ x });
            else if (data_type == "rf32")
                msg_blks[i] = bench::pdu_process<float>::make({ x });
            else if (data_type == "ri32")
                msg_blks[i] = bench::pdu_process<int32_t>::make({ x });
            else if (data_type == "ri16")
                msg_blks[i] = bench::pdu_process<int16_t>::make({ x });
            else if (data_type == "ru8")
                msg_blks[i] = bench::pdu_process<uint8_t>::make({ x });
            else
                throw std::runtime_error("unsupported data type");
        }

        auto fg = flowgraph::make();

        for (size_t i = 1; i < nblocks; i++) {
            fg->connect(msg_blks[i - 1], "out", msg_blks[i], "in");
        }

        auto rt = runtime::make();
        rt->initialize(fg);


        for (size_t p = 0; p < pdus; p++) {
            // brute force do the type mappings here:
            pmtf::pmt data;
            if (data_type == "cf32")
                data = pmtf::vector<gr_complex>(pdu_size,  gr_complex(123.4567, -987.432));
            else if (data_type == "rf32")
                data = pmtf::vector<float>(pdu_size, 99.12345);
            else if (data_type == "ri32")
                data = pmtf::vector<int32_t>(pdu_size, 0x87654321);
            else if (data_type == "ri16")
                data = pmtf::vector<int16_t>(pdu_size, 0xABAB);
            else if (data_type == "ru8")
                data = pmtf::vector<uint8_t>(pdu_size, 0x42);
            else
                throw std::runtime_error("unsupported data type");

            pmtf::pmt meta = pmtf::map{ { "field1", pmtf::pmt("value1") },
                                        { "field2", pmtf::pmt("value2") } };
            pmtf::pmt pdu = pmtf::map{ { "data", data }, { "meta", meta } };
            msg_blks[0]->input_message_port("in")->post(pdu);
        }

        auto t1 = std::chrono::steady_clock::now();

        rt->start();
        rt->wait();

        auto t2 = std::chrono::steady_clock::now();
        auto time =
            std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;

        std::cout << "[PROFILE_TIME]" << time << "[PROFILE_TIME]" << std::endl;
    }
}
