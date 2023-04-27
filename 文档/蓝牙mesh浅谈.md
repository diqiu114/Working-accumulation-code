本文主要根据蓝牙兴趣联盟（SIG）以及其官方微信公众号关于蓝牙 Mesh 组网的相关博文进行梳理，旨在对蓝牙 Mesh 组网技术有一个初步的认识。

## 前言

蓝牙 Mesh 脱胎于 CSR 倡导的私有协议- CSR Mesh，该技术诞生于 2014 年。

蓝牙技术联盟（SIG）于去年 7 月 19 日正式宣布，蓝牙技术开始全面支持 Mesh 网状网络。**蓝牙 Mesh 组网是一种组网技术**，蓝牙 4.0 以上支持低功耗蓝牙的芯片都支持。全新的 Mesh 功能提供设备间多对多传输，并特别提高构建大范围网络覆盖的通信能力，适用于楼宇自动化、无线传感器网络等需要让数以万计个设备在可靠、安全的环境下传输的物联网解决方案。如今，蓝牙适用的范围已经逐渐拓展到所有物联网边缘场景：“蓝牙增强速率技术（BR / EDR）” 的应用从无线耳机发展到鼠标键盘；“蓝牙低功耗技术” 应用于手表、手环，发掘了可穿戴市场；而“蓝牙 Mesh 组网技术”则瞄准了整个（边缘域）物联网市场，包括消费领域和工业领域[[1\]](https://www.erenship.com/posts/63c7.html#fn:1)。

<iframe width="560" height="315" src="https://player.vimeo.com/video/225874947" frameborder="0" allowfullscreen="" style="box-sizing: border-box; color: rgb(0, 0, 0); font-family: &quot;Noto Serif SC&quot;; font-size: 17px; font-style: normal; font-variant-ligatures: normal; font-variant-caps: normal; font-weight: 400; letter-spacing: normal; orphans: 2; text-align: left; text-indent: 0px; text-transform: none; white-space: normal; widows: 2; word-spacing: 0px; -webkit-text-stroke-width: 0px; background-color: rgb(255, 255, 255); text-decoration-thickness: initial; text-decoration-style: initial; text-decoration-color: initial;"></iframe>



## 低功耗蓝牙（BLE）

要讨论蓝牙 Mesh 组网技术就必须先说明低功耗蓝牙（Bluetooth Low Energy, BLE），因为蓝牙 Mesh 网络使用、并且依赖于低功耗蓝牙。**低功耗蓝牙技术是蓝牙 Mesh 使用的无线通信协议栈[[2\]](https://www.erenship.com/posts/63c7.html#fn:2)。**

首先蓝牙是一种短距离通信的无线电技术。其特点为：

- 分散式网络结构；
- 点对点或多点通信；
- 快跳频和短包技术；
- 工作在2.4GHz ISM 频段（Industrial Scientific Medical Band）；
- 时分全双工传输。

低功耗蓝牙泛指蓝牙 4.0 或更高的模块，蓝牙低功耗技术是一种低成本、短距离、可互操作的无线技术通信技术，工作在免许可的2.4GHz ISM 射频频段。相比于传统蓝牙（Classic Bluetooth，BT），低功耗蓝牙拥有更低的功耗，更远的传输距离，以及可以实现 AOA 室内定位。现如今的电子设备基本都配备 BLE 4.0 以上的蓝牙模块。例如我们的无线耳机，智能手环以及各种红黄蓝绿的单车等设备都使用到了低功耗蓝牙模块进行通信。

**BLE 低功耗蓝牙和传统蓝牙有以下5大区别[[5\]](https://www.erenship.com/posts/63c7.html#fn:5)：**

1. 低功耗蓝牙的发送和接受任务会以最快的速度完成，完成之后蓝牙 BLE 会暂停发射无线（但是还是会接受），等待下一次连接再激活；传统蓝牙是持续保持连接；
2. 低功耗蓝牙的广播信道（为保证网络不互相干扰而划分）仅有 3 个；传统蓝牙是 32 个；
3. 低功耗蓝牙“完成”一次连接(即扫描其它设备、建立链路、发送数据、认证和适当地结束)只需 3ms；传统蓝牙完成相同的连接周期需要数百毫秒；
4. 低功耗蓝牙使用非常短的数据包，多应用于实时性要求比较高，但是数据速率比较低的产品，遥控类的如键盘，遥控鼠标，传感设备的数据发送，如心跳带，血压计，温度传感器等；传统蓝牙使用的数据包长度较长，可用于数据量比较大的传输，如语音，音乐，较高数据量传输等；
5. 低功耗蓝牙无功率级别，一般发送功率在 +4dBm，一般在空旷距离，达到 70m 的传输距离；传统蓝牙有3个功率级别，Class1，Class2，Class3，分别支持 100m，10m，1m 的传输距离。

蓝牙低能耗架构共有两种芯片构成：单模芯片和双模芯片。蓝牙单模芯片可以和其它单模芯片及双模芯片通信，此时后者需要使用自身架构中的蓝牙低能耗技术部分进行收发数据。双模芯片也能与标准蓝牙技术及使用传统蓝牙架构的其它双模芯片通信。

## 蓝牙 Mesh 组网

蓝牙 Mesh 技术并非无线通信技术，而是一种网络（组网）的技术，用于构建 “多对多通信连接” 的网络。

简单来说，蓝牙 Mesh 组网就是将众多的蓝牙设备互相连接，进而组成一个网络。各个蓝牙设备在网络中被称为节点（某些关键节点被称为网关）。各节点之间能够互相进行通信。

**蓝牙 Mesh 能让我们建立无线设备之间的“多对多”（m:m）关系**。此外，设备能够将数据中继到不在初始设备直接无线电覆盖范围内的其他设备。这样，Mesh 网络就能够跨越非常大的物理区域，并包含大量设备。

> The new mesh capability enables many-to-many (m:m) device communications and is optimized for creating large-scale device networks. It is ideally suited for building automation, sensor networks, and other IoT solutions where tens, hundreds, or thousands of devices need to reliably and securely communicate with one another[[2\]](https://www.erenship.com/posts/63c7.html#fn:2).
>
> 新的网状功能可实现多对多 (m:m) 设备通信，并为创建大规模设备网络进行了优化。它非常适合楼宇自动化、传感器网络和其他物联网解决方案，在这些方案中，几十台、几百台或几千台设备需要可靠和安全地相互通信。

对于满足日益普及的各种通信需求，Mesh 拓扑结构能提供最佳的方式，因此蓝牙 Mesh 网络应运而生，典型的应用包括楼宇自动化和传感器网络等。这些通信需求包括：

- 覆盖面积广
- “直联互通性”
- 监测和控制大量设备的能力
- 经优化的、低功耗的
- 有效利用无线电资源，有可扩展性
- 与当前市场上的智能手机、平板电脑和个人电脑产品兼容
- 符合行业标准，具有政府级安全性

### 特性

- **以消息为中心的通信**

  **蓝牙 Mesh 网络使用发布/订阅 (publish/subscribe)消息系统**。

  设备可以将消息发送至特定地址，这些地址的名称和含义与用户能够理解的高级概念相对应，如“花园灯”(Garden Lights)。这被称为“发布”（publishing）。

  设备经配置后，可接收由其他设备发送到特定地址的消息。这被称为“订阅” (subscribing) 。

  当设备向特定地址发布消息时，订阅该地址的所有其他设备将收到该地址的副本，对其进行处理，并以某种方式作出回应。

  想象一下花园里安装的一套户外灯, 每盏灯都已经过配置，以便其订阅“花园灯”消息。现在，想像一个蓝牙Mesh 电灯开关向“花园灯”地址发送了 “开” 的消息。没错，花园里的所有灯都会收到 “ON” 消息，并做出开灯的回应。[![Snipaste_2020-09-13_13-11-08](%E8%93%9D%E7%89%99mesh%E6%B5%85%E8%B0%88.assets/20200913131151.png)](https://cdn.jsdelivr.net/gh/erenlu/PicGo//img/20200913131151.png)

- **消息和设备状态**

  **“状态” (state) 是蓝牙 Mesh 网络中的一个关键概念**。蓝牙 Mesh 网络中的每台设备都具有一组独立的状态值，表示设备的某些状态。在花园灯的示例中，每盏灯都有一个状态值，表示设备当前是处于打开或关闭状态。通过发布一类在定义上意味着能够回应“开”或“关”状态值的消息，来改变状态值，蓝牙 Mesh 电灯开关就能对灯泡进行控制。更改状态值会修改设备本身的物理状况，例如打开或关闭设备。

  消息、状态、以及这些和其他概念相关的设备行为已被定义在规格中，称为“模型”（modules）。模型由蓝牙Mesh 设备实施。

- **中继**

  **得益于 Mesh 网络，设备可以在非常广阔的区域中安装，同时彼此之间保持通信。**想象一下购物中心、机场或办公大楼的占地空间有多广阔。因为存在墙壁和其他物理上的障碍物，楼宇中的设备可能无法与安装在同一楼宇远侧的设备、或临近楼宇中的设备建立直接的无线连接。而蓝牙 Mesh 网络则能够将网络中的某些设备指定为“中继设备”，进而解决这一难题。

  **中继设备能够转发从其他设备接收到的消息。**在转发消息时，它们能够与位于初始消息发布设备无线范围以外的设备进行通信。消息可多次被中继，每一次中继即为一 “跳”，最多可进行 127 跳，足以在一片广阔的物理区域中进行消息传输。

  [![Snipaste_2020-09-13_12-54-27](%E8%93%9D%E7%89%99mesh%E6%B5%85%E8%B0%88.assets/20200913125504.png)](https://cdn.jsdelivr.net/gh/erenlu/PicGo//img/20200913125504.png)

- **管理型网络泛洪（Managed Flooding）**

  **蓝牙 Mesh 网络采用一种称为 “网络泛洪（flooding）” 的方式来发布和中继消息。**这意味着消息不会通过某一进程进行路由, 也不会沿着由一系列特定设备构成的特定路径来进行传输。相反，传输范围内的所有设备都会接收消息，负责中继的设备能将消息转发至其传输范围内的所有其他设备。

  **网络泛洪的优势在于无需特定设备专门扮演集中式路由器的角色。**集中式路由器一旦发生故障，就可能会导致整个网络无法运行。没有特定的路由也可能对网络造成灾难性的影响，但这种情况也可以通过在 Mesh 网络中采用网络泛洪的方法来避免。

  网络泛洪的方式也意味着消息一般能够通过多重路径到达其目的地。**这就构建了一个相当可靠的网络。**

  - **优化 Mesh 网络**

    **蓝牙 Mesh 网络也采取了一系列措施，支持采用网络泛洪的方式，同时优化每台设备、甚至整体网络的能耗。**

    所有数据包都包含一个称为 TTL 的字段，它可用于限制消息中继的跳数。由设备间歇性发送的心跳消息中包含的信息，能够让网络了解其拓扑结构、以及传到其他每台设备之间的跳数。这能够让设备将 TTL 设置为最佳值，从而避免不必要的中继操作。

    每台设备都包含消息缓存，以确定自身是否已经中继过该消息。如果是，则会立即丢弃该消息，从而避免上层堆栈进行不必要的处理。

  功率非常受限的设备（例如由小型电池持续供电多年的传感器）可能被指定为 “低功耗节点”。**低功耗节点能够与一个或多个被指定为 “friends” 的设备协同工作。**Friends 并非功率受限，它可以作为低功耗节点，存储寻址到这一低功耗节点的消息，并且只有在低功耗节点需要时才传送消息。**低功耗节点和 “friends” 之间的关系理所当然就称为 “friendship”。**

### 基本术语

- **节点（Node）**

  **蓝牙 Mesh 网络中的这些设备被称为节点 (node) 。**每个节点都能发送和接收消息。信息能够在节点之间被中继，从而让消息传输至比无线电波正常传输距离更远的位置。

- **元素（Elements）**

  一些节点（如传感器）的电池有可能会被耗尽，而其他节点（如照明设备、制造机械和安防摄像机）则会通过主电网来获取电力。一些节点的处理能力会高于其他节点。这些节点在 Mesh 网络中可承担更为复杂的任务，扮演不同的角色，表现出 **以下四个节点特征（Features）**：

  **低功耗 (Low-Power) 特性**

  功率受限的节点可能会利用低功耗特性来减少无线电接通时间并节省功耗。同时低功耗节点（LPN）可以与friend 节点协同工作。

  **Friend 特性**

  功率不受限的节点很适合作为 friend 节点。Friend 节点能够存储发往低功耗节点（LPN）的消息和安全更新；当低功耗节点需要时再将存储的信息传输至低功耗节点。

  **中继 (Relay) 特性**

  中继节点能够接收和转发消息，通过消息在节点之间的中继，实现更大规模的网络。节点是否能够具备这一特性取决于其电源和计算能力。

  **代理 (Proxy) 特性**

  代理节点能够实现 GATT 和蓝牙 Mesh 节点之间的 Mesh 消息发送与接收。承担这一角色的节点需要固定的电源和计算资源。

  [![Snipaste_2020-09-13_13-46-07](%E8%93%9D%E7%89%99mesh%E6%B5%85%E8%B0%88.assets/20200913134652.png)](https://cdn.jsdelivr.net/gh/erenlu/PicGo//img/20200913134652.png)

  **一些节点的复杂性高于其他节点，由多个称为元素（Element）的独立部分组成。**每个节点至少拥有一个元素，称为主元素（Primary Element），同时还可能包含其他多个元素。

  [![Snipaste_2020-09-13_13-28-21](%E8%93%9D%E7%89%99mesh%E6%B5%85%E8%B0%88.assets/20200913132902.png)](https://cdn.jsdelivr.net/gh/erenlu/PicGo//img/20200913132902.png)

  **元素由定义节点功能和元素条件的实体组成。**例如，一个灯泡内有一个元素, 并具有两种功能：

  **节点 = 灯泡**

  **一个元素 = 主元素**

  **节点功能：**

   - 开/关

   - 亮度

  **元素条件/状态：**

   - “开”或“关”

   - 0 – 10 (亮度等级)

  节点中的每个元素都有一个唯一的地址，称为单播地址（unicast address），使每个元素都有址可寻。

- **模型 (Model) 和状态 (State）**

  无论节点位于制造厂房、酒店、办公楼、还是商业园区的网络中，节点的基本功能都由模型（Model）来定义和实施。模型位于元素内，元素必须具有至少一个模型。**模型能够定义并实施节点的功能和行为，而状态 (State) 能够定义元素的条件**。

  [![Snipaste_2020-09-13_13-31-29](%E8%93%9D%E7%89%99mesh%E6%B5%85%E8%B0%88.assets/20200913133144.png)](https://cdn.jsdelivr.net/gh/erenlu/PicGo//img/20200913133144.png)

  以灯泡为例，该模型的功能是开关和调节亮度。相关的状态分别为 “开” / “关” 和 0-10：

  **模型 (节点功能)**

   **1. 开/关**

   状态 -> “开” 或 “关”

   **2. 亮度 (0-10)**

   状态 -> 0-10

  蓝牙 Mesh 支持复合状态，即由两个或多个值组成的状态。变色灯就是这样的一个例子，色调可以不受颜色饱和度或亮度的局限而改变。

  **“绑定状态” (Bound State) 这一术语的定义源自一种状态的变化导致另一状态变化的情况。**级别状态和开/关状态通常就相互绑定。如果级别从0变为1，则“开/关”的状态也从“关”变为“开”。

  每个模型都有唯一的标识符。蓝牙技术联盟采用 16 位的模型，而供应商采用 32 位（其中包含蓝牙技术联盟指定的16位公司标识符以及16位供应商指定的模型标识符）。**这确保了每个模型的地址都独一无二并且能确定被寻址到。**

  **蓝牙 Mesh 网络可借助消息，通过客户端 - 服务器架构进行通信。**服务器的功能是暴露元素的状态。最简单的状态之一是二进制开关，其中状态为“开”或“关”。简单的服务器模型是通用开/关服务器模型 (Generic On/Off Server Model) ，其中包含表示开关开启或关闭的状态。

  客户端可对状态进行访问，请求、更改或使用服务器的状态。举例来说，一个简单的客户端模型就是通用开/关客户端模型（Generic On/Off Client Model）（二进制开关）。通用开/关客户端模型通过发送消息来控制通用开/关服务器模型。例如，客户端可利用这一机制开启或关闭指示灯。

### 协议栈

**蓝牙 Mesh 网络引入了全新的协议栈**。这一协议栈建立在低功耗蓝牙技术之上。下图描绘了**协议栈的层级**。

[![Snipaste_2020-09-13_13-48-12](%E8%93%9D%E7%89%99mesh%E6%B5%85%E8%B0%88.assets/20200913134823.png)](https://cdn.jsdelivr.net/gh/erenlu/PicGo//img/20200913134823.png)

- **承载层（bearer layer）：**承载层定义了如何使用底层低功耗堆栈传输 PDU。目前定义了两个承载层：广播承载层（Advertising Bearer）和 GATT 承载层。
- **网络层（network layer）**：网络层定义了各种消息地址类型和网络消息格式。中继和代理行为通过网络层实施。
- **底层传输层（lower transport layer）：**在需要之时，底层传输层能够处理 PDU 的分段和重组。
- **上层传输层（upper transport layer）**：负责对接入层进出的应用数据进行加密、解密和认证。它还负责称为 “传输控制消息”（transport control messages）这一特殊的消息，包括与 “friendship” 相关的心跳和消息。
- **接入层（access layer）：**负责应用数据的格式、定义并控制上层传输层中执行的加密和解密过程，并在将数据转发到协议栈之前，验证接收到的数据是否适用于正确的网络和应用。
- **基础模型（foundation models）：**基础模型层负责实现与 Mesh 网络配置和管理相关的模型。
- **模型（models）：**模型层与模型等的实施、以及诸如行为、消息、状态等的实施有关。

节点（如照明装置、温控设备、制造设备和电动门）是蓝牙 Mesh 网络中能够发送、接收或中继消息的设备。消息（message）用于在节点之间传输数据，地址（address）用于定义消息源（source）地址和目的（destination）地址。

### **地址（Address）**

**地址有四种类型，其中的三类用于消息的传送：单播（unicast）、虚拟（virtual）和群组（group）地址。第四种被称为未分配（unassigned）地址。**地址长度为16位，并按下述定义进行编码。

[![640](%E8%93%9D%E7%89%99mesh%E6%B5%85%E8%B0%88.assets/20200913135kk700.webp)](https://cdn.jsdelivr.net/gh/erenlu/PicGo//img/20200913135kk700.webp)

**未分配地址（Unassigned Address）**

未经配置的元素或未被指定地址的元素拥有的就是未分配地址。鉴于这些元素没有唯一的地址，**它们不会用于消息的传送。**

**单播地址（Unicast Address）**

在“启动配置”（provisioning）期间，启动配置设备（provisioner）会在网络节点的生命周期内为节点中的每个元素分配一个单播地址。单播地址可能出现在消息的源地址字段或目的地址字段中。**发送到单播地址的消息只能由一个元素进行处理。**

**虚拟地址（Virtual Address）**

**虚拟地址是与特定的 UUID 标签相关联的一组元素**；这些地址可能会被发布或订阅。UUID 标签是与多个来自一个或多个节点的元素相关联的 128 位值。

对于虚拟地址，15 和 14 位分别设置为 1 和 0；13 – 0 位被设置为散列值（hash value）（提供 16384 个散列值）。散列（hash）来自于 Label UUID。使用订阅元素（subscribing element）来检查完整的 128 位 UUID 是十分低效的，特别当 UUID 跨越多个消息段时更为低效。**散列值提供了一种更为有效的方式来确定哪些消息被发送至哪些元素。**

**群组地址（Group Address）**

**群组地址是蓝牙 Mesh 网络中的另一种多播地址（multicast address）**，它通常代表一个或多个节点中的多个元素，包含两种类型：

- 动态分配的地址（Dynamically Assigned） -> 0xC000-0xFEFF
- 固定地址（Fixed Address） – 由蓝牙技术联盟分配，分为五段。

### 消息（Message）

**蓝牙 Mesh 网络通过消息进行通信。消息可以分为控制消息和接入消息。**

**控制消息（Control Message）：**与蓝牙 Mesh 网络操作有关的消息，例如心跳（heartbeat）和 friend 的请求消息。

**接入消息（Access Message）：**该类消息允许客户端模型检索或设置服务器模型中的状态值，或被服务器用于报告状态值。

模型可实施并定义节点的功能。**元素是节点内唯一可被寻址的实体（节点中可包含一个或多个模型），并由状态（state）定义元素的状况变化**。对于每个状态，都有一组服务器模型支持的消息。例如请求状态值或请求改变状态的客户端模型、以及发送状态或状态改变相关消息的服务器模型。

**接入消息分为两类：经确认的（acknowledged）和未经确认的（unacknowledged）**。经确认的消息被发送至每个接收元素，并经其确认。响应通常为状态消息。对于未经确认的消息则不作出响应。**例如蓝牙 Mesh 网络的状态消息就是一种未经确认的消息。**

### 安全（Security）

**所有蓝牙 Mesh 网络消息的安全保障都来自网络密钥（NetKey）和应用密钥（AppKey）对消息的加密和验证。**NetKey 用于网络层通信。假设蓝牙 Mesh 网络没有子网，则该 Mesh 网络内的所有通信都使用相同的网络密钥。

**AppKey 用于应用程序的数据。**网络中的一些节点具有特定应用，并且根据应用的需要对一些潜在敏感数据的访问进行限制。这些节点具有特定的 AppKey，并与特定应用相关联。会使用不同 AppKey 的领域通常包括安全（楼宇门禁、机房门禁和 CEO 办公室门禁）、照明（制造厂房、外部楼宇照明和人行道）和 HVAC 系统。

中继节点（relay node）（如灯泡或墙壁开关）通常具有有效的 NetKey，能够在网络内中继敏感性消息。然而，这些节点无法访问各种限制区域（如楼宇控制或 HVAC 系统）的特定 AppKey，，亦无法解密应用程序的数据。

### 启动配置（Provisioning）

启动配置的全过程包括大概 5 个步骤[[1\]](https://www.erenship.com/posts/63c7.html#fn:1), 分别是：

- Beaconing: 发送Beacon信号，告诉你我要配网, 这里使用的是新定义的 AD 广播包类型, Mesh AD；
- Invitation: 配网者 Provisioner 听到了这个 Beacon 以后, 就发一个邀请, 用的就是配网邀请 PDU（Protocol Data Unit）；
- Exchanging Public Keys: 交换公钥；
- Authentication: 一个互动随机数的认证流程；
- Distribution of the Provisioning Data: 认证完成, 从公钥和两个设备的私钥派生出 Session Key，后面的配网的信息交互的过程会用这个 Session key 来加密， 配网成功以后, 就会根据最后一步里面包含交换的 NetKey 来加密后面的数据交换

### 信息交换

**蓝牙 Mesh 网络使用发布/订阅 (publish/subscribe) 模型来进行消息传输。**生成消息的节点会发布消息。需要接收消息的节点会订阅它们所需的地址。消息可被发布至单播、群组或虚拟地址。

**消息可以作为对其他消息的回复而发送，也可以作为非请求消息（unsolicited messages）被发送。**当模型发送回复消息时，使用消息始发处的源地址作为目标地址。发送非请求消息时，模型将使用模型的发布地址作为目标地址。节点中的每个模型都有一个发布地址。

接收消息时，节点内模型（节点中可能存在多个模型）中的每个实例均可通过订阅方式从一个或多个群组或虚拟地址接收消息。

订阅消息的模型使用模型的订阅列表来定义用于接收消息的有效地址。当模型接收到消息时，模型将检查其订阅列表。**当订阅列表上的地址设置为模型的元素单播地址或属于该节点的固定群组地址时，则视为一个匹配（match）。**下图表示了接入消息的有效源地址和目标地址。

[![640 (1)](%E8%93%9D%E7%89%99mesh%E6%B5%85%E8%B0%88.assets/20200913141452.webp)](https://cdn.jsdelivr.net/gh/erenlu/PicGo//img/20200913141452.webp)

蓝牙 Mesh 实体发布各种节点的状态时，无论其与发送数据的节点位置距离远近,整个蓝牙 Mesh 网络中的系统均可订阅该数据。**这就实现了网络一端的设备可通过低功耗无线消息与设施中的其他的管理者进行对话，而不受距离限制。**

## 进阶篇

- [Bluetooth Mesh Networking: Friendship](https://www.bluetooth.com/blog/bluetooth-mesh-networking-series-friendship/)
- [蓝牙mesh网络 （ 友谊篇 ）](https://mp.weixin.qq.com/s?__biz=MzA4MTg3MTg2Mg==&mid=2651236984&idx=3&sn=a9ed5551ba9703a9ee93ed03a8459de5&chksm=847c5ce1b30bd5f71cca73920a9b1808d16372d8076ebcd226ece022f98a79d2eb7e331ffa21&scene=21#wechat_redirect)
- [蓝牙mesh网络（设备管理）](https://mp.weixin.qq.com/s?__biz=MzA4MTg3MTg2Mg==&mid=2651236997&idx=1&sn=99975f2b3930e36a2e8a040beed7cb75&chksm=847c5c1cb30bd50acc8745f37b2fa733171e2757529ac386cea58e6d2d62c326691e70888469&scene=21#wechat_redirect)
- [蓝牙mesh网络（安全性概览）](https://mp.weixin.qq.com/s?__biz=MzA4MTg3MTg2Mg==&mid=2651237018&idx=1&sn=87b36c6b36ead981e8b89903bcb0880f&chksm=847c5c03b30bd51596d772121c1454393a5dc3b2b03fc41a0eb590847cc8c4dde9b89c0a6f0a&scene=21#wechat_redirect)
- [蓝牙mesh网络（启动配置Part1）](https://mp.weixin.qq.com/s/aS16lAPmy4IRUgmcvqYe8g)
- [蓝牙mesh网络（启动配置Part2）](https://mp.weixin.qq.com/s/yaixqoR5s87c3uw5Uw7ccA)
- [潜入蓝牙mesh海洋深处](https://mp.weixin.qq.com/s/o2oTlXjzcbr0bDEU89uGuA)
- [蓝牙mesh | “三大法宝“让你的网络无懈可击](https://mp.weixin.qq.com/s/4g9dvRy3eJ9ToyMFWiDScQ)
- [蓝牙mesh网络：走进数据包](https://mp.weixin.qq.com/s/cFn3xQ4X3e87viqyDhJM_Q)

## 后记

虽然蓝牙 Mesh 组网技术的协议早已提出，但个人感觉相关 SDK 开发包仍不太成熟。不过未来应用场景仍然是可以畅想的。

正如蓝牙兴趣联盟所畅想的一样：

> 我们期待蓝牙 Mesh 网络广泛应用于各行各业和各种应用，预计最初会从**楼宇自动化、商业照明和传感器网络**等应用开始。尤其令人兴奋的是**蓝牙 Mesh 网络在商业照明方面的应用**。试想一下，有了正确的固件，照明系统能实现的就不仅是无线灯光控制，还能够成为楼宇中各种蓝牙服务的平台，如物资跟踪和定位服务！

## 参考

1. [蓝牙 Mesh 简介](http://www.xmamiga.com/3433/) [↩](https://www.erenship.com/posts/63c7.html#fnref:1)
2. [An Intro to Bluetooth Mesh Part 1](https://www.bluetooth.com/blog/an-intro-to-bluetooth-mesh-part1/) [↩](https://www.erenship.com/posts/63c7.html#fnref:2)
3. [An Intro to Bluetooth Mesh Part 2](https://www.bluetooth.com/blog/an-intro-to-bluetooth-mesh-part2/) [↩](https://www.erenship.com/posts/63c7.html#fnref:3)
4. [Introducing Bluetooth Mesh Networking](https://www.bluetooth.com/blog/introducing-bluetooth-mesh-networking/) [↩](https://www.erenship.com/posts/63c7.html#fnref:4)
5. [The Fundamental Concepts of Bluetooth Mesh Networking Part 1](https://www.bluetooth.com/blog/the-fundamental-concepts-of-bluetooth-mesh-networking-part-1/) [↩](https://www.erenship.com/posts/63c7.html#fnref:5)
6. [BLE和传统蓝牙有什么区别，各有什么优缺点？](https://www.zhihu.com/question/48722431/answer/599493049) [↩](https://www.erenship.com/posts/63c7.html#fnref:6)
7. [蓝牙mesh — 解密蓝牙mesh系列文章汇总](https://blog.csdn.net/zhanghuaishu0/article/details/78770486) [↩](https://www.erenship.com/posts/63c7.html#fnref:7)