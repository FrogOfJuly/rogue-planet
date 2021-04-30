# rogue-planet

### Repository for devdays of spring 2021.

How to run the simulation with our parameters
(approx 20min running time)
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
As an output, there will be some plots. For more details about plot information see our [presentation](https://docs.google.com/presentation/d/1574bsPs3SFwSELA6CzuO_OwHwaCYPg4pNq-grVEDIqo/edit?usp=sharing).


If you want to see even more details go [here](https://www.notion.so/Road-map-82734124a3694ed18324830bc8902489).
