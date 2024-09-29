import 'dart:async';
import 'dart:convert';
import 'dart:developer';
import 'dart:typed_data';

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
  BleService? service;
  BleCharacteristic? chart;
  void refresh() {
    setState(() {});
  }

  void get_ble_connected_stata(BleDevice device) async {
    device_connecting = device;
    // Get current connection state
    // Can be connected, disconnected, connecting or disconnecting
    await device.connectionState;
  }

  void connet(BleDevice dev) async {
    await UniversalBle.connect(dev.deviceId);
  }

  void dis_connet(BleDevice dev) async {
    await UniversalBle.disconnect(dev.deviceId);
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

    UniversalBle.onConnectionChange = (String deviceId, bool isConnected) {
      debugPrint('OnConnectionChange $deviceId, $isConnected');
      if (isConnected) {
        () async {
          List<BleService> services =
              await UniversalBle.discoverServices(deviceId);
          for (var service in services) {
            // debugPrint('\nble sevice:{$service}');
            for (var chart in service.characteristics) {
              if (chart.uuid == "0000ff02-0000-1000-8000-00805f9b34fb") {
                this.chart = chart;
                this.service = service;
                // print("chart ok");
              }
            }
          }
        }(); // 注意这里的调用括号
      }
    };
  }

  void write_ble(String str) async {
    var send_val = Uint8List.fromList(utf8.encode(str));
    await UniversalBle.writeValue(
        this.device_connecting!.deviceId,
        this.service!.uuid,
        this.chart!.uuid,
        send_val,
        BleOutputProperty.withResponse);
  }

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Row(
          mainAxisAlignment:
              MainAxisAlignment.center, // 也可以使用 spaceBetween 或 spaceAround
          children: [
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: RawMaterialButton(
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
            ),
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: RawMaterialButton(
                shape: const RoundedRectangleBorder(
                    borderRadius: BorderRadius.all(Radius.circular(15))),
                elevation: 0,
                highlightElevation: 0,
                fillColor: Colors.blue,
                splashColor: Colors.orange,
                textStyle: const TextStyle(color: Colors.white),
                child: const Text('断开设备'),
                onPressed: () {
                  if (device_connecting?.deviceId != null) {
                    UniversalBle.disconnect(device_connecting!.deviceId);
                    this.dis_connet(device_connecting!);
                  }
                },
              ),
            ),
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: RawMaterialButton(
                shape: const RoundedRectangleBorder(
                    borderRadius: BorderRadius.all(Radius.circular(15))),
                elevation: 0,
                highlightElevation: 0,
                fillColor: Colors.blue,
                splashColor: Colors.orange,
                textStyle: const TextStyle(color: Colors.white),
                child: const Text('写数据'),
                onPressed: () {
                  this.write_ble("sdfsdf");
                },
              ),
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
                      this.dis_connet(obj);
                      this.connet(obj);

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
