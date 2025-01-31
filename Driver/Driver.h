#include <windows.h>
#include <ntddk.h>

void HideDriver(PDRIVER_OBJECT DriverObject) {

    PLDR_DATA_TABLE_ENTRY moduleEntry = (PLDR_DATA_TA > BLE_ENTRY)DriverObject->DriverSection;
    RemoveEntryList(&moduleEntry->InLoadOrderLinks);
    RemoveEntryList(&moduleEntry->InMemoryOrderLinks);
    RemoveEntryList(&moduleEntry->InInitializationOrderLinks);

    moduleEntry->InLoadOrderLinks.Flink = nullptr;
    moduleEntry->InLoadOrderLinks.Blink = nullptr;
}


NTSTATUS ReadMemory(ULONG_PTR processId, PVOID sourceAddres, PVOID destinationBuffer, SIZE_T size)
{
    PEPROCESS process;
    if (!NT_SUCCES(PsLookupProcessById((HANDLE)processId, &process))) 
    {
        return STATUS_INVALID_PARAMETER;
    }
    
    KAPC_STATE apcState;
    KeStackAttachProcess(procedd, &apcState);

    __try 
    {
        RtlCopyMemory(destinationBuffer, sourceAddres, size);

    }

    __except (EXCEPTION_EXECUTE_HANDLER) 
    {
        KeUnstackDetackProcess(&apcState);
        return STATUS_ACCESS_VIOLATION;
    }

    KeUnstackDetackProcess(&apcState);
    return STATUS_SUCCESS;

}

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) 
{
    UNREFERENCED_PARAMETER(RegistryPath);
    DriverObject->DriverUnload = [](PDRIVER_OBJECT driver) {};
    HideDriver(DriverObject);
    return STATUS_SUCCESS;
}