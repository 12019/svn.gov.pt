#!/bin/bash

rm SDK_TESTING_OFICIAL
rm SDK_TESTING_NEW-VERSION
rm pic.jp2
rm pic.cbeff
rm SOD_NEW-VERSION
rm SOD_OFICIAL
rm EF05-Address_OFICIAL
rm EF05-Address_NEW-VERSION
rm Cert0_OFICIAL Cert1_OFICIAL Cert2_OFICIAL Cert3_OFICIAL Cert4_OFICIAL


echo "***************************A executar o SDK Oficial*********************"
make run-oficial
mv SDK_TESTING   SDK_TESTING_OFICIAL
mv SOD           SOD_OFICIAL
mv pic.jp2       PIC_OFICIAL.jp2
mv pic.cbeff     PIC_OFICIAL.cbeff
mv EF05-Address	 EF05-Address_OFICIAL
mv Cert0 	 Cert0_OFICIAL
mv Cert1         Cert1_OFICIAL
mv Cert2         Cert2_OFICIAL
mv Cert3         Cert3_OFICIAL
mv Cert4         Cert4_OFICIAL


echo ""

echo "****************************A executar a nova versão********************"
make run-new
mv SDK_TESTING   SDK_TESTING_NEW-VERSION
mv SOD           SOD_NEW-VERSION
mv pic.jp2       PIC_NEW-VERSION.jp2
mv pic.cbeff     PIC_NEW-VERSION.cbeff
mv EF05-Address	 EF05-Address_NEW-VERSION

mv Cert0         Cert0_NEW-VERSION
mv Cert1         Cert1_NEW-VERSION
mv Cert2         Cert2_NEW-VERSION
mv Cert3         Cert3_NEW-VERSION
mv Cert4         Cert4_NEW-VERSION



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
echo 
echo "DIFERENÇAS NOS CERTIFICADOS"
diff Cert0_OFICIAL	Cert0_NEW-VERSION
diff Cert1_OFICIAL      Cert1_NEW-VERSION
diff Cert2_OFICIAL      Cert2_NEW-VERSION
diff Cert3_OFICIAL      Cert3_NEW-VERSION
diff Cert4_OFICIAL      Cert4_NEW-VERSION
