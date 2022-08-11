# incdir = include_directories('../include')

if CLI11_dep.found()
srcs = ['bm_pdu_process.cc']
executable('bm_pdu_process', 
    srcs, 
    # include_directories : incdir, 
    link_language : 'cpp',
    dependencies: [gnuradio_gr_dep,
                   gnuradio_blocklib_bench_dep,
                   CLI11_dep], 
    link_args: ['-lgnuradio-runtime'], #WHYYYYYY!?!?!?!?
    install : true)

endif