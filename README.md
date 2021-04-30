# rogue-planet

### Repository for devdays of spring 2021.

How to run the simulation with our parameters
```bash
> git clone https://github.com/FrogOfJuly/rogue-planet.git
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
If you want to see some more details go [here](https://www.notion.so/Road-map-82734124a3694ed18324830bc8902489).
