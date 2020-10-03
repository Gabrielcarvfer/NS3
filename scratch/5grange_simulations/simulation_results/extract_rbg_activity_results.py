import os


def extract_rbg_activity_results(simulation_path):
    buffer_file_in = ""
    buffer_file_out = ""

    with open(simulation_path + os.sep + "schedulerInput.txt", 'r') as file:
        buffer_file_in = file.readlines()

    with open(simulation_path + os.sep + "schedulerOutput.txt", 'r') as file:
        buffer_file_out = file.readlines()

    # Discard first lines
    buffer_file_in = buffer_file_in[1:]
    buffer_file_out = buffer_file_out[1:]

    buffer_file_in = buffer_file_in[:-3]
    buffer_file_out = buffer_file_out[:-3]

    input_and_output_bitmap_per_interval = {}

    # Load bitmaps arriving at the scheduler after masked with spectrum sensing results
    for intervalBitmap in buffer_file_in:
        y = intervalBitmap.split(sep=':')

        interval = y[0]  # "+350000000.0ns"
        interval = interval.split(sep=".")  # ["+350000000", "0ns"]
        interval = interval[0]  # "+350000000"
        interval = int(interval)  # 350000000
        interval /= 1000000  # 350

        input_and_output_bitmap_per_interval[interval] = [y[1][1:-1], ""]
    del buffer_file_in

    # Load bitmaps leaving from the scheduler post scheduling
    for intervalBitmap in buffer_file_out:
        y = intervalBitmap.split(sep=':')

        interval = y[0]  # "+350000000.0ns"
        interval = interval.split(sep=".")  # ["+350000000", "0ns"]
        interval = interval[0]  # "+350000000"
        interval = int(interval)  # 350000000
        interval /= 1000000  # 350

        input_and_output_bitmap_per_interval[interval][1] = y[1][1:-1]
    del buffer_file_out

    return input_and_output_bitmap_per_interval
