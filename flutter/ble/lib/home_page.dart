import 'dart:async';

import 'package:flutter/material.dart';
import 'package:universal_ble/universal_ble.dart';

class HomePageSub extends StatefulWidget {
  const HomePageSub({super.key});

  @override
  State<HomePageSub> createState() => _HomePageSubState();
}

class _HomePageSubState extends State<HomePageSub> {
  var ble_scan_result = [];
  var is_scanning = false;
  void refresh() {
    setState(() {});
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
  }

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        RawMaterialButton(
          shape: const RoundedRectangleBorder(
              borderRadius: BorderRadius.all(Radius.circular(15))),
          elevation: 0,
          highlightElevation: 0,
          fillColor: Colors.blue,
          splashColor: Colors.orange,
          textStyle: const TextStyle(color: Colors.white),
          child: const Text('Push'),
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
        Expanded(
          child: SizedBox(
            // height: 200,
            child: ListView(
              padding: const EdgeInsets.symmetric(horizontal: 5),
              children: ble_scan_result
                  .map((obj) => Container(
                        alignment: Alignment.center,
                        padding: EdgeInsets.symmetric(horizontal: 10.0),
                        // child: Text(obj.toString()),
                        child: Text("${obj.runtimeType}"),
                      ))
                  .toList(),
            ),
          ),
        ),
      ],
    );
  }
}
