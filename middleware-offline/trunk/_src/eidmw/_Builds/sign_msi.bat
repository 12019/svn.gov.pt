set SIGNTOOL_PATH=C:\WinDDK\7600.16385.1\bin\x86
set MSI_PATH=C:\Users\agrr\pteid-middleware\_src\eidmw\misc\Wix_MW35\MW35Wix\bin\Release\pt-PT\Pteid-MW-2.0-PT.msi

%SIGNTOOL_PATH%\signtool.exe sign /v /sha1 0c526195081d0ec73e3a697f03a17160190a976f /t http://timestamp.verisign.com/scripts/timestamp.dll %MSI_PATH%