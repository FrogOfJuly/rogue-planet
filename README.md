# rogue-planet

Repository for devdays of spring 2021.
```bash
> cd earthcooling
> mkdir deps && cd deps
> git clone https://github.com/pybind/pybind11.git
> cd ..
> mkdir build && cd build
> cmake .. && make
> mv *.so ../python/ && cd ../python
> pip install matplotlib
> python test.py
```
