incdir = include_directories(['../include/gnuradio/bench','../include'])

bench_deps += [gnuradio_gr_dep, volk_dep, fmt_dep, pmtf_dep, json_dep]
bench_sources += []

# # This is ugly, and there HAS to be a better way to bring in dependencies
# link_args = ['-lgnuradio-pmt','-lgnuradio-runtime']
link_args = ['-lgnuradio-runtime']
block_cpp_args = ['-DHAVE_CPU']
# if USE_CUDA
#      block_cpp_args += '-DHAVE_CUDA'

#     gnuradio_blocklib_bench_cu = library('gnuradio-blocklib-bench-cu', 
#         bench_cu_sources, 
#         include_directories : incdir, 
#         install : true, 
#         dependencies : [cuda_dep])

#     gnuradio_blocklib_bench_cu_dep = declare_dependency(include_directories : incdir,
#                         link_with : gnuradio_blocklib_bench_cu,
#                         dependencies : cuda_dep)

#     bench_deps += [cuda_dep, cusp_dep, gnuradio_blocklib_bench_cu_dep]
#     link_args += '-lcusp'
# endif

incdir = include_directories(['../include/gnuradio/bench','../include'])
gnuradio_blocklib_bench_lib = library('gnuradio-blocklib-bench', 
    bench_sources, 
    include_directories : incdir, 
    install : true,
    link_language: 'cpp',
    link_args : link_args,  # why is this necesary???
    dependencies : bench_deps,
    cpp_args : block_cpp_args)

gnuradio_blocklib_bench_dep = declare_dependency(include_directories : incdir,
					   link_with : gnuradio_blocklib_bench_lib,
                       dependencies : bench_deps)
