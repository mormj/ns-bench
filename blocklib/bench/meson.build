subdir('include/gnuradio/bench')

bench_sources = []
bench_cu_sources = []
bench_pybind_sources = []
bench_pybind_names = []
bench_deps = []

# Individual block subdirectories
#  Copy block as an example
subdir('time_tag_injector')
subdir('latency_meas_sink')

subdir('lib')
if (get_option('enable_python'))
    subdir('python/newsched/bench')
endif

# subdir('test')
