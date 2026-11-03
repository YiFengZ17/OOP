# Lab 04 Personal Diary：用费曼学习法从零写到提交

> 这是一份**教学文档**，不是标准答案。你会一步步自己写出 `pdadd`、`pdlist`、`pdshow`、`pdremove` 四个程序。
> 文中给出类的“骨架”（声明）、关键片段和分级提示，但大部分函数体需要你自己写完。
> 文中所有片段和结论都已在 Linux + g++ 13 上编译、运行验证过。

---

## 目录

0. [这份文档怎么用（费曼学习法）](#0-这份文档怎么用费曼学习法)
1. [读懂题目](#1-读懂题目)
2. [大图景：四个店员，一本账本](#2-大图景四个店员一本账本)
3. [前置知识五节小课](#3-前置知识五节小课)
4. [面向对象设计：从题目里“抠”出类](#4-面向对象设计从题目里抠出类)
5. [设计数据文件格式](#5-设计数据文件格式)
6. [动手实现（六步）](#6-动手实现六步)
7. [测试清单](#7-测试清单)
8. [对照评分标准自检](#8-对照评分标准自检)
9. [整理提交](#9-整理提交)
10. [常见坑](#10-常见坑)
11. [费曼终极检验：讲给室友听](#11-费曼终极检验讲给室友听)
12. [进阶（可选）](#12-进阶可选)

---

## 0. 这份文档怎么用（费曼学习法）

费曼学习法只有四步：

| 步骤 | 做什么 | 在本文里的样子 |
| --- | --- | --- |
| ① 选概念 | 一次只学一个东西 | 每一小节只讲一个概念 |
| ② 讲给小白听 | 假装给完全不懂编程的人讲，只用大白话和类比 | **【大白话】**、**【类比】** |
| ③ 找卡壳点 | 讲不下去的地方就是你没真懂的地方，回去重学 | **【讲给自己听】**：合上文档回答这些问题 |
| ④ 简化 | 能用一句话讲清楚，才算懂了 | **【一句话】** |

每节还有：

- **【动手】**：要你自己敲的代码或命令。**一定要敲，别只看。**
- **【提示阶梯】**：折叠起来的提示，从“轻轻推一下”到“几乎告诉你”。**先自己想 5 分钟再展开第 1 级**，不够再展开下一级。

建议的学习顺序就是目录顺序。第 3 节的五节小课看起来和日记无关，但后面的代码全部建立在它们之上。

---

## 1. 读懂题目

### 1.1 截图里“消失”的参数

题目截图中命令是这样的：

```text
pdadd
pdlist [ ]
pdshow
pdremove
```

`pdadd` 后面什么都没有，`pdlist` 后面只剩一对空的 `[ ]`，这很奇怪。原因几乎可以肯定是：网页把 `<date>` 这样的尖括号内容当成 HTML 标签吞掉了。结合正文（“for the date”、“specified by the date”、“If start and end dates are provided”）和课程 FAQ（“`pdshow`、`pdremove` 使用日期参数”），可以还原为：

```text
pdadd    <date>
pdlist   [<start> <end>]
pdshow   <date>
pdremove <date>
```

`[ ]` 表示**可选**：`pdlist` 可以不带参数，也可以带两个日期。

### 1.2 逐句翻译

| 原文 | 意思 | 隐藏要求 |
| --- | --- | --- |
| `pdadd` is used to add an entity to the diary for the date. | `pdadd 日期`：给这一天写一篇日记 | 日期从**命令行参数**来 |
| If an entity of the same date is in the diary, the existing one will be replaced. | 同一天已有日记就**覆盖** | 一天最多一篇 |
| reads lines of the diary from the stdin, line by line, until a line with a single `.` character or the EOF | 内容从**标准输入**一行行读，遇到“单独一个点的一行”或“输入结束”就停 | 两种结束方式都要支持 |
| `pdlist` lists all entities in the diary ordered by date. | 按日期顺序列出全部日记 | 必须**有序** |
| If `start` and `end` dates are provided… lists entities between the start and the end only. | 给了起止日期就只列这个范围 | 需要决定：包含端点吗？（建议包含） |
| This program lists to the stdout. | 输出到标准输出 | 能被重定向到文件 |
| `pdshow` prints the content of the entity specified by the date to the stdout. | 打印某天日记的内容 | 找不到怎么办？你来设计 |
| `pdremove` removes one entity of the date. It returns 0 on success and -1 on failure. | 删除某天日记，`main` 返回 0 或 -1 | **返回值**有硬性要求 |
| The software stores the diary in one data file, and reads it to the memory at the beginning of each program, and stores it back to the file at the end of the process. | 所有日记存在**一个**文件里；每个程序开始时读入内存，结束时写回 | 四个程序共用一个文件 |

### 1.3 评分标准翻译

| # | 原文 | 白话 | 你要做到 |
| --- | --- | --- | --- |
| 1 | C++ code quality (clean, compact, and reasonable) | 代码干净、紧凑、合理 | 无重复、无巨型函数、命名清楚 |
| 2 | Comments quality | 注释质量 | 注释写**为什么**，而不是把代码翻译成英文 |
| 3 | Common classes and functions should be shared between programs | 公共类和函数要在程序间共享 | 日期、日记等类只写**一份**，四个程序都用它 |
| 4 | These programs are physically independent, so direct interaction is not permitted | 四个程序物理上独立，不许直接互相调用 | 四个独立的可执行文件，彼此只通过数据文件“交流” |
| 5 | These programs are able to work together by means of redirection | 能通过重定向协同工作 | `<`、`>`、`\|` 都能用，输出里不混杂提示语 |
| 6 | These programs are able to be used in a shell/batch script | 能在脚本里使用 | 不依赖人工交互；返回值有意义。FAQ 还要求写一个“分发脚本”，例如 `bash myscript.sh pdadd ...` |

提交物：源代码 + 一个覆盖全部四个程序的 shell/batch 测试脚本（以及课程统一要求的 README 和 PDF 报告，见第 9 节）。

### 【讲给自己听】

合上文档，用**三句话**向一个不学计算机的朋友解释这个作业要做什么。如果第三句话说不出来，回去重读 1.2。

---

## 2. 大图景：四个店员，一本账本

### 【类比】

想象一家小店有一本**账本**（数据文件 `diary.dat`），放在柜子里。店里有四个店员，每人只会干一件事：

| 店员 | 程序 | 工作 |
| --- | --- | --- |
| 记账员 | `pdadd` | 往账本里写一页（同一天的旧页撕掉换新） |
| 目录员 | `pdlist` | 报出账本里有哪些天的记录 |
| 朗读员 | `pdshow` | 把某一天那页念出来 |
| 撕页员 | `pdremove` | 撕掉某一天那页 |

规矩是：

1. **店员之间从不说话**（物理独立）。记账员不能喊朗读员帮忙，只能把东西写进账本，别人以后自己去看。
2. 每个店员**上班时**把账本从柜子搬到桌上（读入内存），**下班时**放回柜子（写回文件）。
3. 四个店员用**同一套文具**（公共类）：同样的尺子量日期、同样格式的纸。文具只造一套，大家共用。

### 代码层面的样子

```text
   Date.cpp   Entry.cpp   Diary.cpp   cli.cpp        ← 公共代码：只写一份（评分 3）
        \         |           |         /
         \________|___________|________/
          |           |           |          |
     pdadd.cpp   pdlist.cpp   pdshow.cpp   pdremove.cpp   ← 每个文件一个 main
          ↓           ↓           ↓          ↓
        pdadd       pdlist      pdshow     pdremove       ← 4 个独立可执行文件（评分 4）
          \___________\___________/__________/
                          ↓
                      diary.dat                           ← 唯一的“交流渠道”
```

**“物理独立”到底禁止什么？** 禁止 `pdadd` 内部用 `system("./pdlist")` 之类的方式调用别的程序，也禁止把四个功能塞进一个程序再用参数区分。允许的是**源代码复用**：四个程序 `#include` 同一个头文件，链接同一份编译结果。

### 【一句话】

四个各自独立的程序，共用一套类，通过同一个数据文件间接合作。

### 【讲给自己听】

1. “代码共享”和“程序独立”矛盾吗？为什么不矛盾？
2. 如果把四个功能写进一个 `pd` 程序，用 `pd add`、`pd list` 区分，违反了哪条评分标准？

---

## 3. 前置知识五节小课

### 3.1 `main` 的参数：`argc` 和 `argv`

**【大白话】** 你在命令行敲的每一个“词”，都会被装进一个数组交给 `main`。

```cpp
int main(int argc, char* argv[])
```

- `argc`（argument count）：一共几个词，**包括程序名本身**。
- `argv`（argument vector）：这些词，每个都是 C 字符串。

敲 `./pdlist 20221101 20221130` 时：

| 表达式 | 值 |
| --- | --- |
| `argc` | `3` |
| `argv[0]` | `"./pdlist"` |
| `argv[1]` | `"20221101"` |
| `argv[2]` | `"20221130"` |

**【动手】** 新建 `echo_args.cpp`（练习用，不提交）：

```cpp
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "argc = " << argc << '\n';
    for (int i = 0; i < argc; ++i) {
        std::cout << "argv[" << i << "] = " << argv[i] << '\n';
    }
}
```

```bash
g++ echo_args.cpp -o echo_args
```

```bash
./echo_args
```

```bash
./echo_args 20221101 "hello world" 42
```

注意第二条命令里 `"hello world"` 是**一个**参数——引号让 shell 把空格内的内容当成一个词。

**【讲给自己听】**

1. 只敲 `./pdadd`，`argc` 是几？这时访问 `argv[1]` 会怎样？（提示：所以必须**先检查 `argc` 再用 `argv`**。）
2. `pdlist` 合法的 `argc` 有哪几种？

---

### 3.2 三根水管：stdin、stdout、stderr 与重定向

**【类比】** 每个程序都是一个盒子，自带三根水管：

| 水管 | C++ 里 | 默认接到 | 用途 |
| --- | --- | --- | --- |
| 进水管 stdin | `std::cin` | 键盘 | 读数据 |
| 出水管 stdout | `std::cout` | 屏幕 | 输出**正经结果** |
| 报警管 stderr | `std::cerr` | 屏幕 | 输出**提示语和错误信息** |

**shell 可以在程序启动前把水管改接到别处，程序本身完全不知道、也不需要知道。** 这就是“通过重定向协同工作”的全部秘密。

| 写法 | 意思 | 例子 |
| --- | --- | --- |
| `prog < file` | 进水管接到文件 | `./pdadd 20221101 < today.txt` |
| `prog > file` | 出水管接到文件（覆盖） | `./pdlist > all.txt` |
| `prog >> file` | 出水管接到文件（追加） | `./pdshow 20221101 >> backup.txt` |
| `prog 2> file` | 报警管接到文件 | `./pdshow 19990101 2> err.txt` |
| `prog 2>/dev/null` | 报警管接到“黑洞”（丢弃） | 脚本里静音提示语 |
| `a \| b` | `a` 的出水管直接接 `b` 的进水管 | `./pdshow 20221101 \| ./pdadd 20221102` |
| `prog <<'END'` … `END` | here-document：把脚本里的几行当作输入 | 测试脚本里常用 |

**关键推论：正经结果写 `cout`，提示语和错误写 `cerr`。**

为什么？设想 `pdshow` 先 `cout << "Here is your diary:\n"` 再打印内容：

- `./pdshow 20221101 > backup.txt` —— 备份文件里混进了这句废话。
- `./pdshow 20221101 | ./pdadd 20221102` —— 这句废话被当成日记内容写进了 11 月 2 日！

写到 `cerr` 就没问题：`cerr` 不走出水管，重定向 stdout 时它照样显示在屏幕上，也不会流进下一个程序。

**【动手】** 在 shell 里体验一下（不用写 C++）：

```bash
echo hello > a.txt
```

```bash
cat < a.txt
```

```bash
ls /nonexistent 2> err.txt; cat err.txt
```

```bash
printf 'line1\nline2\n' | wc -l
```

**【一句话】** 程序只管读 `cin`、写 `cout`/`cerr`；数据从哪来、到哪去，由 shell 决定。

**【讲给自己听】** `pdadd` 想提示用户“请输入内容”，应该写到哪根管子？为什么？

---

### 3.3 EOF 与 `getline`

**【大白话】** EOF（End Of File）**不是一个字符**，而是一种状态：“进水管里再也不会有水了”。

- 进水管接的是**文件**：读完自然就是 EOF。
- 进水管接的是**键盘**：要手动告诉程序“我输完了”：
  - Linux / macOS：在**一行的开头**按 `Ctrl-D`。（在行中间按，只是把这半行先送出去；再按一次才是 EOF。）
  - Windows：在一行开头按 `Ctrl-Z`，再按回车。

**读行的标准写法：**

```cpp
std::string line;
while (std::getline(std::cin, line)) {
    // 处理 line（已经去掉了末尾的 '\n'）
}
```

`std::getline` 返回流本身；流放在 `while (...)` 里会被当成“还能继续读吗”。读到 EOF 时变成 `false`，循环自然结束。

**题目要求两种结束条件**，正好对应循环里两个出口：

```cpp
std::string line;
while (std::getline(in, line)) {   // 出口①：EOF，getline 失败，循环条件为假
    if (line == ".") break;        // 出口②：读到只有一个点的一行
    lines.push_back(line);
}
```

这几行就是 `pdadd` 的心脏。

**两个坑：**

1. **不要写 `while (!std::cin.eof())`。** `eof()` 只有在“尝试读并且失败了”之后才会变成 `true`，它总是晚一步，最后一行会被多处理一次。
2. **Windows 换行是 `\r\n`。** 在 Linux 上读 Windows 编辑的文件，`line` 末尾会残留一个 `'\r'`，于是 `".\r" != "."`，点号结束失效。补救：

   ```cpp
   if (!line.empty() && line.back() == '\r') line.pop_back();
   ```

**【讲给自己听】**

1. EOF 是字符吗？在键盘上怎么“输入” EOF？
2. 用户输入 `.`（前面有个空格），应该结束吗？（题目说 “a single `.` character”，所以按 `line == "."` 严格判断即可；无论选哪种，在 README 里写清楚。）

---

### 3.4 返回值就是“退出码”

**【大白话】** `main` 的 `return` 值会交给 shell，表示“我干得怎么样”。在 shell 里用 `$?` 查看上一个程序的退出码。

```bash
ls /; echo $?
```

```bash
ls /nonexistent; echo $?
```

**Unix 约定：0 表示成功，非 0 表示失败。** 这和 C 语言里“0 是假”的直觉正好相反，记住它。

**`return -1` 会变成 255？** 是的。在 Linux / macOS 上，退出码只保留最低 8 位（0–255），`-1` 的最低 8 位是 `255`，所以：

```bash
./pdremove 19990101; echo $?
# 输出 255
```

题目要求 `pdremove` 失败时返回 `-1`，代码里就写 `return -1;`，然后在 README 中说明“在 Unix shell 中显示为 255”。（Windows 的 `%ERRORLEVEL%` 会显示 `-1`。）

退出码让脚本能做判断：

```bash
if bash pd.sh pdremove 20221101; then
    echo "removed"
else
    echo "nothing to remove"
fi
```

**【讲给自己听】** 为什么 `pdshow` 找不到日记时，也应该返回非 0？（提示：评分 6，脚本要能知道失败了。）

---

### 3.5 多文件编译：`.h`、`.cpp` 和链接

**【类比】** `.h` 头文件是**菜单**（声明：有哪些菜、叫什么名字），`.cpp` 源文件是**厨房**（定义：菜具体怎么做）。别人想点菜，只需要看菜单——也就是 `#include "Diary.h"`。

**编译分两个阶段：**

1. **编译**：每个 `.cpp` **单独**翻译成一个 `.o` 目标文件。此时只要看到声明（菜单）就够了。
2. **链接**：把若干 `.o` 拼成一个可执行文件。此时每个用到的函数都必须找到定义（厨房）。

```bash
g++ -std=c++11 -c Date.cpp       # → Date.o
g++ -std=c++11 -c Entry.cpp      # → Entry.o
g++ -std=c++11 -c Diary.cpp      # → Diary.o
g++ -std=c++11 -c pdadd.cpp      # → pdadd.o
g++ pdadd.o Date.o Entry.o Diary.o -o pdadd
```

**一个可执行文件只能有一个 `main`。** 所以四个程序 = 四个各含一个 `main` 的文件，每个都和**同一批**公共 `.o` 链接。公共代码只编译一次、用四次——这就是评分 3 的落地方式。

**include guard（头文件保护）**：如果 `Entry.h` 和 `Diary.h` 都 `#include "Date.h"`，而 `pdadd.cpp` 同时包含了两者，`Date` 类就会被定义两次而报错。解决方式：

```cpp
#ifndef DATE_H
#define DATE_H
// ...类声明...
#endif
```

第一次包含时定义 `DATE_H`；第二次发现已定义，整段跳过。

**两种最常见的链接错误：**

| 报错 | 原因 |
| --- | --- |
| `undefined reference to 'Diary::load()'` | 声明了但没写定义，或者链接时漏了 `Diary.o` |
| `multiple definition of 'main'` | 把两个含 `main` 的 `.o` 链接进了同一个程序 |

**【讲给自己听】**

1. 只改了 `Diary.cpp`，需要重新编译 `pdadd.cpp` 吗？需要重新链接 `pdadd` 吗？
2. 为什么不能把四个 `pd*.cpp` 一起编译成一个程序？

---

## 4. 面向对象设计：从题目里“抠”出类

### 4.1 名词找类，动词找方法

把题目里的**名词**圈出来：diary、entity、date、line、data file、stdin、stdout……
把**动词**圈出来：add、replace、list、order by date、show、remove、read to memory、store back……

逐个判断名词值不值得成为一个类：

| 名词 | 成为类？ | 理由 |
| --- | --- | --- |
| date | ✅ `Date` | 有自己的规则：格式是否合法、谁先谁后、怎么打印 |
| entity（一篇日记） | ✅ `Entry` | 日期 + 若干行内容；会“从流里读出自己”“把自己写进流” |
| diary（整本日记） | ✅ `Diary` | 管理全部日记；负责和数据文件打交道；增、删、查、列 |
| line | ❌ | 就是 `std::string` |
| data file | ❌ | 只是 `Diary` 记住的一个路径 |
| program | ❌ | 就是各自的 `main` |

再把动词分给最“知情”的类：

| 类 | 知道什么（数据） | 会做什么（方法） |
| --- | --- | --- |
| `Date` | 年、月、日 | 从字符串解析并校验、转回字符串、比较先后 |
| `Entry` | 一个 `Date`、若干行文字 | 从输入流读内容、把内容写到输出流、取第一行 |
| `Diary` | 文件路径、全部 `Entry`、是否改动过 | 加载、保存、添加（覆盖）、查找、删除、全部列出、按范围列出 |

```text
┌────────────────────┐       ┌─────────────────────────┐       ┌───────────────────────────┐
│ Date               │       │ Entry                   │       │ Diary                     │
├────────────────────┤ 1   1 ├─────────────────────────┤ *   1 ├───────────────────────────┤
│ - year_, month_,   │◄──────│ - date_ : Date          │◄──────│ - path_ : string          │
│   day_ : int       │       │ - lines_ : vector<str>  │       │ - entries_: map<Date,Entry>│
├────────────────────┤       ├─────────────────────────┤       │ - modified_ : bool        │
│ + parse(str, out)  │       │ + date()                │       ├───────────────────────────┤
│ + toString()       │       │ + firstLine()           │       │ + load() / save()         │
│ + operator<        │       │ + readContent(istream&) │       │ + add / find / remove     │
└────────────────────┘       │ + writeContent(ostream&)│       │ + all / between           │
                             └─────────────────────────┘       └───────────────────────────┘
```

### 4.2 封装：为什么成员要 `private`

**【类比】** 银行柜台。你不能自己走进金库拿钱，必须通过柜员（公有方法）。这样银行才能保证每笔账都被记录。

如果 `Diary` 的 `entries_` 是 `public`，`pdadd.cpp` 就可以绕过 `add()` 直接往 map 里塞东西——那么“改动过”标记不会更新（第 6 步你会看到这会导致什么问题），以后想把 `map` 换成别的容器时，四个程序都得改。**把数据藏起来，只暴露“能做什么”，修改的影响就被关在类内部。**

### 4.3 为什么用 `std::map<Date, Entry>`

**【类比】** `std::map` 像一个**按标签自动排好序的抽屉柜，每个标签只有一个抽屉**。

- 题目要求“ordered by date” → map 按 key 自动排序，**免费得到**。
- 题目要求“同一天覆盖” → map 的 key 唯一，**免费得到**。
- 按范围列出 → map 有 `lower_bound` / `upper_bound`，**免费得到**。

选对容器，一半功能就自动完成了。代价是：map 需要知道两个 key 谁小，所以 `Date` 必须提供 `operator<`。（这是第一次接触运算符重载，Assignment 05 会深入。）

### 【讲给自己听】

1. 为什么 `load` / `save` 放在 `Diary` 而不是 `Entry`？
2. 用 `std::string` 存 `"20221101"` 当 key 也能按字典序排对，为什么还要写 `Date` 类？（提示：合法性校验写在哪？`20220230` 谁来拦？）
3. 用一句话讲清楚“封装”。

---

## 5. 设计数据文件格式

题目没规定数据文件长什么样，你来设计。需求：能存多篇；每篇可以多行；保存后再读回来要**一模一样**。

| 方案 | 样子 | 问题 |
| --- | --- | --- |
| A：一篇一行 | `20221101\|今天很开心` | 内容一旦多行就崩；内容里有 `\|` 也崩 |
| B：日期 + 行数 + 内容 | `20221101` / `2` / 两行内容 | 可行，但手工修改文件时容易数错行数 |
| C：日期行 + 内容 + 单独一行 `.` | 见下 | 和 `pdadd` 的输入格式**完全一样** |

推荐方案 C：

```text
20221101
First day of November.
Learned argc/argv.
.
20221110
Went hiking.
.
```

**费曼时刻——为什么用 `.` 当分隔符一定安全？** 请先自己想，再往下看。

<details>
<summary>展开答案</summary>

内容全部来自 `pdadd`，而 `pdadd` 一读到单独的 `.` 就停止了。所以任何日记内容里**不可能**存在单独一行 `.`。拿一个“内容中不可能出现的东西”作分隔符，就永远不会误判。

</details>

**额外收获：** 读文件里一篇日记的内容，和从键盘读 `pdadd` 的输入，是**同一套规则**。所以 `Entry::readContent(std::istream& in)` 写一次，`pdadd` 传 `std::cin`、`Diary::load` 传 `std::ifstream`，两处共用。这能行，是因为 `std::cin` 和 `std::ifstream` 都“是一种” `std::istream`（继承关系，后面的课会讲）。

**数据文件放哪？** 默认用当前目录下的 `diary.dat`。建议再支持一个可选的环境变量 `PD_DATA` 来指定路径：测试脚本可以用一个临时文件，不会弄脏你真正的日记。

```bash
PD_DATA=/tmp/test.dat ./pdlist
```

---

## 6. 动手实现（六步）

先建好目录（符合课程提交规范，见第 9 节）：

```text
Assignment04_<学号>_<姓名拼音>/
├── README.md
├── code/
│   ├── Date.h      Date.cpp
│   ├── Entry.h     Entry.cpp
│   ├── Diary.h     Diary.cpp
│   ├── cli.h       cli.cpp
│   ├── pdadd.cpp   pdlist.cpp   pdshow.cpp   pdremove.cpp
│   ├── Makefile
│   ├── pd.sh       （分发脚本）
│   └── test.sh     （测试脚本）
└── report/
    └── Assignment04_<学号>_<姓名拼音>.pdf
```

**原则：每写完一个类就单独测试它，再写下一个。** 不要等四个程序都写完才第一次编译。

---

### 第 1 步：`Date`

**骨架（`Date.h`）：**

```cpp
#ifndef DATE_H
#define DATE_H

#include <string>

// A calendar date written as YYYYMMDD on the command line and in the data file.
class Date {
public:
    Date() = default;

    // Parses "YYYYMMDD". Returns false (and leaves out unchanged) if the text
    // is not a real calendar date, e.g. "20220230" or "2022111".
    static bool parse(const std::string& text, Date& out);

    std::string toString() const;               // back to "YYYYMMDD"
    bool operator<(const Date& other) const;    // lets std::map sort by date

private:
    int year_ = 0;
    int month_ = 0;
    int day_ = 0;
};

#endif
```

**你要在 `Date.cpp` 里写：**

1. `parse`：长度必须是 8 → 每个字符都是数字 → 拆出年、月、日 → 检查月份 1–12、日期不超过当月天数（注意闰年）→ 成功才写入 `out`。
2. `toString`：注意补零，2022 年 1 月 5 日要输出 `20220105` 而不是 `202215`。
3. `operator<`：先比年，年相同比月，月相同比日。

<details>
<summary>提示阶梯 1：拆字符串</summary>

`text.substr(起点, 长度)` 取子串，`std::stoi` 把字符串转成整数。年是 `substr(0, 4)`，月和日呢？

判断数字可以用 `<cctype>` 里的 `std::isdigit`。

</details>

<details>
<summary>提示阶梯 2：闰年与每月天数</summary>

闰年：能被 4 整除且不能被 100 整除，或者能被 400 整除。

写两个只在 `Date.cpp` 内部用的小函数（前面加 `static`，表示“仅本文件可见”）：

```cpp
static bool isLeapYear(int year);
static int daysInMonth(int year, int month);   // 用一个 12 个元素的数组
```

</details>

<details>
<summary>提示阶梯 3：补零输出</summary>

两种写法任选：

```cpp
// 写法一：<cstdio>
char buf[9];
std::snprintf(buf, sizeof buf, "%04d%02d%02d", year_, month_, day_);
return buf;
```

```cpp
// 写法二：<sstream> + <iomanip>
std::ostringstream os;
os << std::setfill('0') << std::setw(4) << year_
   << std::setw(2) << month_ << std::setw(2) << day_;
return os.str();
```

</details>

**【动手】测试 `Date`**（写一个临时的 `test_date.cpp`，不提交）：

| 输入 | 期望 `parse` 结果 |
| --- | --- |
| `20221101` | true，`toString()` 为 `20221101` |
| `20240229` | true（闰年） |
| `20230229` | false（非闰年） |
| `19000229` | false（能被 100 整除但不能被 400 整除） |
| `20000229` | true（能被 400 整除） |
| `20220230` | false |
| `20221301` | false |
| `2022111` | false（长度不对） |
| `2022110a` | false（有非数字） |

**【讲给自己听】**

1. `parse` 为什么是 `static`？（提示：调用它的时候，还没有一个合法的 `Date` 对象。）
2. 为什么用“返回 `bool` + 引用参数 `out`”的写法？（它要同时告诉你“成没成功”和“结果是什么”。）
3. 函数名后面的 `const`（如 `toString() const`）是什么意思？

---

### 第 2 步：`Entry`

**骨架（`Entry.h`）：**

```cpp
#ifndef ENTRY_H
#define ENTRY_H

#include "Date.h"

#include <iosfwd>     // forward declarations of std::istream / std::ostream
#include <string>
#include <vector>

// One diary entity: a date plus any number of text lines.
class Entry {
public:
    explicit Entry(const Date& date);

    const Date& date() const;
    std::string firstLine() const;   // short summary for pdlist; "" if empty

    // Replaces the content with lines read from in, stopping at a line that is
    // exactly "." or at end of input. Used for both stdin and the data file.
    void readContent(std::istream& in);

    // Writes the content lines only (no date, no terminating ".").
    void writeContent(std::ostream& out) const;

private:
    Date date_;
    std::vector<std::string> lines_;
};

#endif
```

**你要在 `Entry.cpp` 里写：** 构造函数（用初始化列表 `: date_(date)`）、`date()`、`firstLine()`、`readContent()`、`writeContent()`。

`readContent` 的核心循环你在 3.3 已经见过了，把它和 `'\r'` 的处理组合起来即可。别忘了开头先 `lines_.clear()`——“读内容”的语义是**替换**。

> `Entry.cpp` 里要 `#include <istream>` 和 `#include <ostream>`，因为头文件里的 `<iosfwd>` 只是“前向声明”，告诉编译器“有这么个类型”，但没有给出完整定义。

**【动手】测试 `Entry`**：写一个临时 `main`，构造一个 `Entry`，调用 `readContent(std::cin)`，再 `writeContent(std::cout)`，然后试：

```bash
printf 'a\nb\n.\nc\n' | ./test_entry
```

期望只输出 `a` 和 `b`（`.` 之后的 `c` 被忽略）。

```bash
printf 'a\nb' | ./test_entry
```

期望输出 `a` 和 `b`（没有 `.`，靠 EOF 结束；而且最后一行没有换行符也能读到）。

**【讲给自己听】**

1. 参数为什么是 `std::istream&`，而不是在函数里直接用 `std::cin`？
2. 为什么 `Entry` 没有默认构造函数？（没有日期的日记有意义吗？）

---

### 第 3 步：`Diary`

**骨架（`Diary.h`）：**

```cpp
#ifndef DIARY_H
#define DIARY_H

#include "Date.h"
#include "Entry.h"

#include <map>
#include <string>
#include <vector>

// The whole diary: loaded from one data file at program start and written
// back at the end. Entries are kept sorted by date, one entry per date.
class Diary {
public:
    explicit Diary(const std::string& path);

    // Data file path: $PD_DATA if set, otherwise "diary.dat".
    static std::string defaultPath();

    bool load();          // a missing file means an empty diary
    bool save() const;    // writes only if something changed (see below)

    void add(const Entry& entry);                // replaces same-date entry
    const Entry* find(const Date& date) const;   // nullptr if absent
    bool remove(const Date& date);               // false if absent

    std::vector<const Entry*> all() const;
    std::vector<const Entry*> between(const Date& from, const Date& to) const;

private:
    std::string path_;
    std::map<Date, Entry> entries_;
    bool modified_ = false;
};

#endif
```

下面逐个方法讲思路，代码你来写。

**`load()`**

```text
打开文件（std::ifstream）
如果打不开 → 视为第一次使用，空日记，返回 true
循环读一行作为日期行：
    去掉末尾 '\r'；空行就跳过
    用 Date::parse 解析；失败 → 文件损坏，往 cerr 报错，返回 false
    用这个日期构造 Entry，调用 entry.readContent(文件流)
    add(entry)
循环结束后 modified_ = false   ← 想想为什么
返回 true
```

**`save()`**

```text
如果 modified_ 为 false → 什么都不写，直接返回 true
用 std::ofstream 打开（覆盖写）；打不开 → cerr 报错，返回 false
遍历 entries_：写日期行，writeContent，再写一行 "."
返回写入是否成功
```

**`add()`**：先 `entries_.erase(日期)`，再 `entries_.insert(std::make_pair(日期, entry))`，最后 `modified_ = true`。

> 为什么不写 `entries_[date] = entry;`？因为 `operator[]` 在 key 不存在时要先**默认构造**一个 `Entry`，而 `Entry` 故意没有默认构造函数，编译会报错。用 C++17 的话也可以写 `entries_.insert_or_assign(date, entry);`。

**`find()`**：用 `entries_.find(date)`；找到就返回 `&it->second`，找不到返回 `nullptr`。

> **【类比】** 你问图书管理员要一本书：有，他就**指给你**书在哪（指针）；没有，他就摇头（`nullptr`）。他不会复印一本给你（不返回拷贝），也不会让你随便在书上涂改（`const`）。

**`remove()`**：`entries_.erase(date)` 会返回删掉了几个元素（0 或 1）。删掉了才把 `modified_` 设为 `true`。

**`all()` 和 `between()`**：遍历 map，把每个 `&pair.second` 放进结果 `vector`。`between` 只遍历一段：

```text
entries_.lower_bound(from)  → 第一个 日期 >= from 的位置
entries_.upper_bound(to)    → 第一个 日期 >  to   的位置
从前者走到后者（不含后者），正好是 [from, to] 闭区间
```

#### 真实的 bug：为什么需要 `modified_`？

题目说“每个程序结束时写回文件”。最直接的做法是四个程序最后都无条件 `save()`。看起来没问题，直到你执行：

```bash
./pdshow 20221101 | ./pdadd 20221201
```

管道两边的程序是**同时运行**的：

```text
时间 →
pdshow: [读文件] [打印内容] [截断文件……写回文件] 结束
pdadd :    [读文件]                                [等输入……EOF] [写回文件]
               ↑
     如果 pdadd 恰好在 pdshow “截断了但还没写完”的那一刻读文件，
     它读到的是空的或残缺的日记，最后写回时把其他日记全部弄丢了！
```

这不是理论推演：在本文验证时，用 28 篇日记重复上面的管道 200 次，**无条件写回的版本有 59 次丢了数据**；加上 `modified_` 标记、只在内容改变时写回后，**0 次**。

只读的 `pdlist` 和 `pdshow` 现在根本不碰文件，问题就消失了。四个程序仍然统一在结尾调用 `save()`，符合题意；“要不要真的写”由 `Diary` 自己判断——这也是封装的好处：调用者不需要关心这个细节。

> `load()` 结尾为什么要 `modified_ = false`？因为 `load()` 内部调用了 `add()`，而 `add()` 会把标记设为 `true`。刚从文件读进来的东西和文件内容一样，不算“修改”。

<details>
<summary>提示阶梯：<code>defaultPath()</code></summary>

```cpp
#include <cstdlib>   // std::getenv

std::string Diary::defaultPath() {
    const char* env = std::getenv("PD_DATA");
    return env ? env : "diary.dat";
}
```

`std::getenv` 在环境变量不存在时返回 `nullptr`。

</details>

<details>
<summary>提示阶梯：遍历 map</summary>

```cpp
for (const auto& pair : entries_) {
    // pair.first  是 Date（key）
    // pair.second 是 Entry（value）
}
```

用迭代器写 `between`：

```cpp
for (auto it = entries_.lower_bound(from); it != entries_.upper_bound(to); ++it) {
    // it->second 是 Entry
}
```

</details>

**【讲给自己听】**

1. `find` 为什么返回指针而不是 `Entry`？为什么是 `const Entry*`？
2. 用自己的话解释管道导致丢数据的过程，以及 `modified_` 为什么能修好它。
3. `lower_bound` 和 `upper_bound` 的区别是什么？

---

### 第 4 步：四个 `main`

四个程序结构几乎一样，可以背成一个模板：

```text
1. 检查 argc            → 不对就往 cerr 打 Usage，返回失败
2. 解析日期参数          → 非法就报错，返回失败
3. Diary diary(Diary::defaultPath());  diary.load() 失败就返回失败
4. 做本程序的那一件事
5. diary.save()
6. 返回 0 或失败码
```

第 2 步在三个程序里都会出现（“解析并在失败时报错”）。按评分 3，把它抽成一个公共函数，放进 `cli.h` / `cli.cpp`：

```cpp
// cli.h
#ifndef CLI_H
#define CLI_H

#include "Date.h"

// Parses a command-line date argument; prints a message to stderr on failure.
bool parseDateArg(const char* arg, Date& out);

#endif
```

`cli.cpp` 里只有几行：调用 `Date::parse`，失败就 `std::cerr << "Invalid date '" << arg << "' (expected YYYYMMDD)\n";`。

#### 示范：`pdshow.cpp`（完整）

先看一个完整的，另外三个照着写。

```cpp
// pdshow <date>: print the content of the entry for <date> to stdout.
#include "Diary.h"
#include "cli.h"

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: pdshow <YYYYMMDD>\n";
        return 1;
    }
    Date date;
    if (!parseDateArg(argv[1], date)) return 1;

    Diary diary(Diary::defaultPath());
    if (!diary.load()) return 1;

    const Entry* entry = diary.find(date);
    if (!entry) {
        std::cerr << "No entry for " << date.toString() << '\n';
        return 1;
    }
    // Content only, no decoration, so the output can be piped into pdadd.
    entry->writeContent(std::cout);
    return diary.save() ? 0 : 1;
}
```

注意：输出里**只有日记内容**，所以 `pdshow A | pdadd B` 能把 A 日的日记原样复制到 B 日。

#### 练习：另外三个

**`pdadd <date>`**

- `argc` 必须是 2。
- 往 **`cerr`** 打一句提示，比如 `Enter content, end with a single '.' line or EOF:`。
- 构造 `Entry`，`readContent(std::cin)`，`diary.add(entry)`。“同日覆盖”已经由 `add` 保证了。
- 返回 `save()` 是否成功。

**`pdlist [<start> <end>]`**

- 合法的 `argc` 只有 1 和 3，其他都打 Usage。
- `argc == 1` 用 `all()`；`argc == 3` 解析两个日期，若 `end < start` 报错，否则用 `between()`。
- 输出格式你来定。推荐**一篇一行**：`日期<TAB>第一行内容`，例如 `20221101	First day of November.`。一篇一行对脚本最友好：`./pdlist | wc -l` 数篇数，`./pdlist | cut -f1` 只取日期，`./pdlist | grep hiking` 搜索。

**`pdremove <date>`**

- 和 `pdshow` 几乎一样，把 `find` 换成 `remove`。
- **所有失败路径都 `return -1;`**（参数错、日期错、加载失败、没有这篇、保存失败），成功 `return 0;`。

<details>
<summary>提示阶梯：<code>pdlist</code> 中的 <code>vector</code></summary>

```cpp
std::vector<const Entry*> entries;
if (argc == 1) {
    entries = diary.all();
} else {
    // 解析 from、to，检查顺序，然后
    entries = diary.between(from, to);
}
for (const Entry* e : entries) {
    std::cout << e->date().toString() << '\t' << e->firstLine() << '\n';
}
```

我们没有写 `operator>`，所以“`start` 在 `end` 之后”要写成 `to < from`。

</details>

**【讲给自己听】**

1. `pdadd` 的提示语为什么写到 `cerr`？如果写到 `cout`，`./pdadd 20221101 < note.txt > log.txt` 会怎样？
2. 为什么 `pdshow` 的输出不加 `===== 20221101 =====` 这样的装饰？

---

### 第 5 步：`Makefile`

每次手敲五六条 `g++` 太累了。`make` 会读 `Makefile`，**只重新编译改过的文件**。

```make
CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
COMMON   = Date.o Entry.o Diary.o cli.o
PROGRAMS = pdadd pdlist pdshow pdremove

all: $(PROGRAMS)

# Each program = its own main object + the shared objects.
$(PROGRAMS): %: %.o $(COMMON)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rebuild an object when its source or any header changes.
%.o: %.cpp *.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o $(PROGRAMS)

.PHONY: all clean
```

逐行看懂：

| 写法 | 意思 |
| --- | --- |
| `目标: 依赖` 下一行 **Tab** 开头的命令 | “要做出目标，先备齐依赖，再执行命令”。**必须是 Tab，不能是空格**，否则报 `missing separator` |
| `$(COMMON)` | 使用变量 |
| `$(PROGRAMS): %: %.o $(COMMON)` | 对四个程序中的每一个，比如 `pdadd`，依赖 `pdadd.o` 和公共 `.o` |
| `$@` | 当前目标，比如 `pdadd` |
| `$^` | 全部依赖 |
| `$<` | 第一个依赖，比如 `Date.cpp` |
| `.PHONY` | `all`、`clean` 不是真文件名 |

在 `code/` 目录下：

```bash
make
```

```bash
make clean
```

没有 `make` 的话，等价的一条命令：

```bash
for p in pdadd pdlist pdshow pdremove; do g++ -std=c++11 -Wall -Wextra $p.cpp Date.cpp Entry.cpp Diary.cpp cli.cpp -o $p; done
```

**`-Wall -Wextra` 下应该零警告。** 有警告就修掉，这直接影响“代码质量”评分。

---

### 第 6 步：脚本

#### 6.1 分发脚本 `pd.sh`（FAQ 明确要求）

FAQ 要求“一个用于交互的脚本，通过不同参数选择调用不同程序”，例如 `bash myscript.sh pdadd ...`。

**骨架：**

```bash
#!/usr/bin/env bash
# Usage: bash pd.sh {pdadd|pdlist|pdshow|pdremove} [args...]
# Runs the chosen program from the directory this script lives in.

DIR="$(cd "$(dirname "$0")" && pwd)"
prog="$1"

case "$prog" in
    pdadd|pdlist|pdshow|pdremove)
        shift                       # drop the program name, keep the rest
        exec "$DIR/$prog" "$@"      # TODO: 想想 exec 和 "$@" 各起什么作用
        ;;
    *)
        echo "Usage: bash pd.sh {pdadd|pdlist|pdshow|pdremove} [args...]" >&2
        exit 1
        ;;
esac
```

| 写法 | 意思 |
| --- | --- |
| `$0` | 脚本自己的路径；配合 `dirname` 找到脚本所在目录，这样从哪里运行都能找到程序 |
| `$1` | 第一个参数 |
| `shift` | 把参数整体左移一位，丢掉 `$1` |
| `"$@"` | 剩下的全部参数，**每个保持原样**（带引号很重要，参数里有空格也不会被拆开） |
| `exec` | 用目标程序**替换**脚本进程：程序的 stdin/stdout 和退出码原封不动传给调用者 |
| `>&2` | 把 `echo` 的输出送到 stderr |

**【讲给自己听】** 为什么 `bash pd.sh pdremove 19990101; echo $?` 能看到 `255`？（提示：`exec`。）

#### 6.2 测试脚本 `test.sh`（提交物要求“覆盖全部程序”）

**骨架**（前两个用例写好了，其余照着补）：

```bash
#!/usr/bin/env bash
# Use cases for all four programs. Run from anywhere: bash test.sh
cd "$(dirname "$0")"

# Use a throwaway data file so tests never touch your real diary.
export PD_DATA="$(pwd)/test_diary.dat"
rm -f "$PD_DATA"
PD="bash pd.sh"

echo "== 1. pdadd: content from a here-document, ended by '.'"
$PD pdadd 20221101 <<'END'
First day of November.
Learned argc/argv.
.
this line is after the dot and must be ignored
END

echo "== 2. pdadd: content from a pipe, ended by EOF (no '.')"
printf 'Second entry\nno dot here\n' | $PD pdadd 20221105

# TODO 3. 同一天再 pdadd 一次，验证“覆盖”
# TODO 4. pdlist 不带参数
# TODO 5. pdlist 带范围
# TODO 6. pdshow 存在的日期
# TODO 7. pdshow | pdadd 管道复制一篇
# TODO 8. pdremove 成功，echo "exit=$?" 应为 0
# TODO 9. 再删一次同一天，echo "exit=$?" 应为 255
# TODO 10. 非法日期 / 参数个数错误 / 起止颠倒
# TODO 11. 最后 cat "$PD_DATA" 看看文件长什么样

rm -f "$PD_DATA"
```

运行（先 `make`）：

```bash
bash test.sh
```

你会看到 `pdadd` 的提示语也打印在屏幕上，因为 stderr 没有被重定向。想要输出更干净，可以在调用后面加 `2>/dev/null`；但对“错误信息”用例要保留 stderr，才能看到报错。

> Windows 用户可以额外写一个 `pd.bat`，用 `if "%1"=="pdadd" ...` 分发。课程要求 shell **或** batch，有一个即可，在 README 里写清楚。

---

## 7. 测试清单

写完后逐条打勾。“期望”一列是**按本文设计**的结果；你的设计不同的话，在 README 里写清楚你的约定。

| # | 场景 | 命令示例 | 期望 |
| --- | --- | --- | --- |
| 1 | 交互输入，`.` 结束 | `./pdadd 20221101`，输入几行，最后一行输入 `.` | 保存成功，退出码 0 |
| 2 | 交互输入，EOF 结束 | 同上，最后在行首按 `Ctrl-D` | 同上 |
| 3 | 文件重定向输入 | `./pdadd 20221102 < note.txt` | 内容与文件一致 |
| 4 | `.` 之后的内容被忽略 | 见 `test.sh` 用例 1 | `pdshow` 不显示 `.` 后面的行 |
| 5 | 同日覆盖 | 对同一天 `pdadd` 两次 | 只剩第二次的内容 |
| 6 | 有序列出 | 乱序添加几天后 `./pdlist` | 按日期升序 |
| 7 | 范围（含端点） | `./pdlist 20221102 20221110` | 只列区间内，端点也列出 |
| 8 | 空范围 | 区间内没有日记 | 无输出，退出码 0 |
| 9 | 起止颠倒 | `./pdlist 20221201 20221101` | 报错到 stderr，非 0 |
| 10 | 参数个数错 | `./pdlist 20221101`、`./pdshow` | 打印 Usage，非 0 |
| 11 | 非法日期 | `./pdshow 20220230`、`./pdshow abc` | 报错，非 0 |
| 12 | 闰年 | `20240229` 合法，`20230229` 非法 | 如期 |
| 13 | 显示不存在的日记 | `./pdshow 19990101` | 报错，非 0 |
| 14 | 删除成功 / 失败 | `./pdremove` 存在 / 不存在的日期 | `$?` 为 0 / 255 |
| 15 | 输出重定向 | `./pdlist > list.txt` | 文件里没有提示语 |
| 16 | 管道协作 | `./pdshow 20221101 \| ./pdadd 20221201` | 两天内容相同，其他日记不丢 |
| 17 | 第一次运行 | 删掉数据文件后 `./pdlist` | 无输出，不报错 |
| 18 | 空内容 | `printf '.\n' \| ./pdadd 20221111` | 你决定：允许空日记还是拒绝；写进 README |
| 19 | 分发脚本 | `bash pd.sh foo` | 打印 Usage，非 0 |

---

## 8. 对照评分标准自检

| 评分项 | 自检问题 | 本文对应 |
| --- | --- | --- |
| 1 代码质量 | 有没有复制粘贴的代码块？有没有超过 40 行的函数？`-Wall -Wextra` 零警告？ | 第 4 步模板、`cli.h` |
| 2 注释质量 | 每个类、每个公有方法有没有一句说明“做什么、边界情况怎么处理”？注释是不是在解释**为什么**？ | 骨架里的注释示范 |
| 3 共享代码 | 日期解析、文件读写是不是只写了一份？ | `Date` / `Entry` / `Diary` / `cli` |
| 4 物理独立 | 是不是四个可执行文件？有没有任何 `system()` 或互相调用？ | 第 2、3.5 节 |
| 5 重定向 | stdout 里是否只有结果？`<`、`>`、`\|` 都试过吗？ | 3.2、`modified_` |
| 6 脚本 | 有分发脚本吗？测试脚本覆盖四个程序吗？退出码有意义吗？ | 第 6 步、3.4 |

**好注释 vs 坏注释：**

```cpp
// 坏：把代码翻译成英文
i++;  // increase i by 1

// 好：解释为什么
// Skip writing when nothing changed: a read-only program running in a pipe
// must not rewrite the file another program is reading.
if (!modified_) return true;
```

---

## 9. 整理提交

按课程统一规范（见仓库根目录 `AGENT.md`）：

```text
Assignment04_<学号>_<姓名拼音>/
├── README.md
├── code/        ← 全部源代码、Makefile、pd.sh、test.sh
└── report/
    └── Assignment04_<学号>_<姓名拼音>.pdf
```

**README 必须写：**

- 各文件夹和文件的作用（可以参考你 Assignment 03 的 README 的表格写法）。
- 环境：操作系统、编译器版本（`g++ --version`）、`make` 版本（`make --version`）。
- 怎么编译、怎么运行，四个程序的用法和参数格式（`YYYYMMDD`）。
- 你自己的设计约定：数据文件位置和 `PD_DATA`、文件格式、`pdlist` 输出格式、范围是否含端点、`-1` 在 shell 里显示为 `255`、空内容是否允许。
- 怎么运行 `test.sh`，以及应该看到什么。

**报告 PDF 必须有：** 运行环境、运行方式、实验结果（贴 `bash test.sh` 的真实输出截图）。**不要编造输出**，贴你自己机器上的真实结果。

**打包前：**

```bash
cd code && make clean && rm -f diary.dat test_diary.dat && cd ..
```

确认 `code/` 里没有 `.o`、可执行文件和测试产生的数据文件，再压缩整个文件夹。

---

## 10. 常见坑

| 症状 | 原因 | 解决 |
| --- | --- | --- |
| `pdshow > a.txt` 后文件里有 “Here is…” | 提示语写进了 `cout` | 提示语和错误全部改用 `cerr` |
| 按了 `Ctrl-D` 程序没结束 | 在行中间按的 | 先回车，在空行开头再按；或连按两次 |
| Windows 下 `Ctrl-Z` 没反应 | 没在行首，或没按回车 | 新起一行，`Ctrl-Z`，回车 |
| 输入了 `.` 却不结束 | 文件是 Windows 换行，行末有 `\r` | `readContent` 里去掉末尾 `\r` |
| `redefinition of 'class Date'` | 头文件没加 include guard | 加 `#ifndef/#define/#endif` |
| `undefined reference to ...` | 漏链接某个 `.o` 或没写定义 | 检查 `Makefile` 的 `COMMON` |
| `Makefile: missing separator` | 命令行用了空格缩进 | 改成 Tab |
| `entries_[d] = e` 编译报错 | `Entry` 没有默认构造函数 | `erase` + `insert`，或 C++17 `insert_or_assign` |
| 在别的目录运行找不到之前的日记 | `diary.dat` 是相对路径，相对“当前目录” | 用 `PD_DATA` 指定绝对路径；在 README 说明 |
| 管道用完后有日记丢了 | 只读程序也在写回文件，和管道另一端竞争 | `modified_` 标记，见第 3 步 |
| `pdremove` 返回 -1，`$?` 却是 255 | 退出码只保留低 8 位 | 正常现象，在 README 写明 |
| `gcc`/`gdb` 找不到文件 | 路径里有中文 | 把项目放到纯英文路径 |
| 头文件里写了 `using namespace std;` | 会污染所有包含它的文件 | 头文件里写全名 `std::string` |

---

## 11. 费曼终极检验：讲给室友听

找一个人（或者对着橡皮鸭），**不看文档**回答下面的问题。哪题卡住了，就回到对应小节。

| # | 问题 | 回看 |
| --- | --- | --- |
| 1 | 这四个程序各干什么？它们怎么“交流”？ | 1、2 |
| 2 | `./pdlist 20221101 20221130` 时 `argc`、`argv[2]` 是什么？ | 3.1 |
| 3 | 为什么提示语要写到 `cerr`？举一个写错会出问题的例子。 | 3.2 |
| 4 | EOF 是什么？`while (getline(...))` 为什么能在 EOF 时停下？ | 3.3 |
| 5 | 为什么 `return -1` 在 shell 里变成 255？ | 3.4 |
| 6 | 四个程序共用 `Diary.cpp`，它被编译了几次？链接了几次？ | 3.5 |
| 7 | 为什么有 `Date`、`Entry`、`Diary` 三个类？各负责什么？ | 4.1 |
| 8 | 为什么选 `std::map`？它免费给了你哪三个功能？ | 4.3 |
| 9 | 为什么用单独一行 `.` 当文件分隔符是安全的？ | 5 |
| 10 | 管道为什么会导致丢数据？`modified_` 怎么修好它？ | 第 3 步 |
| 11 | 分发脚本里的 `exec` 和 `"$@"` 起什么作用？ | 第 6 步 |

全部能用自己的话讲清楚，这个作业你就真正掌握了。

---

## 12. 进阶（可选）

做完基础版、还有余力时可以思考。加不加都要在 README 里如实说明。

1. **RAII 自动保存**：让 `Diary` 的析构函数自动调用 `save()`，`main` 里就不用记得写。思考：析构函数里保存失败了怎么报告？（析构函数不能返回值，也不应该抛异常。）
2. **原子写入**：`save()` 先写到 `diary.dat.tmp`，成功后再 `std::rename` 成 `diary.dat`。这样即使写到一半断电，原文件也不会损坏，也能进一步避免并发读到半截文件。
3. **只在交互时提示**：用 POSIX 的 `isatty(fileno(stdin))` 判断输入是不是来自键盘，是才打印提示。代价是需要 `<unistd.h>`，Windows 不可移植。
4. **`std::optional<Date>`（C++17）**：`static std::optional<Date> parse(const std::string&)`，比“`bool` + 引用参数”更现代。
5. **`pdlist` 的“单边”范围**：只给 `start` 时列出之后的全部？注意这是对题目的扩展，不要改变题目要求的行为。

---

写完任何一步想让我帮你看代码、解释报错或检查设计，随时把代码贴给我。需要完整参考答案的话也可以直接说。
