###################################################
#    QA
###################################################

if get_option('enable_testing')
    env = environment()
    # env.prepend('LD_LIBRARY_PATH', join_paths( meson.build_root(),'schedulers','mt','lib'))
    env.prepend('PYTHONPATH', join_paths(meson.build_root(),'blocklib','bench','python'))

    # test('qa_copy', find_program('qa_copy.py'), env: env)
    # test('qa_file_sink', find_program('qa_file_sink.py'), env: env)

    # if USE_CUDA
    # subdir('cuda')
    # endif


endif
