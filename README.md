# Sudoku
2018下半学年软件工程个人项目——数独终局生成及残局求解
博客地址：https://blog.csdn.net/qq_40036347/article/details/85180825

该代码库中有4个文件夹和一个main.cpp文件

bin文件夹中包含一个可执行程序sudoku.exe，可双击运行或打开Powershell输入命令，需要注意的是，输入的命令为 "-c" + " " + 十进制参数 或者 "-s" + " " + 文件相对路径 的形式，具体请参考上述博客中的“指令校验模块”内容

sudoku文件夹为该数独工程项目的项目文件，内含多个函数模块的头文件和.cpp文件

test_DFS和test_instruction两个文件夹为单元测试项目文件夹，可供sudoku项目的指令校验模块和DFS回溯搜索模块进行单元测试

main.cpp文件为sudoku文件夹中，所有函数模块放到一个.cpp文件里的形式，可直接在VS上编译运行
