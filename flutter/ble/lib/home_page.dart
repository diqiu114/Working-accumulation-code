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

  void refresh() {
    setState(() {});
  }

  @override
  Widget build(BuildContext context) {
    UniversalBle.onScanResult = (result) {
      for (var val in ble_scan_result) {
        if (val.deviceId == result.deviceId) {
          return;
        }
      }
      ble_scan_result.add(result);
    };

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
            UniversalBle.startScan();
            var timer = Timer(Duration(seconds: 2), () {
              UniversalBle.stopScan();
              for (var val in ble_scan_result) {
                print(val);
              }
              print("stop");
              refresh();
            });
          },
        ),
        SizedBox(
          height: 200,
          child: ListView(
            padding: const EdgeInsets.symmetric(horizontal: 5),
            children: ble_scan_result
                .map((color) => Container(
                      alignment: Alignment.center,
                      width: 100,
                      height: 50,
                      child: Text(color.toString()),
                    ))
                .toList(),
          ),
        ),
      ],
    );
  }
}
