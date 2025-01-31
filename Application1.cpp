#include "Overlay/Overlay.hpp"
#include "Thread/Thread.hpp"


HANDLE iqvw64e_device_handle;
inline std::string APPC = _("xx{XX+XX");

inline std::string GameTitle;
inline std::string MapDriver;

int main()
{
    SetConsoleTitle(_("Kernel Debugger"));
    kInterface = new Interface("NtGdiMakeInfoDC");

    if (!kInterface->ConnectToDriver())
    {
        LOG(_("Failed To Call Driver\n"));
        Sleep(2000);
        return EXIT_FAILURE;
    }
    localPid = PID("r5apex.exe");
    std::cout << "PID : " << localPid << "\n";
    if (!localPid)
        exit(0);
    sdk.R5Apex = kInterface->BaseAddress(localPid, "r5apex.exe");
    if (!sdk.R5Apex)
        exit(0);

    std::cout << sdk.R5Apex << "\n";
    Sleep(2500);
    system(_("cls"));
  
        system("cls");
        LOG(_("Starting Cheat\n"));
        LOG(_("Close Cheat [EXIT BUTTON]\n"));

        std::thread(&EntityCacha::EntityThread, entCacha).detach();

        std::thread(&Misc::DoMisc, misc).detach();

        std::thread(&LootCacha::LootThread, lootCacha).detach();

        BeginCheat();

}
