import asyncio
from bleak import BleakScanner, BleakClient
from threading import Thread, Event
import queue
import time

class MyBle:
    def __init__(self) -> None:
        self.loop = asyncio.new_event_loop()
        self.thread = Thread(target=self.start_event_loop)
        self.thread.start()
        self.ble_dev_list_queue = queue.Queue()

    def start_event_loop(self):
        asyncio.set_event_loop(self.loop)
        self.loop.run_forever()

    def stop(self):
        self.loop.stop()
        self.thread.join()

    async def scan_ble(self, scan_time):
        devices = await BleakScanner.discover(scan_time)
        self.ble_dev_list_queue.put_nowait(devices)

    def scanner(self, scan_time=2):
        asyncio.run_coroutine_threadsafe(self.scan_ble(scan_time), self.loop)

    async def connect_ble(self, devices, device_name):
        for device in devices:
            if device.name == device_name:
                self.client = await BleakClient(device.address).connect()
                print(f"Connected to {device.name}")
                break
        

    async def write_to_device(self, uuid, data):
        if self.client:
            await self.client.write_gatt_char(uuid, data)
            print("Data written")

    def connect(self,  devices, device_name):
        asyncio.run_coroutine_threadsafe(self.connect_ble(devices, device_name), self.loop)

    def write(self, uuid, data):
        asyncio.run_coroutine_threadsafe(self.write_to_device(uuid, data), self.loop)

if __name__ == "__main__":
    # 使用示例：
    ble = MyBle()
    ble.scanner(3)  # 开始扫描蓝牙设备

    # 打印出设备列表
    devices = ble.ble_dev_list_queue.get(timeout=5)
    print(devices)
    if devices:
        ble.connect(devices, 'DC243B05')  # 连接到特定的蓝牙设备
    # ble.write('特征值的UUID', b'data')  # 向特定的蓝牙特征值写入数据
