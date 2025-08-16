from PIL import Image
import imagehash
import os

tile_size = 16
shift_x = 0
diff_threshold = 10  

map_image = Image.open("MAP.png")
map_width, map_height = map_image.size
tiles_x = int(map_width / 16)
tiles_y = int(map_height / 16)

tile_images = {}
tile_hashes = {}

for filename in os.listdir("."):
    if filename == "MAP.png":
        continue
    if filename.endswith(".png"):
        img = Image.open(filename).convert("RGBA")
        tile_images[filename] = img
        tile_hashes[filename] = imagehash.phash(img)

with open("blocks.txt", "w") as output:
    output.write(f"{tiles_y} {tiles_x}\n")
    for i in range(tiles_y):
        line = []
        for j in range(tiles_x):
            x = j * tile_size + shift_x
            y = i * tile_size
            tile = map_image.crop((x, y, x + tile_size, y + tile_size)).convert("RGBA")
            tile_hash = imagehash.phash(tile)

            matched = "A"
            min_diff = diff_threshold

            for name, h in tile_hashes.items():
                diff = tile_hash - h
                if diff < min_diff:
                    min_diff = diff
                    matched = name

            line.append(os.path.splitext(matched)[0])
        output.write("".join(f"{elem:<20}" for elem in line) + "\n")
    remainingWidth = tiles_x
    divisor = 1
    while remainingWidth > 0:
        line = []
        for i in range(tiles_x):
            j = i // divisor
            line.append(j % 10)
        output.write("".join(f"{e:<20}" for e in line) + "\n")
        remainingWidth = remainingWidth // 10
        divisor = divisor * 10