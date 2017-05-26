
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
Command: = 7z a lala.7z -mmt=1 -mx15 silesia

TIMES in seconds
RunningTime = 66.757
UserTime    = 65.349
KernelTime  = 0.406

MEMORY in KiB
PageFaultCount             = 110
PeakWorkingSetSize         = 34620
WorkingSetSize             = 20
QuotaPeakPagedPoolUsage    = 95
QuotaPagedPoolUsage        = 0
QuotaPeakNonPagedPoolUsage = 6
QuotaNonPagedPoolUsage     = 0
PagefileUsagee             = 0
PeakPagefileUsage          = 39644

IO ops
ReadOperationCount  = 78
WriteOperationCount = 34
OtherOperationCount = 147
ReadTransferCount   = 211939183
WriteTransferCount  = 58488626
OtherTransferCount  = 4032
```

For two threads:
```
Command: = 7z a lala.7z -mmt=2 -mx15 silesia

TIMES in seconds
RunningTime = 35.847
UserTime    = 64.662
KernelTime  = 0.624

MEMORY in KiB
PageFaultCount             = 114
PeakWorkingSetSize         = 69692
WorkingSetSize             = 20
QuotaPeakPagedPoolUsage    = 95
QuotaPagedPoolUsage        = 0
QuotaPeakNonPagedPoolUsage = 7
QuotaNonPagedPoolUsage     = 0
PagefileUsagee             = 0
PeakPagefileUsage          = 89532

IO ops
ReadOperationCount  = 78
WriteOperationCount = 34
OtherOperationCount = 223
ReadTransferCount   = 211939180
WriteTransferCount  = 58488626
OtherTransferCount  = 4408
```
