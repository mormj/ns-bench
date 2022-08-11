/* -*- c++ -*- */
/*
 * Copyright 2022 Josh Morman
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#pragma once

#include <gnuradio/bench/pdu_process.h>

namespace gr {
namespace bench {

template <class T>
class pdu_process_cpu : public virtual pdu_process<T>
{
public:
    pdu_process_cpu(const typename pdu_process<T>::block_args& args);
    void handle_msg_in(pmtf::pmt msg) override;

private:
    message_port_ptr _out_msg_port;
    size_t _max_messages = 0;
    size_t _msg_cnt = 0;
};

} // namespace bench
} // namespace gr