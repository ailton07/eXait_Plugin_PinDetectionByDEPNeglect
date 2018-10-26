// PinDetectionByDEPNeglect.cpp : Defines the entry point for the console application.
//
// Basta procurar por call [0x0130573C] no debug
#include <stdio.h>
#include <Windows.h>

#define ASSEMBLY_SIZE 4
const unsigned char assembly [ASSEMBLY_SIZE] = {0x90 , 0x90 , 0x90 , 0xC3 } ; // NOP, NOP, NOP, RET

static bool pinDetected = 0;

// ---------- start eXait header 
#define DllExport extern "C" __declspec(dllexport)
DllExport char* GetPluginName(void);
DllExport char* GetPluginDescription(void);
DllExport int DoMyJob(void);

char* GetPluginName(void)
{
	static char PluginName[] = "PinDetectionByDEPNeglect";
	return PluginName;
}

char* GetPluginDescription(void)
{
	static char MyDescription[] = "This plugin exploit a failure in page permissions treatment";
	return MyDescription;
}
// ---------- end of eXait header modifications


int main(int argc, char** argv) {
	printf ("Address of assembly variable: 0x%x\n", assembly);
	// Tentativa 2
	LPVOID virtualAddress;
	//virtualAddress = VirtualAlloc(NULL, ASSEMBLY_SIZE,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
	virtualAddress = VirtualAlloc(NULL, ASSEMBLY_SIZE,MEM_COMMIT,PAGE_READWRITE);
	if (virtualAddress != NULL)
	{
		CopyMemory(virtualAddress, assembly, ASSEMBLY_SIZE);
		
		__try {
			__asm{
				call virtualAddress
			}
			pinDetected = 1;
		}
		__except(EXCEPTION_EXECUTE_HANDLER){
			pinDetected = 0;
		}
	}
	printf("pinDetected = %d", pinDetected);
	getchar();
	return 0;
}

int DoMyJob(void)
{
	printf ("Address of assembly variable: 0x%x\n", assembly);
	// Tentativa 2
	LPVOID virtualAddress;
	//virtualAddress = VirtualAlloc(NULL, ASSEMBLY_SIZE,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
	virtualAddress = VirtualAlloc(NULL, ASSEMBLY_SIZE,MEM_COMMIT,PAGE_READWRITE);
	if (virtualAddress != NULL)
	{
		CopyMemory(virtualAddress, assembly, ASSEMBLY_SIZE);
		
		__try {
			__asm{
				call virtualAddress
			}
			pinDetected = 1;
		}
		__except(EXCEPTION_EXECUTE_HANDLER){
			pinDetected = 0;
		}
	}
	return pinDetected;
}