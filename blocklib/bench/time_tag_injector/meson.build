yml_file = 'time_tag_injector.yml'

bench_time_tag_injector_files = files(['time_tag_injector_cpu.cc'])


if cuda_dep.found() and get_option('enable_cuda')
    bench_time_tag_injector_files += files('time_tag_injector_cuda.cc')
    bench_cu_sources += files('time_tag_injector_cuda.cu')
endif

gen_time_tag_injector_h = custom_target('gen_time_tag_injector_cpu_h',
                        input : ['time_tag_injector.yml'],
                        output : ['time_tag_injector.hh'],
                        command : ['python3', join_paths(share_dir,'utils/blockbuilder/scripts/process_folder.py'),
                            '--yaml_file', '@INPUT@', 
                            '--output_file', '@OUTPUT@', 
                            '--build_dir', join_paths(meson.build_root())],
                        install : true,
                        install_dir : 'include/gnuradio/bench')

gen_time_tag_injector_cc = custom_target('gen_time_tag_injector_cpu_cc',
                        input : ['time_tag_injector.yml'],
                        output : ['time_tag_injector.cc'],
                        command : ['python3', join_paths(share_dir,'utils/blockbuilder/scripts/process_folder.py'),
                            '--yaml_file', '@INPUT@', 
                            '--output_file', '@OUTPUT@', 
                            '--build_dir', join_paths(meson.build_root())],
                        install : false)        

bench_deps += declare_dependency(sources : [gen_time_tag_injector_h])
bench_sources += [bench_time_tag_injector_files, gen_time_tag_injector_cc]

if get_option('enable_python')
    gen_time_tag_injector_pybind = custom_target('gen_time_tag_injector_cpu_pybind',
                            input : ['time_tag_injector.yml'],
                            output : ['time_tag_injector_pybind.cc'],
                            command : ['python3', join_paths(share_dir,'utils/blockbuilder/scripts/process_pybind.py'),
                                '--yaml_file', '@INPUT@', 
                                '--output_file', '@OUTPUT@', 
                                '--build_dir', join_paths(meson.build_root())],
                            install : false)                   
    bench_pybind_sources += gen_time_tag_injector_pybind
    bench_pybind_names += 'time_tag_injector'
endif
