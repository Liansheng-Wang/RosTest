import serial

# 串口配置
port = '/dec/ttyUSB0'          # 串口号，根据实际情况修改
baudrate = 9600        # 波特率，根据实际情况修改

# 打开串口
ser = serial.Serial(port, baudrate)

try:
    while True:
        # 读取串口数据
        data = ser.readline().decode().strip()
        
        # 处理读取到的数据，这里简单地将其输出到控制台
        print(data)
        
except KeyboardInterrupt:
    # 如果按下Ctrl+C，退出循环并关闭串口
    ser.close()