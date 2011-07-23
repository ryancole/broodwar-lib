#include "PatchClass.h"

DWORD PatchClass::PatchAddress(int type, DWORD AddressToPatch, DWORD AddressToUse, DWORD PadSize) {
    PadSize = PadSize == NULL ? 0 : PadSize;
	BYTE  CallOperand;

	switch(type) {
		case 1:
			CallOperand = 0xE9;
			break;

		case 2:
			CallOperand = 0xE8;
			break;

		default:
			CallOperand = 0xE9;
			break;
	}
    DWORD DataBuffer   = (AddressToUse - (AddressToPatch + 5));
    DWORD OldProtect   = 0;

    VirtualProtect((LPVOID)AddressToPatch, 5 + PadSize, PAGE_EXECUTE_READWRITE, &OldProtect);
    *(BYTE*)AddressToPatch = CallOperand;
    *(DWORD*)(AddressToPatch + 1) = DataBuffer;

    for (DWORD x = PadSize; x > 0; x--) {
        *(BYTE*)(AddressToPatch+5+x) = 0x90;
    }
    VirtualProtect((LPVOID)AddressToPatch, 5 + PadSize, OldProtect, &OldProtect);

    return 1;
}

DWORD PatchClass::NopAddress(DWORD AddressToPatch, DWORD Length) {
	Length = Length == NULL ? 0 : Length;
	BYTE CallOperand = 0x90;
	DWORD OldProtect = 0;

	VirtualProtect((LPVOID)AddressToPatch, Length + 1, PAGE_EXECUTE_READWRITE, &OldProtect);
	memset((void*)AddressToPatch, CallOperand, Length);
	VirtualProtect((LPVOID)AddressToPatch, Length + 1, OldProtect, &OldProtect);
	return 1;
}