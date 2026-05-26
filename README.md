# Land War
[English](#english) | [简体中文](#简体中文)

---

<h2 id="english">English</h2>

Land War is a 2D action-strategy game developed in C++ using the Qt framework. In this game, players take on the role of a commander managing a highly customizable floating island. The core objective is to survive and dominate aerial battlefields by strategically managing resources, expanding the island's structure with various blocks, and equipping weapons to fend off continuous enemy attacks.

### Gameplay Mechanics

#### Floating Island Management
The core of Land War revolves around the floating island system. The island serves as a dynamic, moving fortress composed of interconnected block grids. Players must constantly monitor and balance the island's flight energy. Keeping the island airborne requires careful management of energy consumption and regeneration. If the energy reserves run out, gravity takes over and the island begins to descend, putting the entire structure at risk. 

The structural integrity of the island depends entirely on the specific blocks chosen for construction. Players can expand and upgrade their base using an intuitive grid system, customizing its shape and utility to fit different tactical needs. Every expansion choice affects the island's overall survivability.

#### Combat and Arsenal
Combat in Land War is fast-paced and challenging. The game dynamically scales the difficulty as players face continuous waves of enemies. To defend the territory, players can equip up to five distinct weapons in designated strategic slots on the island. 

Each weapon features its own independent cooldown mechanism, firing rate, and tactical advantage. The combat engine provides an action-oriented environment where players must continuously maneuver the island, aim precisely, and manage attacks, all while ensuring the fortress remains structurally sound and safely airborne.

### Key Features
- **Resource Management:** Balance flight energy and gravitational pull to keep the fortress floating during combat.
- **Modular Building:** Expand the island using a grid-based block system to customize the base layout.
- **Dynamic Combat:** Equip multiple weapons, manage attack cooldowns, and fight against progressively difficult enemies.
- **Settings Interface:** A straightforward UI that allows players to adjust game parameters and visual preferences.
- **Multi-language Support:** Built-in internationalization (i18n) with full localization for English and Simplified Chinese, dynamically loaded based on the system locale.

### Technical Details
- **Language:** C++11 or higher
- **Framework:** Qt (Widgets, QtGui, QtCore) for rendering and event handling.
- **Architecture:** Object-Oriented Design utilizing custom Sprite classes for entity rendering and 2D physics, alongside dedicated manager classes for game state orchestration.

### Build Instructions
1. Ensure Qt Creator and the corresponding Qt development libraries are installed.
2. Clone the repository to a local directory.
3. Open the `Land_War.pro` project file in Qt Creator.
4. Configure the build environment for your preferred desktop kit (e.g., MinGW, MSVC).
5. Build the project. Game resources such as images and language files are automatically compiled via `images.qrc`.
6. Run the executable to start the game.

---

<h2 id="简体中文">简体中文</h2>

Land War 是一款使用 C++ 和 Qt 框架开发的 2D 动作策略游戏。玩家在游戏中扮演指挥官，管理一座高度可定制的浮空岛。游戏的核心目标是通过战略性地管理资源、使用各类方块扩展岛屿结构，并装备武器来抵御敌人的不断攻击，从而在空战中生存并取得优势。

### 玩法机制

#### 浮空岛管理
游戏的核心围绕浮空岛系统展开。岛屿是一个由方块网格拼接而成的动态移动堡垒。玩家必须时刻监控并平衡岛屿的飞行能量。维持岛屿升空需要仔细管理能量的消耗与恢复；一旦能量耗尽，岛屿就会在重力作用下坠落，使整个结构面临解体的风险。

岛屿的结构完整性完全取决于建造时所选用的方块。玩家可以使用直观的网格系统来扩展和升级基地，根据战术需求自定义其形状和功能。每一次扩建都会直接影响岛屿的长期生存能力。

#### 战斗与武器系统
游戏中的战斗节奏紧凑且充满挑战。随着玩家面临一波又一波的敌人，系统会动态调整战斗难度。为了保卫领地，玩家可以在岛屿的指定槽位上装备最多五种不同的武器。

每种武器都有独立的冷却机制、射速和战术优势。战斗系统要求玩家在操作岛屿移动、精准瞄准和释放攻击的同时，还要兼顾堡垒的结构安全和飞行状态。

### 核心特性
- **资源管理：** 在激烈的战斗中平衡飞行能量与重力，保持堡垒悬空。
- **模块化建造：** 使用网格化的方块系统扩展岛屿，自由定制基地布局。
- **动态战斗：** 装备多种武器，管理攻击冷却时间，对抗难度不断提升的敌人。
- **设置界面：** 简洁的 UI 界面，允许玩家调整游戏参数和视觉偏好。
- **多语言支持：** 内置国际化 (i18n) 支持，提供完整的英语和简体中文本地化，并根据系统语言环境自动加载。

### 技术细节
- **开发语言：** C++11 及以上
- **核心框架：** Qt (Qt Widgets, QtGui, QtCore)，用于渲染和事件处理。
- **软件架构：** 采用面向对象设计，使用自定义的 Sprite 类进行实体渲染和 2D 物理计算，并通过专门的 Manager 类来调度游戏状态。

### 编译与运行
1. 确保已安装 Qt Creator 及相应的 Qt 开发库。
2. 将项目克隆到本地目录。
3. 在 Qt Creator 中打开 `Land_War.pro` 项目文件。
4. 为当前环境配置合适的构建套件（如 MinGW、MSVC）。
5. 编译项目。图片、语言包等游戏资源会通过 `images.qrc` 自动编译打包。
6. 运行可执行文件即可启动游戏。
