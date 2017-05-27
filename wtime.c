
/**
 * Copyright (c) 2017 Tino Reichardt
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 * You can contact the author at:
 * - wtime source repository: https://github.com/mcmilk/wtime
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <processthreadsapi.h>	/* GetProcessTimes() */
#include <psapi.h>		/* GetProcessMemoryInfo() */

static void panic(char *errmsg)
{
	fprintf(stderr, "%s\n", errmsg);
	exit(1);
}

static void usage(void)
{
	printf("\n"
	       "\n wtime version 1.0a"
	       "\n Copyright (c) 2017 Tino Reichardt"
	       "\n"
	       "\n"
	       "\n Usage: wtime COMMAND [OPTIONS]"
	       "\n"
	       "\n The program will start COMMAND with the given OPTIONS"
	       "\n and print out some statistic of it to stderr."
	       "\n"
	       "\n There are no options for this command."
	       "\n"
	       "\n Report bugs to: https://github.com/mcmilk/wtime/issues"
	       "\n");

	exit(0);
}

int main(int argc, char *argv[])
{
	STARTUPINFO si = { };	/* init si to zero */
	PROCESS_INFORMATION pi = { };
	FILETIME createTime, exitTime, kernelTime, userTime;
	ULONGLONG Create64, Exit64, Kernel64, User64;
	PROCESS_MEMORY_COUNTERS memCounters;
	IO_COUNTERS ioCounters;
	char *cmdline;
	int ret, alen, i;

	/* even this can be difficult, print the usage ;) */
	if (argc < 2)
		usage();

	/* build up our command line for the new process */
	for (i = 1, alen = 0; i < argc; i++)
		alen += strlen(argv[i]) + 1;
	cmdline = malloc(alen + 1);
	if (!cmdline)
		panic("Out of memory!\n");

	cmdline[0] = 0;
	for (i = 1; i < argc; i++) {
		if (i != 1)
			strcat(cmdline, " ");
		strcat(cmdline, argv[i]);
	}

	/* open process... */
	si.cb = sizeof(si);
	if (!CreateProcess
	    (NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		fprintf(stderr, "CreateProcess() failed, Error: %d.\n",
			GetLastError());
		exit(1);
	}

	/* ... wait for finish */
	WaitForSingleObject(pi.hProcess, INFINITE);

	ret =
	    GetProcessTimes(pi.hProcess, &createTime, &exitTime,
			    &kernelTime, &userTime);
	if (ret == 0)
		panic("GetProcessTimes() failed.");

	ret =
	    GetProcessMemoryInfo(pi.hProcess, &memCounters,
				 sizeof(memCounters));
	if (ret == 0)
		panic("GetProcessMemoryInfo() failed.");

	ret = GetProcessIoCounters(pi.hProcess, &ioCounters);
	if (ret == 0)
		panic("GetProcessIoCounters() failed.");

	/* let the process close the last handle, now */
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	/**
	 * print summary about the infos
	 */
	fprintf(stderr, "Command: %s\n", cmdline);

	/**
	 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms683223(v=vs.85).aspx
	 *
	 * typedef struct _FILETIME {
	 *  DWORD dwLowDateTime;
	 *  DWORD dwHighDateTime;
	 * } FILETIME;
	 */

	/* get the u64 values */
	Create64 =
	    ((ULONGLONG) createTime.dwHighDateTime << 32) +
	    createTime.dwLowDateTime;
	Exit64 =
	    ((ULONGLONG) exitTime.dwHighDateTime << 32) +
	    exitTime.dwLowDateTime;
	Kernel64 =
	    ((ULONGLONG) kernelTime.dwHighDateTime << 32) +
	    kernelTime.dwLowDateTime;
	User64 =
	    ((ULONGLONG) userTime.dwHighDateTime << 32) +
	    userTime.dwLowDateTime;
	Exit64 -= Create64;

	#define _MILLISECOND (10000)
	fprintf(stderr,
		"\nTIMES in milliseconds"
		"\nRunningTime................. %llu"
		"\nUserTime.................... %llu"
		"\nKernelTime.................. %llu"
		"\n",
		Exit64 / _MILLISECOND,
		User64 / _MILLISECOND,
		Kernel64 / _MILLISECOND);

	/**
	 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms683219(v=vs.85).aspx
	 *
	 * typedef struct _PROCESS_MEMORY_COUNTERS {
	 *   DWORD  cb;
	 *   DWORD  PageFaultCount;
	 *   SIZE_T PeakWorkingSetSize;
	 *   SIZE_T WorkingSetSize;
	 *   SIZE_T QuotaPeakPagedPoolUsage;
	 *   SIZE_T QuotaPagedPoolUsage;
	 *   SIZE_T QuotaPeakNonPagedPoolUsage;
	 *   SIZE_T QuotaNonPagedPoolUsage;
	 *   SIZE_T PagefileUsage;
	 *   SIZE_T PeakPagefileUsage;
	 * } PROCESS_MEMORY_COUNTERS;
	 */

	#define _KB (1024)
	fprintf(stderr,
		"\nMEMORY in KiB"
		"\nPageFaultCount.............. %llu"
		"\nPeakWorkingSetSize.......... %llu"
		"\nWorkingSetSize.............. %llu"
		"\nQuotaPeakPagedPoolUsage..... %llu"
		"\nQuotaPagedPoolUsage......... %llu"
		"\nQuotaPeakNonPagedPoolUsage.. %llu"
		"\nQuotaNonPagedPoolUsage...... %llu"
		"\nPagefileUsage............... %llu"
		"\nPeakPagefileUsage........... %llu"
		"\n",
		(ULONGLONG)memCounters.PageFaultCount / _KB,
		(ULONGLONG)memCounters.PeakWorkingSetSize / _KB,
		(ULONGLONG)memCounters.WorkingSetSize / _KB,
		(ULONGLONG)memCounters.QuotaPeakPagedPoolUsage / _KB,
		(ULONGLONG)memCounters.QuotaPagedPoolUsage / _KB,
		(ULONGLONG)memCounters.QuotaPeakNonPagedPoolUsage / _KB,
		(ULONGLONG)memCounters.QuotaNonPagedPoolUsage / _KB,
		(ULONGLONG)memCounters.PagefileUsage / _KB,
		(ULONGLONG)memCounters.PeakPagefileUsage / _KB);

	/**
	 * https://msdn.microsoft.com/de-de/library/windows/desktop/ms683218(v=vs.85).aspx
	 *
	 * typedef struct _IO_COUNTERS {
	 *   ULONGLONG ReadOperationCount;
	 *   ULONGLONG WriteOperationCount;
	 *   ULONGLONG OtherOperationCount;
	 *   ULONGLONG ReadTransferCount;
	 *   ULONGLONG WriteTransferCount;
	 *   ULONGLONG OtherTransferCount;
	 * } IO_COUNTERS;
	 */

	fprintf(stderr,
		"\nIO count"
		"\nReadOperationCount.......... %llu"
		"\nWriteOperationCount......... %llu"
		"\nOtherOperationCount......... %llu"
		"\nReadTransferCount........... %llu"
		"\nWriteTransferCount.......... %llu"
		"\nOtherTransferCount.......... %llu"
		"\n",
		ioCounters.ReadOperationCount,
		ioCounters.WriteOperationCount,
		ioCounters.OtherOperationCount,
		ioCounters.ReadTransferCount,
		ioCounters.WriteTransferCount,
		ioCounters.OtherTransferCount);

	/* free resources and exit */
	free(cmdline);
	exit(0);
}
