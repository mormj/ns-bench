import os

# Check if the gnuradio package is installed or whether we're attempting to import it from
# the build directory.
path_ending = os.path.join('python', 'gnuradio', '__init__.py')
print(path_ending)
path = os.path.abspath(__file__)
if path.endswith('.pyc'):
    path = path[:-1]

print(path)

if path.endswith(path_ending):
    print("importing from the build directory")
    # We importing it from build directory.
    build_path = os.path.join(path[:-len(path_ending)])
    print(build_path)

    ###BLOCKLIB###
    __path__.append(os.path.join(build_path, 'blocklib', 'bench', 'python'))
