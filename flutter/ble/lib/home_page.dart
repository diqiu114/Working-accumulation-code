// ignore_for_file: slash_for_doc_comments, non_constant_identifier_names, unnecessary_this, unused_local_variable, use_function_type_syntax_for_parameters

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
  BleDevice? conneted_ble_dev;

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
      for (var dev in ble_scan_result) {
        if (dev.deviceId == deviceId) {
          conneted_ble_dev = dev;
        }
      }
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
      } else {
        conneted_ble_dev = null;
      }
      setState(() {});
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

  void scan_ble() {
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
  }

  Padding sample_btn({void on_pressed_cb()?, String? name}) {
    return Padding(
      padding: const EdgeInsets.all(8.0),
      child: RawMaterialButton(
        shape: const RoundedRectangleBorder(
            borderRadius: BorderRadius.all(Radius.circular(15))),
        elevation: 0,
        highlightElevation: 0,
        fillColor: Colors.blue,
        splashColor: Colors.orange,
        textStyle: const TextStyle(color: Colors.white),
        child: Padding(
          padding: const EdgeInsets.all(8.0),
          child: Text(name ?? ""),
        ),
        onPressed: () {
          on_pressed_cb?.call();
        },
      ),
    );
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
              child: sample_btn(
                name: "扫描设备",
                on_pressed_cb: scan_ble,
              ),
            ),
            Padding(
                padding: const EdgeInsets.all(8.0),
                child: sample_btn(
                    name: "断开设备",
                    on_pressed_cb: () {
                      if (device_connecting?.deviceId != null) {
                        UniversalBle.disconnect(device_connecting!.deviceId);
                        this.dis_connet(device_connecting!);
                      }
                    })),
            sample_btn(
              name: "发送数据",
              on_pressed_cb: () {if(conneted_ble_dev != null )this.write_ble("sdfsdf");},
            ),
          ],
        ),
        Text(
            "当前连接设备：${(conneted_ble_dev == null ? "无" : conneted_ble_dev?.name)}"),
        // 扫描完成后会创建一个btn列表
        widget_devices_list(),
      ],
    );
  }

  void connect_ble(BleDevice dev) {
    this.dis_connet(dev);
    this.connet(dev);
    get_ble_connected_stata(dev);
  }

  Expanded widget_devices_list() {
    return Expanded(
      child: SizedBox(
        // height: 200,
        child: ListView(
          padding: const EdgeInsets.symmetric(horizontal: 5),
          children: ble_scan_result.map((obj) {
            return Container(
                alignment: Alignment.center,
                padding: EdgeInsets.symmetric(horizontal: 8.0),
                // child: Text(obj.toString()),
                child: Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    sample_btn(
                      name: '连接该设备：${obj.name}',
                      on_pressed_cb: () {
                        this.dis_connet(obj);
                        this.connet(obj);
                        get_ble_connected_stata(obj);
                      },
                    ),
                  ],
                ));
          }).toList(),
        ),
      ),
    );
  }
}
