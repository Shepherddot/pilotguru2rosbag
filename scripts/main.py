import json
import os
import numpy as np
import math
import time
import shutil

candi_parse_file = ['rotations.json', 'accelerations.json', 'frames.json']


def process_rotation_data(path):
    with open(path, 'r') as f:
        data = json.load(f)['rotations']

    rot_time_list = []
    rot_data_list = []

    for item in data:
        x_rot = item['x']
        y_rot = item['y']
        z_rot = item['z']
        timestamp = item['time_usec']

        rot_time_list.append(timestamp)
        rot_data_list.append([x_rot, y_rot, z_rot])

    return rot_time_list, rot_data_list


def process_acceleration_data(path):
    with open(path, 'r') as f:
        data = json.load(f)['accelerations']

    acc_time_list = []
    acc_data_list = []

    for item in data:
        x_acc = item['x']
        y_acc = item['y']
        z_acc = item['z']
        timestamp = item['time_usec']

        acc_time_list.append(timestamp)
        acc_data_list.append([x_acc, y_acc, z_acc])

    return acc_time_list, acc_data_list


def process_frame_data(path, save_path):
    with open(path, 'r') as f:
        data = json.load(f)['frames']

    image_frames = []
    for item in data:
        frame_id = str(item['frame_id']).zfill(6)
        timestamp = str(item['time_usec'])

        item_stream = frame_id + ' ' + timestamp
        image_frames.append(item_stream)

        with open(save_path, 'a') as f:
            f.write(item_stream)
            f.write('\n')


def main():
    base_path = '/home/liu/test_dataset/2022_03_12-10_52_59'
    save_imu_path = base_path + '/pre/imu.txt'
    save_image_path = base_path + '/pre/image.txt'
    save_video_path = base_path + '/pre/video.mp4'

    if os.path.isfile(save_imu_path):
        os.remove(save_imu_path)

    if os.path.isfile(save_image_path):
        os.remove(save_image_path)

    rotation_path = os.path.join(base_path, candi_parse_file[0])
    rot_time, rot_data = process_rotation_data(rotation_path)

    acceleration_path = os.path.join(base_path, candi_parse_file[1])
    acc_time, acc_data = process_acceleration_data(acceleration_path)

    acc_time_array = np.array(acc_time)
    for idx, a_time in enumerate(rot_time):
        closest_time = np.fabs(a_time - acc_time_array).min() * 1e-3
        min_args = np.fabs(a_time - acc_time_array).argmin()

        if min_args - 1 < 0:
            continue

        target_time_1 = acc_time_array[min_args]
        target_time_2 = acc_time_array[min_args - 1]

        print(closest_time)
        print(str(a_time) + ' ' + str(target_time_1) + ' ' + str(target_time_2))

        acc_1 = np.array(acc_data[min_args])
        acc_2 = np.array(acc_data[min_args - 1])

        lamda_factor = (a_time - target_time_2) / (target_time_1 - target_time_2)
        acc_inter = (1 - lamda_factor) * acc_2 + lamda_factor * acc_1

        real_data_item = []
        real_data_item.append(a_time)
        real_data_item.extend(rot_data[idx])
        real_data_item.extend(acc_inter.tolist())

        time_str = str(a_time) + '\t'
        data_string_line = time_str + '\t'.join(format(e, ".16f") for e in real_data_item[1:])
        with open(save_imu_path, 'a') as f:
            f.write(data_string_line)
            f.write('\n')

    image_frame_path = os.path.join(base_path, candi_parse_file[2])
    process_frame_data(image_frame_path, save_image_path)

    video_exist_path = os.path.join(base_path, 'video.mp4')
    if os.path.isfile(video_exist_path):
        shutil.move(video_exist_path, save_video_path)


if __name__ == '__main__':
    main()
