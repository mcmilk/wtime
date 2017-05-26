
## Information given by the help option

```
 Usage: wtime COMMAND [OPTIONS]

 Copyright (c) 2017 Tino Reichardt


 The program will start COMMAND with the given OPTIONS
 and print out some statistic of it to stderr.

 There are no options for this command.

 Report bugs to: https://github.com/mcmilk/wtime/issues
```

## Sample Output

```
Command: = 7z a -mmt=off lala.7z silesia

TIMES in seconds
RunningTime = 3.806;
UserTime    = 2.028;
KernelTime  = 0.172;

MEMORY in KiB
PageFaultCount             = 25
PeakWorkingSetSize         = 9688
WorkingSetSize             = 20
QuotaPeakPagedPoolUsage    = 95
QuotaPagedPoolUsage        = 0
QuotaPeakNonPagedPoolUsage = 5
QuotaNonPagedPoolUsage     = 0
PagefileUsagee             = 0
PeakPagefileUsage          = 11576

IO ops
ReadOperationCount  = 129
WriteOperationCount = 109
OtherOperationCount = 150
ReadTransferCount   = 211939017
WriteTransferCount  = 67500037
OtherTransferCount  = 4272
```
