#include <iostream>
#include <cstdlib> // For system()
#include <string>

// 注意：以下代码主要演示 system() 函数的用法。
// 对于更健壮和灵活的进程创建，应使用特定于操作系统的API。

int main(int argc, char *argv[]) {
    std::cout << "主进程开始。" << std::endl;

    // 示例 1: 使用 system() 执行一个简单的命令 (例如：列出当前目录文件)
    std::cout << "\n示例 1: 使用 system() 执行命令..." << std::endl;
#ifdef _WIN32
    int result_dir = system("dir"); // Windows命令
#else
    int result_dir = system("ls -l"); // POSIX命令
#endif

    if (result_dir == 0) {
        std::cout << "system(\"dir/ls\") 执行成功。" << std::endl;
    } else {
        std::cerr << "system(\"dir/ls\") 执行失败，返回代码: " << result_dir << std::endl;
    }

    // 示例 2: 使用 system() 启动另一个可执行文件 (如果存在)
    // 假设在同一目录下有一个名为 'another_program.exe' (Windows) 或 'another_program' (Linux) 的程序
    std::cout << "\n示例 2: 尝试使用 system() 启动另一个程序..." << std::endl;
    // int result_program = system(".\\another_program.exe"); // Windows
    // int result_program = system("./another_program");    // Linux/macOS
    // 由于我们不能保证 'another_program' 存在，这里仅作演示说明，实际执行可能会失败。
    // 您可以自行编译一个简单的程序并替换路径来测试。
    std::cout << "(此示例需要一个名为 'another_program' 的可执行文件在当前目录才能成功运行)" << std::endl;

    // 提示：关于特定于操作系统的API
    std::cout << "\n--- 关于特定于操作系统的进程创建 API --- " << std::endl;
    std::cout << "对于更高级的进程控制 (例如，重定向输入/输出，获取进程ID，更精细的错误处理等)，" << std::endl;
    std::cout << "应使用特定于操作系统的API:" << std::endl;
    std::cout << "  - Windows: CreateProcess() 系列函数 (需要 #include <windows.h>)" << std::endl;
    std::cout << "  - POSIX (Linux, macOS): fork() 和 exec() 系列函数 (需要 #include <unistd.h> 和 #include <sys/wait.h>)" << std::endl;
    std::cout << "这些API提供了更大的灵活性，但使用起来也更复杂。" << std::endl;

    // 示例：如何通过命令行参数启动本程序自身的一个新实例 (简易演示)
    if (argc < 2) { // 如果没有命令行参数，说明是第一次运行
        std::cout << "\n尝试以新进程方式重新运行本程序并传递参数..." << std::endl;
        std::string command = argv[0]; // 获取当前程序路径
        command += " child_process";   // 添加参数
#ifdef _WIN32
        // Windows系统下，如果路径包含空格，需要用引号括起来
        if (command.find(' ') != std::string::npos) {
            command = "\"" + command + "\"";
        }
#endif
        system(command.c_str());
    } else {
        std::cout << "\n这是一个由 system() 启动的新进程实例。" << std::endl;
        std::cout << "接收到的参数: " << argv[1] << std::endl;
    }

    std::cout << "\n主进程结束。" << std::endl;
    return 0;
}

/*
编译和运行指南 (例如使用 g++):
1. 保存文件为 process_creation_demo.cpp
2. 打开终端或命令行
3. 编译: g++ process_creation_demo.cpp -o process_demo -std=c++11
4. 运行: ./process_demo (在 Linux/macOS) 或 process_demo.exe (在 Windows)

注意:
- system() 函数的行为高度依赖于操作系统和shell环境。
- 它会启动一个新的shell来执行命令，这可能带来安全风险（例如，如果命令字符串来自不受信任的输入）。
- system() 的错误处理能力有限，通常只返回命令的退出状态。
- 对于复杂的应用，强烈建议使用 CreateProcess (Windows) 或 fork/exec (POSIX)。
*/