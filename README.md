# gnuradio Example OOT

## Dependencies

```
meson
ninja
```

## Building
```
meson setup build
cd build
ninja
ninja install
ninja test
```
Currently ninja test won't work without first installing due to the relative import from the gnuradio package.  gnuradio needs some python magic to make the disjoint relative import work
