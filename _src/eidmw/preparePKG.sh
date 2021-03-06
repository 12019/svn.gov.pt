#!/bin/bash

rm -rf pteid-pkg 
mkdir pteid-pkg

mkdir -p pteid-pkg/lib
mkdir -p pteid-pkg/bin
mkdir -p pteid-pkg/eidgui
mkdir -p pteid-pkg/jar
mkdir -p pteid-pkg/misc/certs/

cp -r lib/*  			pteid-pkg/lib/
cp -r bin/*  			pteid-pkg/bin/
cp -r eidgui/*.qm		pteid-pkg/eidgui/
cp -r jar/pteidlibJava.jar	pteid-pkg/jar/
cp misc/certs/*.der		pteid-pkg/misc/certs/

echo "#!/bin/bash" > pteid-pkg/install_pteid.sh

echo "echo \"Este script instala a aplicação do cartão de cidadao\"" >> pteid-pkg/install_pteid.sh
echo "uid=\`id -u\`"  >> pteid-pkg/install_pteid.sh
echo "if [ \$uid -eq 0 ]"  >> pteid-pkg/install_pteid.sh
echo "then"  >> pteid-pkg/install_pteid.sh


# Add Certs
list_of_files=`find misc/certs/ -name "*.der"`
for file in $list_of_files;
do
	echo "  install -m 755 -p \"$file\" \"/usr/local/share/certs\"" >> pteid-pkg/install_pteid.sh
done

echo "  install -m 755 -p \"lib/libpteidpp2-gempc.so\" \"/usr/local/lib/pteidpp/libpteidpp2-gempc.so\"" >> pteid-pkg/install_pteid.sh

echo "  install -m 755 -p \"lib/libfreeimagePTEiD-3.15.1.so\" \"/usr/local/lib/libfreeimagePTEiD-3.15.1.so\"" >> pteid-pkg/install_pteid.sh
echo "  ln -f -s /usr/local/lib/libfreeimagePTEiD-3.15.1.so /usr/local/lib/libfreeimagePTEiD.so"  >> pteid-pkg/install_pteid.sh
echo "  ln -f -s /usr/local/lib/libfreeimagePTEiD-3.15.1.so /usr/local/lib/libfreeimagePTEiD.so.3"  >> pteid-pkg/install_pteid.sh

echo "  install -m 755 -p \"lib/libpteidcommon.so.2.0.0\" \"/usr/local/lib/libpteidcommon.so.2.0.0\"" >> pteid-pkg/install_pteid.sh
echo "  ln -f -s /usr/local/lib/libpteidcommon.so.2.0.0 /usr/local/lib/libpteidcommon.so"  >> pteid-pkg/install_pteid.sh
echo "  ln -f -s /usr/local/lib/libpteidcommon.so.2.0.0 /usr/local/lib/libpteidcommon.so.2"  >> pteid-pkg/install_pteid.sh
echo "  ln -f -s /usr/local/lib/libpteidcommon.so.2.0.0 /usr/local/lib/libpteidcommon.so.2.0"  >> pteid-pkg/install_pteid.sh

echo "  install -m 755 -p \"lib/libpteiddialogsQT.so.2.0.0\" \"/usr/local/lib/libpteiddialogsQT.so.2.0.0\""  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteiddialogsQT.so.2.0.0 /usr/local/lib/libpteiddialogsQT.so"  >> pteid-pkg/install_pteid.sh  
echo "  ln -s -f /usr/local/lib/libpteiddialogsQT.so.2.0.0 /usr/local/lib/libpteiddialogsQT.so.2"  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteiddialogsQT.so.2.0.0 /usr/local/lib/libpteiddialogsQT.so.2.0"  >> pteid-pkg/install_pteid.sh


echo "  install -m 755 -p \"bin/pteiddialogsQTsrv\" \"/usr/local/bin/pteiddialogsQTsrv\""  >> pteid-pkg/install_pteid.sh

echo "  install -m 755 -p \"lib/libpteidcardlayer.so.2.0.0\" \"/usr/local/lib/libpteidcardlayer.so.2.0.0\""  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidcardlayer.so.2.0.0 /usr/local/lib/libpteidcardlayer.so"  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidcardlayer.so.2.0.0 /usr/local/lib/libpteidcardlayer.so.2"  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidcardlayer.so.2.0.0 /usr/local/lib/libpteidcardlayer.so.2.0"  >> pteid-pkg/install_pteid.sh

echo "  install -m 755 -p \"lib/libcardpluginPteid.so.2.0.0\" \"/usr/local/lib/libcardpluginPteid.so.2.0.0\""  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libcardpluginPteid.so.2.0.0 /usr/local/lib/libcardpluginPteid.so"  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libcardpluginPteid.so.2.0.0 /usr/local/lib/libcardpluginPteid.so.2"  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libcardpluginPteid.so.2.0.0 /usr/local/lib/libcardpluginPteid.so.2.0"  >> pteid-pkg/install_pteid.sh

echo "  install -m 755 -p \"lib/libpteidpkcs11.so.2.0.0\" \"/usr/local/lib/libpteidpkcs11.so.2.0.0\""  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidpkcs11.so.2.0.0 /usr/local/lib/libpteidpkcs11.so"  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidpkcs11.so.2.0.0 /usr/local/lib/libpteidpkcs11.so.2"  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidpkcs11.so.2.0.0 /usr/local/lib/libpteidpkcs11.so.2.0"  >> pteid-pkg/install_pteid.sh

echo "  install -m 755 -p \"lib/libpteidapplayer.so.2.0.0\" \"/usr/local/lib/libpteidapplayer.so.2.0.0\""  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidapplayer.so.2.0.0 /usr/local/lib/libpteidapplayer.so"  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidapplayer.so.2.0.0 /usr/local/lib/libpteidapplayer.so.2"  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidapplayer.so.2.0.0 /usr/local/lib/libpteidapplayer.so.2.0"  >> pteid-pkg/install_pteid.sh

echo "  install -m 755 -p \"lib/libpteidlib.so.2.0.0\" \"/usr/local/lib/libpteidlib.so.2.0.0\""  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidlib.so.2.0.0 /usr/local/lib/libpteidlib.so"  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidlib.so.2.0.0 /usr/local/lib/libpteidlib.so.2"  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidlib.so.2.0.0 /usr/local/lib/libpteidlib.so.2.0"  >> pteid-pkg/install_pteid.sh

echo "  install -m 755 -p \"lib/libpteidlibJava_Wrapper.so.2.0.0\" \"/usr/local/lib/libpteidlibJava_Wrapper.so.2.0.0\""  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidlibJava_Wrapper.so.2.0.0 /usr/local/lib/libpteidlibJava_Wrapper.so"  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidlibJava_Wrapper.so.2.0.0 /usr/local/lib/libpteidlibJava_Wrapper.so.2"  >> pteid-pkg/install_pteid.sh
echo "  ln -s -f /usr/local/lib/libpteidlibJava_Wrapper.so.2.0.0 /usr/local/lib/libpteidlibJava_Wrapper.so.2.0"  >> pteid-pkg/install_pteid.sh


echo "  install -m 755 -p \"jar/pteidlibJava.jar\" \"/usr/local/lib/pteid_jni/\""  >> pteid-pkg/install_pteid.sh


echo "  install -m 755 -p \"bin/pteidgui\" \"/usr/local/bin/pteidgui\""  >> pteid-pkg/install_pteid.sh
echo ""  >> pteid-pkg/install_pteid.sh
echo "  install -m 644 -p \"eidgui/eidmw_de.qm\" \"/usr/local/bin/\""  >> pteid-pkg/install_pteid.sh
echo "  install -m 644 -p \"eidgui/eidmw_en.qm\" \"/usr/local/bin/\""  >> pteid-pkg/install_pteid.sh
echo "  install -m 644 -p \"eidgui/eidmw_fr.qm\" \"/usr/local/bin/\""  >> pteid-pkg/install_pteid.sh
echo "  install -m 644 -p \"eidgui/eidmw_nl.qm\" \"/usr/local/bin/\""  >> pteid-pkg/install_pteid.sh



echo "  echo \"Instalação bem sucedida!\"" >> pteid-pkg/install_pteid.sh
echo "  echo \"Pode agora executar a aplicação a partir do comando pteidgui\"" >> pteid-pkg/install_pteid.sh

echo "else" >> pteid-pkg/install_pteid.sh
echo "  echo \"Nao tem permissoes de instalacao! Necessita de permissoes de super-utilizador para instalar o software.\"" >> pteid-pkg/install_pteid.sh
echo "  echo \"Instalação cancelada!\"" >> pteid-pkg/install_pteid.sh
echo "fi" >> pteid-pkg/install_pteid.sh



chmod +x pteid-pkg/install_pteid.sh
tar czvf pteid-pkg.tar.gz pteid-pkg/
