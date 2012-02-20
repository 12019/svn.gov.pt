#!/bin/bash

rm SDK_TESTING_OFICIAL
rm SDK_TESTING_NEW-VERSION
rm pic.jp2
rm pic.cbeff
rm SOD_NEW-VERSION
rm SOD_OFICIAL
rm EF05-Address_OFICIAL
rm EF05-Address_NEW-VERSION

echo "***************************A executar o SDK Oficial*********************"
./testOficialCSDK
mv SDK_TESTING   SDK_TESTING_OFICIAL
mv SOD           SOD_OFICIAL
mv pic.jp2       PIC_OFICIAL.jp2
mv pic.cbeff     PIC_OFICIAL.cbeff
mv EF05-Address	 EF05-Address_OFICIAL
echo ""

echo "****************************A executar a nova versão********************"
./testNewversionCSDK
mv SDK_TESTING   SDK_TESTING_NEW-VERSION
mv SOD           SOD_NEW-VERSION
mv pic.jp2       PIC_NEW-VERSION.jp2
mv pic.cbeff     PIC_NEW-VERSION.cbeff
mv EF05-Address	 EF05-Address_NEW-VERSION

echo "************************************************************************"
echo ""
echo "DIFERENÇAS NO OUTPUT:"
diff SDK_TESTING_OFICIAL SDK_TESTING_NEW-VERSION 
echo
echo "DIFERENÇAS NO SOD:"
diff SOD_OFICIAL SOD_NEW-VERSION
echo
echo "DIFERENÇAS NA FOTO:"
diff PIC_OFICIAL.jp2    PIC_NEW-VERSION.jp2
diff PIC_OFICIAL.cbeff  PIC_NEW-VERSION.cbeff
echo 
echo "DIFERENÇAS NO FICHEIRO MORADA (PTEID_READFILE) "
diff EF05-Address_OFICIAL EF05-Address_NEW-VERSION
