import requests
from PIL import Image
from io import BytesIO

# ESP32-CAM的IP地址和端口
esp32_cam_ip = '192.168.43.193'
esp32_cam_port = '81'

# 获取ESP32-CAM的视频流
def get_video_stream():
    url = f'http://{esp32_cam_ip}:{esp32_cam_port}/stream'
    response = requests.get(url, stream=True)
    return response

# 显示图像
def show_image(image_data):
    image = Image.open(BytesIO(image_data))
    image.show()

# 主程序
def main():
    try:
        while True:
            # 获取视频流数据
            response = get_video_stream()

            # 检查响应状态
            if response.status_code == 200:
                # 获取图像数据
                image_data = response.content

                # 显示图像
                show_image(image_data)

    except KeyboardInterrupt:
        print("程序已终止")

if __name__ == "__main__":
    main()