#!/usr/bin/env python3
#
# Copyright 2021 Josh Morman
#
# SPDX-License-Identifier: GPL-3.0-or-later
#
#

from newsched import gr, blocks
from newsched import bench
from newsched.schedulers import nbt
import time

tb = gr.flowgraph()

nsamples = 100000
samp_rate = 32000
interval = 0.1
ncopy = 20

managed_latency_in_seconds = .00005
max_fill = int(samp_rate * managed_latency_in_seconds )
print(f'max_fill={max_fill}')

src = blocks.null_source(gr.sizeof_gr_complex)
hd = blocks.head(gr.sizeof_gr_complex, nsamples)
inj = bench.time_tag_injector(gr.sizeof_gr_complex, interval, samp_rate)
# cp1 = blocks.copy(gr.sizeof_gr_complex)
snk = bench.latency_meas_sink(gr.sizeof_gr_complex, samp_rate)

edges = tb.connect([src, hd, inj])

grp = [src,hd,inj]
ops = []
last_block = inj
for ii in range(ncopy):
    ops.append(blocks.copy(gr.sizeof_gr_complex))
    edges.append(tb.connect(last_block, ops[ii]))
    last_block = ops[ii]
    grp.append(ops[ii])

edges.append(tb.connect(ops[ncopy - 1], snk))
grp.append(snk)

for e in edges:
    e.set_custom_buffer(gr.buffer_cpu_vmcirc_properties.make(gr.buffer_cpu_vmcirc_type.AUTO).set_max_buffer_fill(max_fill))

sched = nbt.scheduler_nbt("nbtsched")
tb.add_scheduler(sched)

sched.add_block_group(grp)
tb.validate()

startt = time.time()
tb.start()
tb.wait()
endt = time.time()

print(f"Took {endt-startt} seconds")
print(f"Avg. Latency = {snk.avg_latency()} us")
