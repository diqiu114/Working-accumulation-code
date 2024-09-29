import 'package:flutter/material.dart';
import 'package:universal_ble/universal_ble.dart';
import 'home_page.dart';
import 'package:permission_handler/permission_handler.dart';

Future<void> requestBluetoothPermissions() async {
  Map<Permission, PermissionStatus> statuses = await [
    Permission.bluetooth,
    Permission.bluetoothScan,
    Permission.bluetoothConnect,
    Permission.bluetoothAdvertise,
  ].request();

  // 检查每个权限的状态
  statuses.forEach((permission, status) {
    if (status.isGranted) {
      print('$permission granted');
    } else {
      print('$permission denied');
    }
  });
}

void get_permis() async {
  await requestBluetoothPermissions();
}

void main() async{
  WidgetsFlutterBinding.ensureInitialized(); // 确保初始化
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {

    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  var val = 0;

  @override
  Widget build(BuildContext context) {
    get_permis();
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: Text(widget.title),
      ),
      body: const HomePageSub(),
    );
  }
}
