#include <iostream>
#include <windows.h> 
#include <WinUser.h> 
typedef DWORD(__cdecl* decompiler_general)(int idk1, int idk2); //this is the function that calls decompiler
typedef int (__thiscall* decompiler_main)(DWORD Bytecode, int idkwhathtisintegeris); //this is actual decomp func
// this function may be wrong^
void HandleKrnlException(int Exception) {
    if (Exception == 0) //Dll Load Failure 
    {
        std::cout << "krnl error - attempt to call a 32 bit dll with 64bit pe";
        MessageBox(NULL, L"Krnl Hard Error 1", L"Krnl", 0);
        throw std::runtime_error("krnl error 1");
    }
    else if(Exception == 1) {
        std::cout << "cannot find krnl";
        MessageBox(NULL, L"Krnl Hard Error 2", L"Krnl", 0);
        throw std::runtime_error("krnl error 2");
    }
    else
    {
        throw std::runtime_error("unknown krnl exception");
        MessageBox(NULL, L"Krnl Unknown Error", L"Krnl", 0);

    }
    exit(0);

}
int main()
{
    system("title Krnl Decompiler [ST4] \n");
    system("color 2");
        auto KrnlDll = (TEXT("krnl.dll"));
        HINSTANCE Krnl = LoadLibrary(KrnlDll);


    if (Krnl == 0){
        HandleKrnlException(0);
    }

    std::cout << "Krnl Loaded!\n";
    std::cout << "!calling decompiler!\n";
    std::cout << "...if no text is below, an invalid adress was used...";
    INT DecompilerGeneral = 0x67B74D40;
    INT DecompilerMainAddy = 0x67B74FB0;
    //Todo: Rebase the above?
    decompiler_main newkrnldecomp = (decompiler_main)DecompilerMainAddy;
    try {
        int BytecodeHex = 0603010101010101;
        DWORD Bytecode = BytecodeHex;
        auto DecompileResult = newkrnldecomp(Bytecode, 5); //perhaps 2nd arg is version?
        std::cout << "Decomp success!\n";
        std::cout << "Output-->\n";
        std::cout << DecompileResult;
    }
    catch (std::exception e)
    {
        std::cout << "fatal error in krnl decompiler function" << e.what() << std::endl;
        HandleKrnlException(10);
    }
    std::cout << "end of main, return = 1";
    system("pause");
    return 1;
}
