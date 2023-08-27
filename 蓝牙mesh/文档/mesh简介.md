# 蓝牙 Mesh 简介

 [xmamiga](http://www.xmamiga.com/author/zengzy/) [2019年7月25日](http://www.xmamiga.com/3433/)

> 随着 阿里 对蓝牙 Mesh 的布局， 蓝牙 Mesh 又火了一把；蓝牙 Mesh不是无线通信技术，而是一种网络技术。蓝牙 Mesh 网络使用并取决于蓝牙 BLE，蓝牙LE是蓝牙Mesh使用的无线通信协议栈。




![img](http://www.xmamiga.com/wp-content/uploads/2019/07/Mesh-Device-Networks_800x800-660x660.jpg)



从本质上来讲，蓝牙Mesh技术并非无线通信技术，而是一种网络（组网）的技术，用于构建“多对多通信连接”的网络。如今，蓝牙适用的范围已经逐渐拓展到所有物联网边缘场景：“蓝牙增强速率技术（BR / EDR）”的应用从无线耳机发展到鼠标键盘；“蓝牙低功耗技术”应用于手表、手环，发掘了可穿戴市场；而“蓝牙 Mesh 组网技术”则瞄准了整个（边缘域）物联网市场，包括消费领域和工业领域。

### 一、蓝牙 Mesh 基本概念

#### 1.1 设备(Devices)和节点(Nodes)

如果一个设备成为了蓝牙 Mesh 网络的一部分, 我们就把它叫做节点(node)，反之, 我们就把它叫做"未配网的设备"(unprovisioned devices)。

#### 1.2 元素(Element)

在设备中可以寻址访问的实体(即设备的子节点)。

#### 1.3 消息(Messages)

当一个节点需要查询别的节点的状态(Status)或者控制别的节点的时候, 就需要发一个对应类型的消息。当一个节点向别人报告状态改变的时候, 他也需要发出一个消息，在蓝牙Mesh 里面定义了很多种类型的消息，每种消息都有对应的操作码(opcode)，消息可以按照有应答(acknowledged)和没应答(unacknowledged)来分类。

#### 1.4 地址(Addresses)

在蓝牙 Mesh 里面定义了三种类型的地址: * 单播地址(unicast address): 这个地址是在配网的时候分配给设备的. 一个 Mesh 网络可以有 32767 个单播地址. * 组播地址(group address): 一共可以有 16384 个组播地址. * SIG 保留地址(256个): SIG 定义了 4 个组播地址, 分别是"All-proxies", "All-friends", "All-relays" and "All-nodes". * 动态分配地址(16128): 动态分配的组播地址是设计成在用户配置的时候, 可以分配代表一些实际的场所, 比如可以定义几个组播地址代表几个不同的房间. * 虚拟地址(virtual address)。

#### 1.5 发布和订阅(Publish & Subscribe)

- 节点发布消息到单播地址, 组播地址或者虚拟地址
- 一个设备可以订阅多个消息
- 多个节点可以订阅同一个消息

#### 1.6 状态和属性(States & Properties)

- 状态: 元素的不同情况叫做状态(States), 状态是一个特定类型的值, 在每个元素内部存在，除了本身的值以外, 状态还有一些相关的行为(如Generic OnOff)
- 状态绑定(Bound States): 一个状态的变化会造成另外状态的触发, 这种关系叫做状态绑定

#### 1.7 消息(Messages)

类型:

- GET: 获取状态
- SET: 设置状态 //STATUS: 可以作为GET/SET的应答; 也可以独立出现

蓝牙 Mesh 里面定义了很多种消息, 通过 Opcode 来区分, 还包含了相关联的参数和行为，Opcode 可以是单字节, 双字节(常见)或者三字节(厂商指定)
所以绝大部分的 Mesh 消息都是对状态进行操作的, 只有特别的和属性相关的消息, 才会对属性进行操作, 而且需要制定 16 位的属性 ID

#### 1.8 模型/模式(Models)

定义了一个节点的基本功能
一个节点当然可以包含多个Model

蓝牙Mesh采用的C-S架构：

- Server model: 定义了状态states, 状态转换 state transitions, 状态绑定state bindings 和包含了哪些消息, 当然也同样定义了与这些消息, 状态, 状态转换相关的行为Behaviors
- Client model: 没有定义任何的状态States, 但是它定义了要收发那些消息
- Control model: Server + Client

#### 1.9 配网(Provisioning)

配网的全过程包括大概 5 个步骤, 分别是：
\- Beaconing: 告诉你我要配网, 这里使用的是新定义的 AD 广播包类型, Mesh AD
\- Invitation: 配网者 Provisioner 听到了这个 Beacon 以后, 就发一个邀请, 用的就是配网邀请 PDU(Protocol Data Unit)
\- Exchanging Public Keys: 交换公钥
\- Authentication: 一个互动随机数的认证流程, 这点和原来蓝牙输入 0000 的密码很像, 但是会简单一点点
\- Distribution of the Provisioning Data: 认证完成, 从公钥和两个设备的私钥派生出 Session Key，后面的配网的信息交互的过程会用这个 Session key 来加密， 配网成功以后, 就会根据最后一步里面包含交换的 NetKey 来加密后面的数据交换

#### 1.10 节点特性(Features)

- 中继(Relay): 可以转发收到的消息. 因为有了 Relay, Mesh 网络就可以实现多跳(Hops)
- 低功耗(Low Power): 经常需要睡眠而不能接收消息的节点
- 朋友(Friend): 当 Low-Power 节点在睡眠的时候, 帮其接收消息的节点
- 代理(Proxy): 这就是 Mesh 想到的兼容现有的非 Mesh 设备的方法. 在 Proxy 节点, 其实是可以通过 BLE 的 GATT 来交流的

### 二、拓扑的故事

蓝牙Mesh也叫蓝牙网状网，是多点对多点网络拓扑结构的物联网。蓝牙 Mesh 主要针对简单的控制和监视应用，比如光控或传感器数据采集，针对小数据的控制包传输，发出单一的命令或报告。

蓝牙 BR/EDR 让一台设备连接到另一台设备并与另一台设备进行通信，建立 1：1 关系，反映在大多数人熟悉的术语“配对”中。一些设备可以与其他设备具有多个 1：1关 系，并且可以形成称为“ 微微网（piconet）” 的一种中枢/辐射拓扑（hub/spoke topology） 。

蓝牙 BLE 设备也可以与其他设备形成 1：1 和中枢/辐射（hub/spoke）关系，并以无连接方式工作，广播任何其他直接射频范围内的设备都可以接收的数据。这是一个 1 ：m的 拓扑，其中 m 可以是一个非常大的数字！如果收听广播的设备本身不进行数据传输，则广播设备自己具有射频频谱，并且对可以接收和利用其广播的其他设备的数量没有实际的限制（蓝牙信标就是这种能力的一个例子）。

蓝牙 Mesh 允许我们在无线设备之间建立多对多（m：m ）的关系。此外，设备可以将数据中继到不在发端设备的直接射频范围内的其他设备。这样，Mesh 网络可以跨越很大的物理区域并包含大量的设备。

### 三、网络结构




![img](http://www.xmamiga.com/wp-content/uploads/2019/07/mesh_stack.png)



承载层（bearer layer）：承载层（bearer layer）定义了如何使用底层 BLE栈 传送 PDU。目前，定义了两个承担者，即广告承载者和 GATT 承载者。

网络层（network layer）：网络层定义各种消息地址类型和网络消息格式。中继和代理 行为由网络层实现。

下层传输层（lower transport layer）：如果需要，下层传输层处理 PDU 的分段和重组。

上层传输层（upper transport layer）：负责传入和传出接入层的应用数据的加密，解密和认证。它还负责称为传输控制消息的特殊消息。这些包括与“友谊（friendship）” 关系有关的心跳和消息。

接入层（access layer）：负责应用数据的格式，定义和控制在上层传输层中执行的加密和解密过程，并验证从它接收到的数据适用于正确的网络和应用，然后再将数据转发到堆栈。

基础模型（foundation models）：基础模型层负责实施与 Mesh 网络的配置和管理相关的模型。

模型（models）：模型层关注模型的实现，因此实现行为，消息，状态等。

------

- [SIG Mesh](https://www.bluetooth.com/bluetooth-technology/topology-options/)