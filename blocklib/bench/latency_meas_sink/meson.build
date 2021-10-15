yml_file = 'latency_meas_sink.yml'

bench_latency_meas_sink_files = files(['latency_meas_sink_cpu.cc'])


if cuda_dep.found() and get_option('enable_cuda')
    bench_latency_meas_sink_files += files('latency_meas_sink_cuda.cc')
    bench_cu_sources += files('latency_meas_sink_cuda.cu')
endif

gen_latency_meas_sink_h = custom_target('gen_latency_meas_sink_cpu_h',
                        input : ['latency_meas_sink.yml'],
                        output : ['latency_meas_sink.hh'],
                        command : ['python3', join_paths(share_dir,'utils/blockbuilder/scripts/process_folder.py'),
                            '--yaml_file', '@INPUT@', 
                            '--output_file', '@OUTPUT@', 
                            '--build_dir', join_paths(meson.build_root())],
                        install : true,
                        install_dir : 'include/gnuradio/bench')

gen_latency_meas_sink_cc = custom_target('gen_latency_meas_sink_cpu_cc',
                        input : ['latency_meas_sink.yml'],
                        output : ['latency_meas_sink.cc'],
                        command : ['python3', join_paths(share_dir,'utils/blockbuilder/scripts/process_folder.py'),
                            '--yaml_file', '@INPUT@', 
                            '--output_file', '@OUTPUT@', 
                            '--build_dir', join_paths(meson.build_root())],
                        install : false)        

bench_deps += declare_dependency(sources : [gen_latency_meas_sink_h])
bench_sources += [bench_latency_meas_sink_files, gen_latency_meas_sink_cc]

if get_option('enable_python')
    gen_latency_meas_sink_pybind = custom_target('gen_latency_meas_sink_cpu_pybind',
                            input : ['latency_meas_sink.yml'],
                            output : ['latency_meas_sink_pybind.cc'],
                            command : ['python3', join_paths(share_dir,'utils/blockbuilder/scripts/process_pybind.py'),
                                '--yaml_file', '@INPUT@', 
                                '--output_file', '@OUTPUT@', 
                                '--build_dir', join_paths(meson.build_root())],
                            install : false)                   
    bench_pybind_sources += gen_latency_meas_sink_pybind
    bench_pybind_names += 'latency_meas_sink'
endif
