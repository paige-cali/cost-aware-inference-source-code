import numpy as np


def exit_point_index(cpu_load, flops, accuracies):
    """
    Choose an exit point based on current cpu load and flops characteristics of
    the model.
    Args:
        cpu_load: float in the range (0,1)
                 ex. cpu_load = 0.4 => (cpu is 40% loaded)
        flops: list of integers. The integer at index i represents flop count
                for the model if we exit at ith exit point.
                ex. flops = [167532, 245134, 432874, 481234]
        accuracies: list of floats. The float at index i represent accuracy
                of the model for ith exit point.
                ex. accuracies = [0.62, 0.75, 0.81, 0.82]
    Returns:
        an integer: index in range [0, len(flops)-1]
                    this index represents the exit point id of the models.
                    ex. if it return is 0, this means first exit point is selected
                    if it retuns len(flops)-1, this means last exit point.
    """

    #
    rk = np.floor(flops[0] + (1.0 - cpu_load) * (flops[-1] - flops[0]))
    print ("Rk value: " + str(rk))


    #find differences between rk value and each floating point operator
    differences = []
    for i in flops:
        t = np.abs(rk -i)
        differences.append(t)

    exit_point = differences.index(min(differences)) #select closest floating point value to rk
    print ("Exit point: " + str(exit_point))

    return exit_point


rk = exit_point_index(.99, [167532, 245134, 432874, 481234], [0.62, 0.75, 0.81, 0.82])


