# Digital-circuit-simulator
A digital circuit simulation software based on C++ and EasyX Library

#### 开发环境
* Microsoft Visual Studio 2019
* EasyX Graphics Library

#### 功能设计
1. 系统中，用不同符号表示与、或、非门、输入端和输出端，每个部件有输入引脚、输出引脚
2. 整个界面分为组件框和绘制框，用户可以在组件框中将数字逻辑电路部件用鼠标拖拽到绘制框中，以新建一个部件
3. 用户可以在绘制框上，通过鼠标拖动，随意更改数字逻辑电路部件的位置
4. 用户可以随意添加和删除任意一个部件
5. 用户可以在系统中，把各输入端、与门、或门、非门、输出端用连线进行引脚的连接
6. 用户可在系统中设置每个输入端的0或1的输入值
7. 系统检查用户的连接有无错误，若连接无误则计算并显示该部件的输出值
8. 系统计算并显示输出端的信号结果（0或1）
9. 用户现在可以使用滚动条移动绘制框以绘制更大更复杂的电路图

#### 功能实现
1. 使用C++的easyX库实现绘图和鼠标事件监测功能，数字电路计算等核心功能均仅使用C++实现。
2. **图像的显示**部分。使用Windows画图工具绘制与或非门、输入端、输出端及其被选中状态的图像，并在绘图器printer创建时，使用easyX提供的loadimage()函数从文件中读入图像，保存在printer对象的10个IMAGE对象中，并在绘图器printer调用print_ui()和print_widgets()函数绘图时调用easyX库中的putimage()函数直接使用IMAGE对象绘制图像。
绘图器printer的print_lines()函数会遍历所有部件，若该部件的输入引脚与其他部件的输出引脚相连，则绘制一条连线，为了使得连线符合数字电路绘图要求，编写了print_line()函数进行美化。
此外，绘图器printer的print_outputvalue ()函数会遍历所有部件，若该部件的输出引脚有正确的输出值（即0或1），则在输出引脚上方显示该值，否则显示“-”号。
3. **部件的拖动和连线**部分。部件的拖动和连线需要监测鼠标事件，所有鼠标事件均由mouse对象的check()调用easyX的库函数来检测，并由check()来处理。部件的拖动、连线和输入端数值的修改均由该函数控制。
4. **widget类对象的创建、储存和删除**部分。所有widget类对象都保存在C++标准库提供的unordered_map的一个实例widgets中，其中键为部件的编号id，值为widget类的对象的引用。当鼠标事件处理器mouse调用分配器contributor的创建部件的函数时，分配器contributor会为新对象分配内存空间和id，并将该新对象的引用储存到widgets当中，随后会立即调用fresh_i()函数以保证分配器的成员对象i为未被使用的最小id值。当一个widget类对象被删除后，占用的id被释放，这时鼠标事件处理器mouse会调用分配器contributor的set_i()以保证分配器的成员对象i为未被使用的最小id值。
5. **横向滚动条和纵向滚动条**在滑块移动时修改横向和纵向位移变量，将该变量添加到绘图和鼠标事件判断中，以实现绘制框的移动。

#### 不足与改进方向
1. ~~绘制框的大小有限，无法绘制复杂的电路图，后续可以扩大可操作的范围并添加缩放功能，使得软件能绘制更加复杂的电路图。~~
2. 目前只支持一次选择一个部件，然后对其进行移动，而不能进行部件的多选。后续可加入拖拽鼠标进行部件多选，使用键盘按键进行复制、粘贴、删除的功能。
3. CPU占用率高，性能有待优化。本软件需要循环进行鼠标事件的检测，在软件运行时CPU占用率较高，有待优化。