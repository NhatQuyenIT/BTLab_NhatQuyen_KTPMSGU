import os

# Lấy thư mục chứa file input.py
cwd = os.path.dirname(os.path.abspath(__file__))
filename = os.path.join(cwd, "all_input.inp")

n = int(input("Nhập số lượng test: "))

with open(filename, "w", encoding="utf-8") as f:
    for i in range(n):
        val = input(f"Nhập số thứ {i+1}: ")
        f.write(val.strip() + "\n")

print(f"✅ Đã lưu {n} dòng vào {filename}")
