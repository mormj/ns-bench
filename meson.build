# SPDX-FileCopyrightText: 2020 Josh Morman 
#

project('gnuradio-bench', 'cpp', 
  version : '0.0.0',
  license : 'GPLv3',
  default_options : ['cpp_std=c++17'])

cc = meson.get_compiler('cpp')
rt_dep = cc.find_library('rt', required : false)
libdl_dep = cc.find_library('dl')

c_available = add_languages('c', required : true)
cuda_available = add_languages('cuda', required : false)

boost_dep = dependency('boost', modules : ['program_options','thread'], version : '>=1.65')
volk_dep = dependency('volk', version : '>=2.2')
yaml_dep = dependency('yaml-cpp', version : '>=0.6')
fmt_dep = dependency('fmt', method: 'cmake', modules: ['fmt::fmt'])
spdlog_dep = dependency('spdlog', method: 'cmake', modules : ['spdlog::spdlog'])
python3_dep = dependency('python3', required : get_option('enable_python'))

# Import python3 meson module which is used to find the Python dependencies.
py3_inst = import('python').find_installation('python3')

pybind11_dep = dependency('pybind11', required : get_option('enable_python'))
threads_dep = dependency('threads')
gtest_dep = dependency('gtest', main : true, version : '>=1.10', required : get_option('enable_testing'))
USE_CUDA = cuda_available and get_option('enable_cuda')
cuda_dep = dependency('cuda', version : '>=10.1', required : USE_CUDA , modules : ['cufft'])
cusp_dep = dependency('cusp', required : USE_CUDA)

prefix = get_option('prefix')
# Escape spaces
prefix_parts = prefix.split(' ')
prefix = '\ '.join(prefix_parts)
share_dir = join_paths(prefix,'share')

# gnuradio_dep = dependency('gnuradio', method: 'cmake')
# TODO - do this with subcomponents
pmt_dep = dependency('pmtf')
gnuradio_runtime_dep = dependency('gnuradio-runtime')

prefix = get_option('prefix')
# Escape spaces
prefix_parts = prefix.split(' ')
prefix = '\ '.join(prefix_parts)
share_dir = join_paths(prefix,'share')

USE_CUDA = cuda_available and get_option('enable_cuda')
IMPLEMENT_CUDA = USE_CUDA
IMPLEMENT_CPU = true
SCRIPTS_DIR=join_paths(share_dir,'utils','blockbuilder','scripts')

subdir('blocklib')

subdir('python/gnuradio')