
## Information given by the help option

```
 Usage: wtime COMMAND [OPTIONS]

 Copyright (c) 2017 Tino Reichardt


 The program will start COMMAND with the given OPTIONS
 and print out some statistic of it to stderr.

 There are no options for this command.

 Report bugs to: https://github.com/mcmilk/wtime/issues
```

## Sample Outputs

For one thread:
```
Command: 7z a silesia.7z -mmt=off -mx15 silesia

TIMES in milliseconds
RunningTime................. 32104
UserTime.................... 31793
KernelTime.................. 249

MEMORY in KiB
PageFaultCount.............. 112
PeakWorkingSetSize.......... 34856
WorkingSetSize.............. 20
QuotaPeakPagedPoolUsage..... 85
QuotaPagedPoolUsage......... 0
QuotaPeakNonPagedPoolUsage.. 6
QuotaNonPagedPoolUsage...... 0
PagefileUsage............... 0
PeakPagefileUsage........... 36296

IO count
ReadOperationCount.......... 81
WriteOperationCount......... 34
OtherOperationCount......... 115
ReadTransferCount........... 211939037
WriteTransferCount.......... 58043652
OtherTransferCount.......... 3414
```

For four threads:
```
Command: 7z a silesia.7z -mmt=4 -mx15 silesia

TIMES in milliseconds
RunningTime................. 11668
UserTime.................... 43025
KernelTime.................. 202

MEMORY in KiB
PageFaultCount.............. 124
PeakWorkingSetSize.......... 133688
WorkingSetSize.............. 20
QuotaPeakPagedPoolUsage..... 85
QuotaPagedPoolUsage......... 0
QuotaPeakNonPagedPoolUsage.. 7
QuotaNonPagedPoolUsage...... 0
PagefileUsage............... 0
PeakPagefileUsage........... 184848

IO count
ReadOperationCount.......... 81
WriteOperationCount......... 34
OtherOperationCount......... 115
ReadTransferCount........... 211939037
WriteTransferCount.......... 58043652
OtherTransferCount.......... 3414
```
