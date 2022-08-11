/* -*- c++ -*- */
/*
 * Copyright 2022 Josh Morman
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "pdu_process_cpu.h"
#include "pdu_process_cpu_gen.h"

namespace gr {
namespace bench {

template <class T>
pdu_process_cpu<T>::pdu_process_cpu(const typename pdu_process<T>::block_args& args)
    : INHERITED_CONSTRUCTORS(T), _max_messages(args.max_messages)
{
    _out_msg_port = this->get_message_port("out");
}

template <class T>
void pdu_process_cpu<T>::handle_msg_in(pmtf::pmt msg)
{
    size_t msg_cnt = pmtf::get_as<size_t>(*this->param_message_count);
    *this->param_message_count = ++msg_cnt;

    // Assuming that incoming message is a PDU type, i.e.
    auto meta = pmtf::map(pmtf::map(msg)["meta"]);
    auto data = pmtf::vector<T>(pmtf::map(msg)["data"]);

    pmtf::vector<T> new_data(data);
    auto pdu_out = pmtf::map{ { "meta", meta }, { "data", new_data } };

    if (_max_messages && msg_cnt >= _max_messages) {
        this->input_message_port("system")->post("done");
    }
    _out_msg_port->post(pdu_out);
}

} // namespace bench
} // namespace gr