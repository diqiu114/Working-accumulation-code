import 'package:flutter/material.dart';
class CustomListView extends StatelessWidget {
  CustomListView({Key? key}) : super(key: key);

  final List<Color> data = [
    Colors.purple[50]!,
    Colors.purple[100]!,
    Colors.purple[200]!,
    Colors.purple[300]!,
    Colors.purple[400]!,
    Colors.purple[500]!,
    Colors.purple[600]!,
    Colors.purple[700]!,
    Colors.purple[800]!,
    Colors.purple[900]!,
  ];

  TextStyle get textStyle => const TextStyle(
        color: Colors.white,
        shadows: [
          Shadow(color: Colors.black, offset: Offset(.5, .5), blurRadius: 2)
        ],
      );

  @override
  Widget build(BuildContext context) {
    return SizedBox(
      height: 200,
      child: ListView(
        padding: const EdgeInsets.symmetric(horizontal: 5),
        children: data
            .map((color) => Container(
                  alignment: Alignment.center,
                  width: 100,
                  height: 50,
                  color: color,
                  child: Text(
                    colorString(color),
                    style: textStyle,
                  ),
                ))
            .toList(),
      ),
    );
  }

  String colorString(Color color) =>
      "#${color.value.toRadixString(16).padLeft(8, '0').toUpperCase()}";
}