#include <cstring>
#include <iostream>

#if defined(_WIN32)
#include <windows.h>
#endif

#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)
#include <cpuid.h>
#endif

void cpuid(int func, int subfunc, unsigned int regs[4]) {
#if defined(_MSC_VER)
    __cpuidex(reinterpret_cast<int *>(regs), func, subfunc);
#else
    __cpuid_count(func, subfunc, regs[0], regs[1], regs[2], regs[3]);
#endif
}

std::string get_cpu_vendor() {
    unsigned int regs[4]{};
    cpuid(0, 0, regs);
    char vendor[13]{};
    std::memcpy(&vendor[0], &regs[1], 4); // EBX
    std::memcpy(&vendor[4], &regs[3], 4); // EDX
    std::memcpy(&vendor[8], &regs[2], 4); // ECX
    return vendor;
}

std::string get_cpu_brand() {
    unsigned int regs[4]{};
    char brand[49]{};
    for (int i = 0; i < 3; ++i) {
        cpuid(0x80000002 + i, 0, regs);
        std::memcpy(brand + i * 16, regs, 16);
    }
    return brand;
}

int main() {
    std::cout << "CPU Vendor: " << get_cpu_vendor() << std::endl;

    std::string brand = get_cpu_brand();
    if (!brand.empty() && brand.find_first_not_of(' ') != std::string::npos) {
        std::cout << "CPU Model: " << brand << std::endl;
    } else {
        std::cout << "CPU Brand String: [Not available]" << std::endl;
    }

#if defined(_WIN32)
    SYSTEM_INFO sysinfo{};
    GetNativeSystemInfo(&sysinfo);
    std::cout << "Number of processors: " << sysinfo.dwNumberOfProcessors << std::endl;
    std::cout << "Processor architecture: ";
    switch (sysinfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            std::cout << "x64 (AMD or Intel)" << std::endl;
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            std::cout << "ARM" << std::endl;
            break;
        case PROCESSOR_ARCHITECTURE_ARM64:
            std::cout << "ARM64" << std::endl;
            break;
        case PROCESSOR_ARCHITECTURE_IA64:
            std::cout << "Intel Itanium-based" << std::endl;
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            std::cout << "x86" << std::endl;
            break;
        default:
            std::cout << "Unknown" << std::endl;
            break;
    }
#endif

    return 0;
}
