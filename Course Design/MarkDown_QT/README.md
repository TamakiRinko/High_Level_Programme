# 课程设计报告

## 一. 题目选择及主要实现内容

* 本次实验我选择了**简易Markdown编辑器**，实现了如下功能：
    * 所有题目说明中要求的语法格式及嵌套/混合使用。
    * **BlockQuote，图片，水平线，Code，删除线**等拓展语法。
    * 可以选择输出带有**内联式CSS**/**外部式CSS**的HTML文件。
    * 利用QT实现了**简易图形化编辑器**，可以进行简单编辑并保存转换为HTML文件。



## 二. 设计思路

#### Markdown解释器

* Markdown主体部分为一个解释器(`parser`)，负责将给定的Markdown文件转换为对应的HTML格式的文件。
* 对于解释器，需要考虑以下两方面：
    * 各种不同语法如何正确地转换为对应的HTML/CSS格式。本项目采用**正则表达式**进行查找与替换。
    * 各种不同语法相互嵌套/混合使用时的正确逻辑。本项目**未**采用递归或是词法分析器，而是使用**顺序逻辑**表达。
* 为统一管理项目中出现的字符串常量以及正则表达式，将它们放入类中，作为静态数据成员提供使用。

#### 文字编辑器

* 文字编辑器功能是完成简单的文件新建，编辑，修改，保存功能，同时为Markdown解释器中支持的语法配置相应的快捷键，使得编辑更为便捷。
* 作为项目的附加功能，其中并没有与Markdown语法逻辑相关的判断。

#### 解释器与编辑器的交互

* 采用"**半预览**"模式，当第一次保存文件后自动打开新的只读窗口，显示转换后的HTML文件。随后每次保存文件会自动更新HTML文件。
* **QTexiEdit**支持显示HTML4，但HTML5并不支持，故有一些语法并不支持，可以部分显示结果。



## 三. 支持的Markdown语法及对应正则表达式

```cpp
regex Values::SERegex(R"((\*\*\*)(.+?)(\*\*\*))");              //加粗斜体
regex Values::SRegex(R"((\*\*)(.+?)(\*\*))");                   //加粗
regex Values::ERegex(R"((\*)(.+?)(\*))");                       //斜体
regex Values::H1Regex(R"(^# )");                                //h1
regex Values::H2Regex(R"(^## )");                               //h2
regex Values::H3Regex(R"(^### )");                              //h3
regex Values::H4Regex(R"(^#### )");                             //h4
regex Values::H5Regex(R"(^##### )");                            //h5
regex Values::H6Regex(R"(^###### )");                           //h6
regex Values::LIRegex(R"(^[*+-] )");                            //列表
regex Values::LIORegex(R"(^(\d+)\.)");                          //有序列表
regex Values::LKSRegex(R"(\[(.*?)\]\((.+?)\))");                //链接
regex Values::BLQRegex(R"(^> )");                               //BlockQuote
regex Values::IMGRegex(R"(!\[(.*?)\]\((.+?)\))");               //图片
regex Values::HORLINRegex(R"(^---)");                           //水平线
regex Values::CODERegex(R"(`(.+?)`)");                          //Code
regex Values::MTNRegex(R"(~~(.+?)~~)");                         //删除线
```



## 四. 编辑器支持的功能

```cpp
新建文件						Ctrl+N;
打开文件						Ctrl+O;
保存文件						Ctrl+S;
复制							 Ctrl+C;
粘贴							 Ctrl+V;
剪切							 Ctrl+S;
H1~H6						  Ctrl+1~Ctrl+6;
加粗							 Ctrl+B;
斜体							 Ctrl+I;
图片							 Ctrl+Shift+I;
链接							 Ctrl+K;
语句间代码					   Ctrl+Shift+`;
删除线							Alt+Shift+5;
水平线							Ctrl+L;
引用							 Ctrl+Shift+Q;
```



## 五. 类设计

#### Values类

1. **作用**：统一管理项目中出现的字符串常量以及正则表达式，并提供HTML/内联式CSS/外部式CSS三种模式的切换。

2. **结构**：所有数据成员均作为**静态public数据成员**，使得所有的窗口使用同一个Values类。

3. **数据成员**：

    ```cpp
    static bool isInlineCSS;				//是否为内联CSS
    static bool isOutCSS;					//是否为外部CSS
    
    enum Status{							//文件处理过程中的三种状态
        NORMAL/*一般状态*/, LISTS/*列表*/, ORDEREDLISTS/*有序列表*/
    };
    
    static string htmlStart;				//HTML开头部分
    static string htmlEnd;					//HTML结尾部分
    static string CSSStart;					//外部式CSS开头部分
    ```

#### Parser类

1. **作用**：解释器主体类，包含用于处理Markdown文件各种语法的方法，以及相应的数据成员。

2. **结构**：

    * **对外接口**：

        ```cpp
        //构造函数，给定输入输出文件名，构造解释器对象。
        //具体工作：打开相应文件，根据输出类型(HTML/CSS)初始化相应的文件头部和其他变量。
        Parser(const char* inFileName, const char* outFileName);
        
        //处理接口，调用则开始处理文件。
        //具体工作：逐行读取文件内容，调用handleLine()函数处理每一行，并在处理结束后执行收尾工作，添加HTML结尾。
        void Handle();
        ```

    * **内部逻辑**：

        * 函数**主要作用**及函数间**调用关系**如下：
            * `handleLine()`，负责按行转换文件。
                * `handleLine()` &rArr; `blankHandle()`，处理空白行。
                * `handleLine()` &rArr; `listCount()`，处理每行前的空格，并以此确定当前列表层数。
                * `handleLine()` &rArr;`listLogic()`，具体处理(有序)列表嵌套逻辑。
                * `handleLine()` &rArr;`REHandle()`，当不是列表状态时，处理其他语法，转换为HTML代码。
            * `listLogic()`，利用栈来处理列表**嵌套**逻辑。
                * `listLogic()`&rArr;`REHandle()`，在处理完列表嵌套逻辑后，处理其他语法，转换为正则表达式。
                * `listLogic()`&rArr;`handleLine()`，当旧列表结束，新列表开始时，处理新的列表。
            * `REHandle()`，利用正则表达式处理除了列表外的其他语法。
                * `REHandle()`&rArr;`handleHtml()`，**HTML**模式或**外部式CSS**模式。
                * `REHandle()`&rArr;`handleCSS()`，**内联式CSS**模式。
            * `handleHtml()`和`handleCSS()`，按照HTML或外部式CSS或内联式CSS模式进行对语法进行处理。
                * `handleHtml`&rArr;`blqLogic()`，处理**Blockquote**逻辑。
            * `blqLogic()`，处理**Blockquote**逻辑
            * `blankHandle()`，处理空白行逻辑，每三个空白行为一个空行。
            * `lineHandle()`，去除每行开头的空格，并由此判断当前的列表层数等。

3. **具体逻辑解析**：

    * `blankHandle()`和`listCount()`，负责处理每行前的空格及空白行。将空格去除并以4个空格为单位计算当前列表层数。
        * 当出现连续三个空行，则在HTML文件中增加一个空行，即`&nbsp;`。若此时状态为(有序)列表，则应将状态退回到**NORMAL**。
        * 若Blockquote后出现一个空行，则当前Blockquote结束，增加相应的结束符。

    - `handleLine()`，处理每行文件的逻辑。
        - 首先，进行空白行和行前空格的处理。
        - 对于处理结束后的字符串，**判断读入行是否为列表或有序列表**。
            - 若是，则调用`listLogic()`函数处理列表嵌套逻辑。
            - 否则，若当前行是列表，则说明来了新的非列表，则将栈清空，结束列表并继续处理。若当前行不是列表，则直接处理非列表行即可。

    - `listLogic()`，处理(有序)列表嵌套逻辑。利用栈的**后进先出**特性来处理嵌套列表时`<ul>`，`<li>`等的插入问题。<font color=#99aaff>有序与无序列表处理逻辑相同，仅是结束符不同</font>。在当前读入行为列表时：
        - 若当前状态为**NORMAL**，则开始新的列表，当前列表层数为1。压入**层列表结束符**`</ul>`和**列表项结束符**`</li>`。
        - 若当前状态为**LISTS**或**ORDEREDLISTS**，说明当前已经是列表/有序列表。判断当前列表层次和读入的列表项层次关系。
            - <font color=#00aaff>若读入的列表项为子列表项</font>，则开始新的一级列表。
            - <font color=#00aaff>若读入的列表项与当前列表同级</font>，则有两种情况：
                - 若两者分别为列表和有序列表，且当前列表层数为1，说明旧列表结束，新列表开始，则将栈清空，调用`handleLine`按新列表重新处理该行。
                - 否则，说明列表仍未结束，弹出当前**列表项结束符**`</li>`，并压入读入的**列表项结束符**`</li>`。
            - <font color=#00aaff>若读入的列表项为父列表项</font>，则有两种情况：
                - 若两者分别为列表和有序列表，且当读入的列表项层数为1，说明旧列表结束，新列表开始，则将栈清空，调用`handleLine`按新列表重新处理该行。
                - 否则，弹出对应数量的**层列表结束符**`</ul>`，并压入读入的**列表项结束符**`</li>`
        - 在处理完列表嵌套逻辑后，处理其他的Markdown语法。
    - `handleHtml()`和`handleCSS()`，处理Markdown语法。**处理顺序依次为：标题(从六级至一级)，水平线，斜体加粗，加粗，斜体，图片，链接，行内代码，删除线，Blockquote。**当不是标题，(有序)列表和Blockquote时，需要在前后加上`<p>`和`</p>`，表示普通的一行。<font color=#99aaff>HTML处理方式和内联式CSS相同，仅为添加的内容不同。</font>
    - `blqLogic()`，处理Blockquote的逻辑。本项目中Blockquote**不支持嵌套**，仅支持顶行书写。
        - 定义bool变量`blqFlag`，代表是否在Blockquote模式
        - 定义bool变量`blqMatch`，代表Blockquote的`<p>`与`</p>`是否配对。
        - 当首次遇到`> `时，进入Blockquote模式，加入开始符号`<blockquote>\n<p>`，此时未配对。
        - 当再次次遇到`> `时，若当前`<p>`已匹配，则增加新的一行`<p>`，代表一个新的blockquote行。若当前`<p>`未配对，则说明未出现新的blockquote行，仅需在两段之间增加一个空格即可。
        - 若出现`>`单行，则说明出现换行，增加结束符`</p>`。
        - 若出现非blockquote行，则添加整体结束符`</blockquote>`

#### MainWindow类

1. **作用**：MainWindow类负责图形化编辑器以及它与Markdown解释器间的交互。在完成新文件的编辑后，可以将其保存到任意一个位置，同时选择保存的模式(HTML/内联式CSS/外部式CSS)。此时，会自动能够打开另一个**只读窗口**，展示该文件的处理后的样式。此后，每次保存，则会自动更新只读窗口，展示新的内容。

2. **结构**：

    * **数据成员**：

        ```cpp
        //============与HTML解释器的交互部分===========================
        MainWindow* htmlWindow;         //展示html文件的窗口
        QString htmlFileName;           //html文件的名称
        bool firstTime;                 //是否为第一次保存
        bool isInlineCSS;               //是否为内联式
        bool isOutCSS;                  //是否为外部式
        //=============文件本身性质部分================================
        QTextEdit* mainText;            //编辑的文字
        QString fileName;               //导入的文件名
        QString thisFileName;           //本窗口打开文件名
        bool isMDFile;                  //当前打开文件是否为md文件
        //=============菜单栏部分====================================
        QMenuBar* menubar;              //菜单栏
        QMenu* fileMenu;                //文件菜单
        QMenu* operationMenu;           //操作菜单
        //=============支持的操作部分=================================
        QAction* newFileAction;         //新建文件
        QAction* copyAction;            //复制
        QAction* strongAction;          //加粗
        ……………………//不全部展示
        ```

    * **内部逻辑**：

        * 函数**主要作用**及函数间**调用关系**如下：
            * `MainWindow()`，构造函数，负责初始化窗口，初始化编辑器，并设置相应的操作。构造函数具有参数`isMDFile`，**若该窗口不是为了打开Markdown文件，则不会有编辑器对应的快捷键，也不可以保存，新建，打开文件。这用于查看HTML文件。**
                * `MainWindow()`&rArr;`setAction()`，设置相应的槽函数。
            * `setAction()`，设置槽函数并与主窗口相关联。
            * `setReadOnly()`，使编辑器`mainText`变为只读。
            * `setWritten()`，使编辑器可编辑。
            * `saveFile()`，保存文件并转换为HTML样式。
                * `saveFile()`&rArr;`handleFile()`，与解释器部分交互，完成文件转换并展示。
        * **具体逻辑解析**：
            * `newFile()`，**新建文件**槽函数，新建一个窗口并展示。
            * `openFile()`，**打开文件**槽函数，当窗口为空且还未加载过其他文件时，将打开的文件直接放入到当前窗口中。否则新建一个窗口，打开文件放入。同时设置该窗口当前导入文件的名称(`fileName`)。
            * `loadFile()`，导入文件函数，将调用该函数的窗口中编辑器清空，导入文件的内容，并设置本窗口打开文件名称(`thisFileName`)和对应的HTML文件名(`htmlFileName`)。
            * `saveFile()`，**保存文件**槽函数，第一次保存则选择保存的位置，保存后打开保存的文件并用解释器来转换文件，保存到`htmlFileName`指示的文件中。第一次转换(或之前窗口被关闭)后新建只读窗口并导入转换后文件，后续每次保存后重新读入文件，转换后输出到窗口中。需要注意，每次在导入转换后的文件后，须将编辑器改为只读。
            * `closeEvent()`，覆盖父类的关闭方法。
                * **对于Markdown窗口**，当关闭文件时若文件已被修改，则询问是否保存到文件中。关闭主窗口，则对应的HTML只读窗口也会被关闭。
                * **对于HTML只读窗口**，则直接关闭，不影响对应Markdown窗口。
            * 对于`strong()`，`italic()`，`mistaken()`，检查光标是否选中区域，若选中，则对该部分进行操作，否则对于整行进行操作。对于`code()`，只有当选中光标区域时才会转换为行内代码。对于`image()`，`link()`，只有光标未有选择区域时才会插入。对于`h1()`~`h6()`，`horizon()`，`blockquote()`，无论光标是否选择区域，均有效。**由于相应的操作较为简单，故不再赘述。**



## 六. 遇到的问题

* **在HTML解释器方面**
    * 主要的难点在于列表的嵌套问题。在列表嵌套时，对应列表项的**结束符位置取决于其后续列表项的排列**。但是可以知道的是，当前列表项的结束符总是在同级下一个列表项到来或是父列表项到来时出现。所以最后选择用**栈**来存储，在对应的时候将保存着的结束符弹出。
    * 对于HTML解释器部分的类结构也并不明朗。虽然使用Values类来管理项目中的常量，但是私以为并无太大必要。面向对象的设计并不凸显。
    * 虽然没有完全详细说明，但是在解释器的**顺序逻辑表达**中，会出现很多边界情况，比如列表/Blockquote出现在文件末尾，两个不同列表相邻等等，在项目中的各个位置打上的"**补丁**"使得在后续拓展功能的嵌套方面出现了苦难。最终我的拓展功能里的Blockquote选择不支持嵌套。
* **在简易编辑器的实现方面**
    * 主要问题在于新学习的QT并不熟练，使用出现磕绊。同时编辑器的快捷键与Markdown的交互若想要做到类似于Typora那样的智能，相当困难，需要重新考虑各个语法间的关系，暂时难以做到。仅能完成基本的快捷键功能。
    * `QTextEdit`不支持HTML5和CSS，导致HTML文件展示不正确，仅能勉强观看。



## 七. 运行方法

* <font color = #ff0000>***在`Ubuntu 16.04`环境下***</font>
    * `./MarkDown`
* <font color = #ff0000>***注意：直接执行二进制文件，由于CSS文件路径的原因，无法使用外部式CSS样式。外部式CSS样式在现场演示时展示！***</font>
