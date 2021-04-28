import earthcooling
import matplotlib.pyplot as plt
from tqdm import tqdm
import numpy as np


def reset_lim():
    axes = plt.gca()
    axes.set_ylim([0, 1000])


def model(eng, step_num=500, draw_each=50):
    plt.ion()
    for _ in tqdm(range(int(step_num/draw_each))):
        eng.simulate_n_steps(draw_each)
        data = eng.getT()

        reset_lim()
        plt.plot(data)

        plt.draw()
        plt.pause(0.1)
        plt.clf()

    plt.ioff()


def plot_eng(eng):
    plt.plot(eng.getT())
    reset_lim()
    plt.show()


if __name__ == "__main__":
    eng = earthcooling.Engine(0.1, 0.01)
    args = {
        "mantle_temperature": 573,
        "thermal_conductivity": 3.75,
        "specific_heat_capacity": 1077.0,
        "density": 2700.0,
        "upper_mantle": -40 * pow(10, 3),
        "troposphere_height": 0  # 15*pow(10, 3)
    }
    eng.init_physics(**args)

    eng.fill_with(300.0)

    eng.forward_pass()
    eng.backward_pass()

    plot_eng(eng)

    model(eng, step_num=60000, draw_each=1000)

    print("balance?")
    plot_eng(eng)

    eng.enable_radiation(0.5)

    model(eng, step_num=10000, draw_each=500)

    plot_eng(eng)
