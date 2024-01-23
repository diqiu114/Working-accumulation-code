from network import Bluetooth

bluetooth = Bluetooth()
bluetooth.start_scan(-1)    # start scanning with no timeout

while True:
    print(bluetooth.get_adv())