incdir = include_directories(['../include/gnuradio/bench','../include'])

bench_deps += [newsched_runtime_dep, volk_dep, fmt_dep, pmt_dep]
bench_sources += []

# This is ugly, and there HAS to be a better way to bring in dependencies
link_args = ['-lnewsched-pmt','-lnewsched-runtime']
block_cpp_args = ['-DHAVE_CPU']
if USE_CUDA
     block_cpp_args += '-DHAVE_CUDA'

    newsched_blocklib_bench_cu = library('newsched-blocklib-bench-cu', 
        bench_cu_sources, 
        include_directories : incdir, 
        install : true, 
        dependencies : [cuda_dep])

    newsched_blocklib_bench_cu_dep = declare_dependency(include_directories : incdir,
                        link_with : newsched_blocklib_bench_cu,
                        dependencies : cuda_dep)

    bench_deps += [cuda_dep, cusp_dep, newsched_blocklib_bench_cu_dep]
    link_args += '-lcusp'
endif

incdir = include_directories(['../include/gnuradio/bench','../include'])
newsched_blocklib_bench_lib = library('newsched-blocklib-bench', 
    bench_sources, 
    include_directories : incdir, 
    install : true,
    link_language: 'cpp',
    link_args : link_args,  # why is this necesary???
    dependencies : bench_deps,
    cpp_args : block_cpp_args)

newsched_blocklib_bench_dep = declare_dependency(include_directories : incdir,
					   link_with : newsched_blocklib_bench_lib,
                       dependencies : bench_deps)
