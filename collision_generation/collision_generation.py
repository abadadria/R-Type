from png import Reader
from argparse  import ArgumentParser
from math import log2
from numpy import uint8, vstack, reshape, empty
import sys
import os
import warnings

def parse_args():
    parser = ArgumentParser()
    parser.add_argument('collision_png', help='Relative path to the collision (no bg) PNG file.')
    parser.add_argument('scenario_png', help='Relative path to the scenario (with bg) PNG file.')
    parser.add_argument('--output', '-o', default="output.txt", help='Name of the output file.')
    parser.add_argument('-wd', default=os.getcwd(), help='Sets the current working directory. '
                        'By default it is set to the path where the script is being executed from.')
    parser.add_argument('--tilesize', '-ts', type=int, default=8,
                        help='Defines the size of the collision tiles. Must be a power of 2.')
    args = parser.parse_args()
    if not os.path.exists(args.wd):
        print('Working directory is not valid')
        sys.exit(1)
    return args

def parse_tile(pixels_3d, y, x, ts):
    # 2 Inner loops iterate over the pixels of the tile
    for yy in range(y, y + ts):
        for xx in range(x, x + ts):
            if pixels_3d[yy][xx][3] != 0:
                return True
    return False
    
def parse_pixels(pixels_3d, width, height, map_size, ts):
    map = empty(shape=(map_size['y'], map_size['x']))
    map.fill(False)
    # 2 Outer loops iterate over tiles in PNG
    for y in range(0,height,ts):
        for x in range(0,width,ts):
            map[int(y/ts)][int(x/ts)] = parse_tile(pixels_3d, y, x, ts)
    return map

args = parse_args()
r = Reader(filename=os.path.normpath(os.path.join(args.wd, args.collision_png)))
width, height, pixels, info = r.asDirect()
ts = args.tilesize
map_size = {'x': int(width / ts), 'y': int(height / ts)}
print(f"PNG METADATA")
print(f"Size:\t\t {width} x {height}")
print(f"Colour:\t\t {'RGBA' if info['alpha'] else 'RGB'}")
print(f"Planes:\t\t {info['planes']}")
print(f"Bit depth:\t {info['bitdepth']*info['planes']}")
print(f"Interlace:\t {info['interlace']}\n")
print(f"COLLISION MAP INFO")
print(f"Size:\t\t {map_size['x']} x {map_size['y']}\n")

warnings.simplefilter("ignore")
pixels_2d = vstack(map(uint8, pixels))
pixels_3d = reshape(pixels_2d, (height, width, info['planes']))

map = parse_pixels(pixels_3d, width, height, map_size, ts)

with open(os.path.normpath(os.path.join(args.wd, args.output)), 'w') as f:
    f.write("TILEMAP\n")
    f.write(f"{map_size['x']} {map_size['y']}\t-- Size of map in tiles\n")
    f.write(f"{ts}\t-- Size of tiles in pixels\n")
    f.write(f"images/{os.path.basename(os.path.normpath(args.scenario_png))}\t-- Scenario file\n")
    for row in map:
        for v in row:
            f.write('1' if v else ' ')
        f.write('\n')

print(f"LEVEL CREATED IN {os.path.normpath(os.path.join(args.wd, args.output))}")