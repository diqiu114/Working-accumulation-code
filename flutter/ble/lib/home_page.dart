import 'dart:async';

import 'package:flutter/material.dart';
import 'package:universal_ble/universal_ble.dart';

class HomePageSub extends StatefulWidget {
  const HomePageSub({super.key});

  @override
  State<HomePageSub> createState() => _HomePageSubState();
}

class _HomePageSubState extends State<HomePageSub> {
  /**这里显示的声明为List<BleDevice>有助于
   * ble_scan_result.map(
   * (obj){
   * 
   * }
   * 中的obj被识别为BleDevice
   * 
   */
  // List<BleDevice> ble_scan_result = [];
  List<BleDevice> ble_scan_result = [];
  var is_scanning = false;
  BleDevice? device_connecting;
  void refresh() {
    setState(() {});
  }

  void get_ble_connected_stata(BleDevice device) async {
    device_connecting = device;
    // Get current connection state
    // Can be connected, disconnected, connecting or disconnecting
    BleConnectionState connectionState = await device.connectionState;
    print("connectionState:$connectionState");
    var chart = await UniversalBle.discoverServices(device.deviceId);
    print("chart:$chart");
  }

  @override
  void initState() {
    super.initState();
    UniversalBle.onScanResult = (result) {
      // print(ble_scan_result);
      for (var val in ble_scan_result) {
        if (val.deviceId == result.deviceId) {
          return;
        }
      }
      ble_scan_result.add(result);
      refresh();
    };

    // Get connection/disconnection updates
    UniversalBle.onConnectionChange = (String deviceId, bool isConnected) {
      debugPrint('OnConnectionChange $deviceId, $isConnected');
    };
  }

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Row(
          children: [
            RawMaterialButton(
              shape: const RoundedRectangleBorder(
                  borderRadius: BorderRadius.all(Radius.circular(15))),
              elevation: 0,
              highlightElevation: 0,
              fillColor: Colors.blue,
              splashColor: Colors.orange,
              textStyle: const TextStyle(color: Colors.white),
              child: const Text('扫描设备'),
              onPressed: () {
                if (is_scanning) {
                  return;
                }
                is_scanning = true;
                UniversalBle.startScan();
                ble_scan_result.clear();
                refresh();
                var timer = Timer(Duration(seconds: 2), () {
                  UniversalBle.stopScan();
                  // for (var val in ble_scan_result) {
                  //   print(val);
                  // }
                  print("stop");
                  // 结束扫描后不要允许马上又发起扫描
                  Timer(Duration(seconds: 1), () {
                    is_scanning = false;
                  });
                });
              },
            ),
            RawMaterialButton(
              shape: const RoundedRectangleBorder(
                  borderRadius: BorderRadius.all(Radius.circular(15))),
              elevation: 0,
              highlightElevation: 0,
              fillColor: Colors.blue,
              splashColor: Colors.orange,
              textStyle: const TextStyle(color: Colors.white),
              child: const Text('断开设备'),
              onPressed: () {
                if(device_connecting?.deviceId != null) {
                  UniversalBle.disconnect(device_connecting!.deviceId);
                }
              },
            ),
          ],
        ),
        Expanded(
          child: SizedBox(
            // height: 200,
            child: ListView(
              padding: const EdgeInsets.symmetric(horizontal: 5),
              children: ble_scan_result.map((obj) {
                return Container(
                  alignment: Alignment.center,
                  padding: EdgeInsets.symmetric(horizontal: 10.0),
                  // child: Text(obj.toString()),
                  child: RawMaterialButton(
                    padding: EdgeInsets.symmetric(horizontal: 10.0),
                    shape: const RoundedRectangleBorder(
                        borderRadius: BorderRadius.all(Radius.circular(10))),
                    elevation: 0,
                    highlightElevation: 0,
                    fillColor: Colors.blue,
                    splashColor: Colors.orange,
                    textStyle: const TextStyle(color: Colors.white),
                    child: Text('连接设备：${obj.name}'),
                    onPressed: () {
                      UniversalBle.disconnect(obj.deviceId);
                      UniversalBle.connect(obj.deviceId);
                      get_ble_connected_stata(obj);
                    },
                  ),
                );
              }).toList(),
            ),
          ),
        ),
      ],
    );
  }
}
