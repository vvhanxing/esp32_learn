import cv2
import urllib.request
import numpy as np

# ESP32-CAM的IP地址和端口
esp32_cam_ip = '192.168.43.193'  # 你的ESP32-CAM的实际IP地址
esp32_cam_port = 81  # 默认端口是81，可能需要根据你的设置进行更改

# ESP32-CAM视频流的URL
stream_url = f'http://{esp32_cam_ip}:{esp32_cam_port}/stream'

# 使用OpenCV打开视频流
cap = cv2.VideoCapture(stream_url)

# 检查视频流是否成功打开
if not cap.isOpened():
    print("无法接收视频流。请检查ESP32-CAM端的设置和连接。")
else:
    # 循环读取并显示视频流
    index = 0
    while True:
        ret, frame = cap.read()

        if not ret:
            print("无法读取视频帧。")
            break

        # 在这里可以对图像进行处理，例如显示、保存等
        index+=1
        if index%2==0:
            filename = "pic.jpg"
        
            cv2.imwrite(filename, frame)
        #cv2.imshow('ESP32-CAM Video Stream', frame)

        # 按下 'q' 键退出循环
        # if cv2.waitKey(1) & 0xFF == ord('q'):
        #     break

    # 释放资源
    cap.release()
    cv2.destroyAllWindows()