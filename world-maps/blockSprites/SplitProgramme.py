from PIL import Image
import os

# Đường dẫn file gốc
input_path = "./underground items.png"
output_dir = "./underground_extracted"
os.makedirs(output_dir, exist_ok=True)

# Mở ảnh
img = Image.open(input_path).convert("RGBA")
pixels = img.load()

# Xác định màu nền (màu xanh dương nhạt ở background)
bg_color = pixels[0, 0]  # Lấy màu pixel ở góc trên bên trái

# Thay thế màu nền bằng trong suốt
for y in range(img.height):
    for x in range(img.width):
        if pixels[x, y] == bg_color:
            pixels[x, y] = (0, 0, 0, 0)

# Giả sử mỗi tile có kích thước 16x16 pixel
tile_width, tile_height = 16, 16
tile_index = 0

# Cắt các tile và lưu
for ty in range(0, img.height, tile_height + 1):
    for tx in range(0, img.width, tile_width + 1):
        tile = img.crop((tx, ty, tx + tile_width, ty + tile_height))
        # Bỏ qua tile toàn trong suốt
        if tile.getbbox():
            tile.save(os.path.join(output_dir, f"tile_{tile_index}.png"))
            tile_index += 1

output_dir
