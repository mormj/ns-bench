#!/usr/bin/env python3
#
# Copyright 2021 Josh Morman
#
# SPDX-License-Identifier: GPL-3.0-or-later
#
#

from newsched import gr, blocks
from newsched import bench



tb = gr.flowgraph()

nsamples = 10000
samp_rate = 32000
interval = 0.1

src = blocks.null_source(gr.sizeof_gr_complex)
hd = blocks.head(gr.sizeof_gr_complex, nsamples)
inj = bench.time_tag_injector(gr.sizeof_gr_complex, interval, samp_rate)
# cp1 = blocks.copy(gr.sizeof_gr_complex)
snk = bench.latency_meas_sink(gr.sizeof_gr_complex, samp_rate)

tb.connect([src, hd, inj, snk])

tb.start()
tb.wait()

print(f'latency = {snk.avg_latency()}')