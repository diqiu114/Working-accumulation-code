from PySide6.QtCore import Qt, QAbstractListModel, QModelIndex, Signal
from PySide6.QtWidgets import QApplication, QListView, QVBoxLayout, QWidget, QPushButton

class ListModel(QAbstractListModel):
    data_changed = Signal()  # 定义一个信号

    def __init__(self, data=None):
        super().__init__()
        self._data = data or []

    def rowCount(self, parent=QModelIndex()):
        return len(self._data)

    def data(self, index, role=Qt.DisplayRole):
        if index.isValid() and role == Qt.DisplayRole:
            return self._data[index.row()]
        return None

    def update_data(self, new_data):
        self.beginResetModel()
        self._data = new_data
        self.endResetModel()
        self.data_changed.emit()  # 发射信号

def on_data_change():
    print("Data has been updated!")

app = QApplication([])

window = QWidget()
layout = QVBoxLayout()

model = ListModel(["Item 1", "Item 2", "Item 3"])
model.data_changed.connect(on_data_change)  # 连接信号到槽函数

list_view = QListView()
list_view.setModel(model)

button = QPushButton("Update Data")
button.clicked.connect(lambda: model.update_data(["New Item 1", "New Item 2", "New Item 3"]))  # 按钮点击更新数据

layout.addWidget(list_view)
layout.addWidget(button)
window.setLayout(layout)
window.show()

app.exec()
