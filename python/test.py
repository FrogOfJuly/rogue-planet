import earthcooling
import matplotlib.pyplot as plt
from tqdm import tqdm, trange


def reset_lim():
    axes = plt.gca()
    axes.set_ylim([0, 1000])


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
    surface = []
    plt.ion()
    t = trange(int(step_num / draw_each), desc='days passed', leave=True)
    for _ in t:
        eng.simulate_n_steps(draw_each)

        t.set_description(str(get_info(eng)))

        temps = eng.getT()
        surface.append(temps[-1])

        plt.plot(eng.getX(), temps)
        reset_lim()

        plt.draw()
        plt.pause(0.1)
        plt.clf()

    plt.ioff()
    return surface


def plot_eng(eng):
    plt.plot(eng.getX(), eng.getT())
    reset_lim()
    plt.show()


if __name__ == "__main__":
    dx = 0.01
    dt = pow(10, -1)
    eng = earthcooling.Engine(dx, dt)

    Tsuf = 380.0
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
        "surface_temperature": Tsuf,
        "thermal_conductivity": 3.75,
        "specific_heat_capacity": 1077.0,
        "density": 2700.0,
        "upper_mantle": -40 * pow(10, 3),
        "troposphere_height": 0.0,  # 15*pow(10, 3)
        "interval_to_model": depth
    }
    eng.init_physics(**args)
    N = eng.N()
    eng.fill_with(Tsuf)
    Tl = eng.Tl()
    print("left border tmp: ", Tl)
    eng.set_border_cond([Tl + (Tsuf - Tl) * float(i) / float(N) for i in range(N)])
    ticks_per_day = eng.ticks_per_day()
    eng.enable_radiation(0.2)
    model(eng, step_num=10000, draw_each=ticks_per_day*100)
    plot_eng(eng)
    eng.enable_radiation(1.0)
    surface_tmp = model(eng, step_num=5000, draw_each=ticks_per_day)  # ticks_per_day + 1)

    plot_eng(eng)

    plt.plot(surface_tmp)
    plt.show()
