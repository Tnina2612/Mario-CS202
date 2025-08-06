from PIL import Image
import os

tile_size = 16
map_image = Image.open("MAP.png")
map_width, map_height = map_image.size
tiles_x = 192
tiles_y = 15

def image_diff(img1, img2):
    pixels1 = img1.convert("RGBA").getdata()
    pixels2 = img2.convert("RGBA").getdata()
    total = 0
    count = 0

    for p1, p2 in zip(pixels1, pixels2):
        if p2[3] == 0:
            continue
        total += sum((a - b) ** 2 for a, b in zip(p1[:3], p2[:3]))
        count += 1
    return total / count if count > 0 else float('inf')

tile_images = {}
for filename in os.listdir("."):
    if filename.endswith(".png"):
        tile_images[filename] = Image.open(filename)

with open("blocks.txt", "w") as output:
    output.write(f"{tiles_y} {tiles_x}\n")
    for i in range(tiles_y):
        line = []
        for j in range(tiles_x):
            x = j * tile_size + 256
            y = i * tile_size
            tile = map_image.crop((x, y, x + tile_size, y + tile_size))

            matched = "A"
            min_diff = float('inf')
            for name, img in tile_images.items():
                diff = image_diff(tile, img)
                if diff < min_diff:
                    min_diff = diff
                    matched = name
            line.append(os.path.splitext(matched)[0])
        output.write("\t".join(line) + "\n")