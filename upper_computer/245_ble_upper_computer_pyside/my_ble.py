from abc import abstractmethod
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
        self.__be_scanning = False
        self.devices = None
        self.client = None
    @abstractmethod
    def scan_ble_end(self):
        pass
    
    @abstractmethod
    def connect_state(self, state = False):
        pass

    @abstractmethod
    def notify_update(self, sender, data):
        pass

    def start_event_loop(self):
        asyncio.set_event_loop(self.loop)
        self.loop.run_forever()

    def stop(self):
        self.loop.stop()
        self.thread.join()

    async def scan_device(self, scan_time):
        # 还在扫描，如果有操作断开了当前client的连接，又想接着扫描到这个蓝牙
        # 需要等下位机蓝牙反应下
        if self.client:
            if self.client.is_connected():
                await asyncio.sleep(1)
        self.devices = await BleakScanner.discover(scan_time)
        devs_name_list = []
        for device in self.devices:
            if device.name == None:
                devs_name_list.append(device.address)
            else:
                devs_name_list.append(device.name)
            
        self.ble_dev_list_queue.put(devs_name_list)
        self.scan_ble_end()
        self.__be_scanning = False

    async def connect_device(self, device_name = ""):
        for device in self.devices:
            if device.name == device_name or device.address == device_name:
                print(f"Connecting to {device_name}")

                self.client = BleakClient(device.address, winrt=dict(use_cached_services=True))
                if self.client == None:
                    print("Connect false")
                    return
                await self.client.connect()
                if self.client.is_connected():
                    print(f"Connected to {device.name}")
                    self.connect_state(True)
                    # 获取服务列表
                    services = await self.client.get_services()
                    for service in services:
                        print(f"Service: {service.uuid}")
                        # 获取特征列表
                        for char in service.characteristics:
                            print(f"  Characteristic: {char.uuid}, Handle: {char.handle}")
                else:
                    print("Connect false")
                break
    async def dis_connet_device(self):
        if self.client == None:
            return
        await self.client.disconnect()

    async def write_to_device(self, uuid, data):
        if self.client.is_connected():
            await self.client.write_gatt_char(uuid, data)
            print("Data written")

    async def notify_device(self, uuid):
        # 设置通知回调
        await self.client.start_notify(uuid, self.notify_update)
        print("Notifications started. Listening for data...")

    def scan_ble(self, scan_time=2):
        # 正在发现蓝牙就不要再扫描了
        if self.__be_scanning:
            print("Be discovering")
            return
        asyncio.run_coroutine_threadsafe(self.scan_device(scan_time), self.loop)
        self.__be_scanning = True

    def disconnet_ble(self):
        asyncio.run_coroutine_threadsafe(self.dis_connet_device(), self.loop)

    def connect_ble(self, name = ""):
        asyncio.run_coroutine_threadsafe(self.connect_device(name), self.loop)

    def write_ble(self, uuid, data):
        asyncio.run_coroutine_threadsafe(self.write_to_device(uuid, data), self.loop)

    def notify_ble(self, uuid):
        asyncio.run_coroutine_threadsafe(self.notify_device(uuid), self.loop)

if __name__ == "__main__":
    # 使用示例：
    ble = MyBle()
    ble.scanner(3)  # 开始扫描蓝牙设备

    # # 打印出设备列表
    # devices = ble.ble_dev_list_queue.get(timeout=5)
    # logging.info(devices)
    # if devices:
    #     ble.connect(devices, 'DC243B05')  # 连接到特定的蓝牙设备
    # ble.write('特征值的UUID', b'data')  # 向特定的蓝牙特征值写入数据
