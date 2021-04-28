import earthcooling
import matplotlib.pyplot as plt
import numpy as np


def reset_lim():
    axes = plt.gca()
    axes.set_ylim([0, 1000])


def model(eng, step_num=500, draw_each=25):
    plt.ion()
    for i in range(step_num):
        eng.forward_pass()
        eng.backward_pass()
        data = eng.getT()

        reset_lim()
        plt.plot(data)

        if i % draw_each == 0:
            plt.draw()
            plt.pause(0.1)
            plt.clf()

    plt.ioff()


if __name__ == "__main__":
    eng = earthcooling.Engine(0.01, 0.01)
    eng.init_physics(573, 10, 1.0, 1.0, 1.0)

    eng.fill_with(0.0)

    plt.plot(eng.getT())
    reset_lim()
    plt.show()

    model(eng, step_num=1000)

    plt.plot(eng.getT())
    reset_lim()
    plt.show()

    eng.enable_radiation()

    model(eng, step_num=1000)

    plt.plot(eng.getT())
    reset_lim()
    plt.show()
