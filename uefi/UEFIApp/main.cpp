#include <Uefi.h>
#include <LoadedImage.h>
#include <EfiShell.h>
#include <EfiShellInterface.h>
#include <EfiShellParameters.h>

EFI_GUID ShellInterfaceProtocolConst = SHELL_INTERFACE_PROTOCOL_GUID;
EFI_GUID ShellParametersProtocolConst = EFI_SHELL_PARAMETERS_PROTOCOL_GUID;

void UlToStr(CHAR16 *s, unsigned long bin, unsigned char n)
{
    s += n;
    *s = '\0';

    while (n--)
    {
        *--s = (bin % 10) + '0';
        bin /= 10;
    }
}

void CharToStr(CHAR16 *s, char *c)
{
	int i = 0;
    while (c[i] != '\0')
    {
        *(s+i) = c[i];
		i++;
		*(s+i) = '\0';
    }
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_SHELL_INTERFACE *ShellInterface;
	EFI_SHELL_PARAMETERS_PROTOCOL *ShellParameters;
	CHAR16 s[128];
	CHAR16 n[] = { '\n', '\r' };
/*
    if (EFI_SUCCESS == (*SystemTable->BootServices->HandleProtocol)(ImageHandle, (EFI_GUID *)&ShellInterfaceProtocolConst, (void **)&ShellInterface))
    {
		UlToStr( s, ShellInterface->Argc, 4 );
		SystemTable->ConOut->OutputString(SystemTable->ConOut, s );
		SystemTable->ConOut->OutputString(SystemTable->ConOut, n );
	}
	else
*/
	if (EFI_SUCCESS == (*SystemTable->BootServices->HandleProtocol)(ImageHandle, (EFI_GUID *)&ShellParametersProtocolConst, (void **)&ShellParameters))
	{
		UlToStr( s, ShellParameters->Argc, 4 );
		SystemTable->ConOut->OutputString(SystemTable->ConOut, s );
		SystemTable->ConOut->OutputString(SystemTable->ConOut, n );
	}
	else
	{
		char *msg = "Load shell interface and parameter protocol fail";
		CharToStr( s, msg );
		SystemTable->ConOut->OutputString(SystemTable->ConOut, s );
		SystemTable->ConOut->OutputString(SystemTable->ConOut, n );
	}



  return EFI_SUCCESS;
}