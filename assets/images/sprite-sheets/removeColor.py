from PIL import Image

# Đọc ảnh
input_path = "peach.png"   # đổi thành tên ảnh của bạn
output_path = "peach.png"

# Mở ảnh và chuyển sang RGBA để có kênh alpha
img = Image.open(input_path).convert("RGBA")
pixels = img.load()

# Lấy màu nền từ pixel (0,0)
bg_color = pixels[0, 0]

# Duyệt toàn bộ ảnh và thay các pixel có màu giống bg_color thành trong suốt
width, height = img.size
for y in range(height):
    for x in range(width):
        if pixels[x, y] == bg_color:
            pixels[x, y] = (0, 0, 0, 0)  # pixel trong suốt

# Lưu ảnh kết quả
img.save(output_path, "PNG")
print(f"Ảnh đã được xử lý và lưu tại {output_path}")
