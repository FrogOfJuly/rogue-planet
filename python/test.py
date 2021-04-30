import earthcooling
import matplotlib.pyplot as plt
from tqdm import tqdm, trange
import numpy as np


def reset_lim():
    axes = plt.gca()
    axes.set_ylim([0, 1000])
    plt.xlabel("R, km")
    plt.ylabel("T, K")


def get_info(eng):
    time = eng.passed_time()
    axes = plt.gca()
    day = time // (24 * 3600)
    time = time % (24 * 3600)
    hour = time // 3600
    time %= 3600
    minutes = time // 60
    time %= 60
    seconds = time

    return {"days": day, "T_surf": eng.getT()[-1]}


def model(eng, step_num=500, draw_each=50):
    surface, time, flux = [], [], []
    plt.ion()
    draw_each = max(1, int(draw_each))
    t = trange(int(step_num / draw_each), desc='days passed', leave=True)

    for _ in t:
        temps = eng.getT()

        surface.append(temps[-1])
        time.append(eng.passed_time())
        flux.append(eng.get_radiation_flux())

        t.set_description(str(get_info(eng)) + ", flux: " + str(flux[-1]))

        plt.plot(eng.getX(), temps)
        reset_lim()

        plt.draw()
        plt.pause(0.1)
        plt.clf()

        eng.simulate_n_steps(draw_each)

    plt.ioff()
    return surface, time, flux


def plot_eng(eng):
    plt.plot(eng.getX(), eng.getT())
    reset_lim()
    # plt.show()
    plt.savefig("Termperature_in_depth.png")


if __name__ == "__main__":
    dx = 0.001
    dt = 0.01
    eng = earthcooling.Engine(dx, dt)

    Tsurf = 293.0
    depth = 5 * pow(10, 2)
    T0 = 900
    # args = {
    #     "mantle_temperature": T0,
    #     "surface_temperature": Tsuf,
    #     "thermal_conductivity": 3.75,
    #     "specific_heat_capacity": 1077.0,
    #     "density": 2700.0,
    #     "upper_mantle": -40 * pow(10, 3),
    #     "troposphere_height": 0,  # 15*pow(10, 3)
    #     "interval_to_model": 1 * pow(10, 3)
    # }
    args = {
        "mantle_temperature": T0,
        "surface_temperature": Tsurf,
        "thermal_conductivity": 3.75,
        "specific_heat_capacity": 1077.0,
        "density": 2700.0,
        "upper_mantle": -40 * pow(10, 3),
        "troposphere_height": 0.0,  # 15*pow(10, 3)
        "interval_to_model": depth
    }
    eng.init_physics(**args)
    N = eng.N()
    eng.fill_with(Tsurf)
    Tl = eng.Tl()
    print("left border tmp: ", Tl)
    # eng.set_border_cond([Tl + (Tsuf - Tl) * float(i) / float(N) for i in range(N)])
    eng.fill_with(Tsurf)
    ticks_per_day = eng.ticks_per_day()
    # eng.enable_radiation(0.001)
    # surface_tmp, time = model(eng, step_num=100000, draw_each=ticks_per_day * 10)
    surface_tmp, time, flux = [], [], []
    # plot_eng(eng)

    eng.enable_radiation(1.0)
    print(ticks_per_day)
    local_surface_tmp, local_time, local_flux = model(eng, step_num=200, draw_each=ticks_per_day)

    surface_tmp, time, flux = surface_tmp + local_surface_tmp, time + local_time, flux + local_flux

    global_suface_tmp, global_time, global_flux = model(eng, step_num=50000, draw_each=ticks_per_day * 10)
    surface_tmp, time, flux = surface_tmp + global_suface_tmp, time + global_time, flux + global_flux
    plot_eng(eng)

    time = [t / (3600.0 * 24.0) for t in time]

    plt.plot(time, surface_tmp)
    plt.ylabel("T, K")
    plt.xlabel("t, days")
    ax = plt.gca()
    height = 400
    length = 3000
    ax.vlines(7, 0, height, linestyles='dashed', colors='red', label='week')
    ax.vlines(31, 0, height, linestyles='dashed', colors='red', label='month')
    ax.vlines(365, 0, height, linestyles='dashed', colors='red', label='year')
    ax.hlines(273, 0, length, linestyles='dashed', colors='blue', label='$0^\circ C$')
    ax.hlines(195, 0, length, linestyles='dashed', colors='blue', label='195 $K^\circ$ $CO_2$')
    ax.hlines(90, 0, length, linestyles='dashed', colors='blue', label='90 $K^\circ$ $O_2$')
    ax.hlines(77, 0, length, linestyles='dashed', colors='blue', label='77 $K^\circ$ $N$')
    plt.legend()
    # plt.show()
    plt.savefig("surface_temperature_over_time.png")

    # plt.plot(time, flux)
    # plt.ylabel("Enegry flux, $J \cdot m^{-2}$")
    # plt.xlabel("t, days")
    # # plt.show()
    # plt.savefig("Energy_flux_over_time.png")
